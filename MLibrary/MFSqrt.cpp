#include "MFSqrt.h"
#include "MFAbs.h"
#include "MFConst.h"
#include "MFMul.h"
#include "MFPow.h"
#include "MFDiv.h"

MFSqrt::MFSqrt(MFunction *fn){
	if (fn) m_fn=fn->Clone();
	else m_fn=NULL;
	m_type=MF_SQRT;
}

MFunction* MFSqrt::Clone(){
	return new MFSqrt(m_fn);
}

bool MFSqrt::IsOk(){
	if (!m_fn) return false;
	if (!m_fn->IsOk()) return false;
	return true;
}

bool MFSqrt::IsConstant(MVariablesList* variables){
	if (m_fn)
		if(!m_fn->IsConstant(variables)) return false;
	return true;
}

MFunction* MFSqrt::Solve(MVariablesList* variables){
	if (!m_fn) return new MFConst(0.0);
	MFunction *fn=m_fn->Solve(variables);
	if (fn->GetType()==MF_CONST){
		double value=sqrt(((MFConst*)fn)->GetValue());
		fn->Release();
		return new MFConst(value);
	}
	if (fn->GetType()==MF_POW){
		if (((MFPow*)fn)->GetExponent()->GetType()==MF_CONST)
		{
			MFConst* exp =(MFConst*)((MFPow*)fn)->GetExponent();
			if (exp->GetValue() == 2.0)
			{
				MFAbs *ret=new MFAbs();				
				ret->SetFn(((MFPow*)fn)->GetExponent());
				delete fn;
				return ret;
			}
		}
	}
	MFSqrt *ret=new MFSqrt();
	ret->SetFn(fn);
	return ret;
}

MFunction* MFSqrt::Derivate(MVariablesList *variables){
	if (!m_fn) return new MFConst(0.0);
	if (m_fn->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_fn->Derivate(variables);
	if (!fn) return NULL;
	MFDiv *ret=new MFDiv();
	ret->SetNum(fn);
	MFMul *denum=new MFMul(m_fn);
	MFConst* con = new MFConst(0.2);
	denum->SetRhs(con);
	ret->SetDenum(denum);
	return ret;
}

MVariablesList* MFSqrt::GetVariablesList(MVariablesList *list){
	if (!m_fn) return list;
	return m_fn->GetVariablesList(list);
}

MSistem* MFSqrt::CalcDominum(MSistem *update){
	if (!m_fn) return update;
	update = m_fn->CalcDominum(update);
	if (!update) update=new MSistem();
	MFConst z(0.0);
	update->Add(MR_MAJOR_OR_EQUAL,*m_fn,z);
	return update;
}

void MFSqrt::SetFn(MFunction *fn){
	if (m_fn) m_fn->Release();
	m_fn=fn;
}

void MFSqrt::Release(){
	if (m_fn) m_fn->Release();
	delete this;
}