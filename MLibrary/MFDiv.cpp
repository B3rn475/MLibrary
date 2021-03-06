#include "MFDiv.h"
#include "MFPow.h"
#include "MFMul.h"
#include "MFOpp.h"
#include "MFSub.h"
#include "MFConst.h"

MFDiv::MFDiv(MFunction *num,MFunction *denum){
	if (num) m_num=num->Clone();
	else m_num=NULL;
	if (denum) m_denum=denum->Clone();
	else m_denum=NULL;
	m_type=MF_DIV;
}

MFunction* MFDiv::Clone(){
	return new MFDiv(m_num,m_denum);
}

bool MFDiv::IsOk(){
	if (!m_num) return false;
	if (!m_denum) return false;
	if (!m_num->IsOk()) return false;
	if (!m_denum->IsOk()) return false;
	return true;
}

bool MFDiv::IsConstant(MVariablesList* variables){
	if (m_num)
		if(!m_num->IsConstant(variables)) return false;
	if (m_denum)
		if(!m_denum->IsConstant(variables)) return false;
	return true;
}

MFunction* MFDiv::Solve(MVariablesList* variables){
	if (!m_num || !m_denum) return new MFConst(0.0);
	MFunction *num=m_num->Solve(variables);
	MFunction *denum=m_denum->Solve(variables);
	if (num->GetType()==MF_CONST && denum->GetType()==MF_CONST){
		double value=((MFConst*)num)->GetValue()/((MFConst*)denum)->GetValue();
		num->Release();
		denum->Release();
		return new MFConst(value);
	}
	MFDiv *ret=new MFDiv();
	ret->SetNum(num);
	ret->SetDenum(denum);
	return ret;
}

MFunction* MFDiv::Derivate(MVariablesList *variables){
	if (!m_num || !m_denum) return NULL;
	if (m_num->IsConstant(variables)){
		if (m_denum->IsConstant(variables)){
			return new MFConst(0.0);
		}else{
			MFunction *fn=m_denum->Derivate(variables);
			if (!fn) return NULL;
			MFOpp *ret = new MFOpp();
			MFDiv *arg = new MFDiv();
			MFMul *num = new MFMul(m_num);
			MFPow *denum= new MFPow(m_denum);
			denum->SetExponent(new MFConst(2.0));
			num->SetRhs(fn);
			arg->SetNum(num);
			arg->SetDenum(denum);
			ret->SetFn(arg);
			return ret;
		}
	}else{
		if (m_denum->IsConstant(variables)){
			MFunction *fn=m_num->Derivate(variables);
			if (!fn) return NULL;
			MFDiv *ret = new MFDiv(NULL,m_denum);
			ret->SetNum(fn);
			return ret;
		}else{
			MFunction *num=m_num->Derivate(variables);
			if (!num) return NULL;
			MFunction *denum=m_denum->Derivate(variables);
			if (!denum){
				num->Release();
				return NULL;
			}
			MFDiv *ret=new MFDiv();
			MFSub *nnum =new MFSub();
			MFPow *ndenum = new MFPow(m_denum);
			ndenum->SetExponent(new MFConst(2.0));
			MFMul *lhs= new MFMul(num,m_denum);
			MFMul *rhs= new MFMul(denum,m_num);
			num->Release();
			denum->Release();
			nnum->SetLhs(lhs);
			nnum->SetRhs(rhs);
			ret->SetNum(nnum);
			ret->SetDenum(ndenum);
			return ret;
		}
	}
}

MVariablesList* MFDiv::GetVariablesList(MVariablesList *list){
	if (!m_num || !m_denum) return list;
	list = m_num->GetVariablesList(list);
	return m_denum->GetVariablesList(list);
}

MSistem* MFDiv::CalcDominum(MSistem *update){
	if (!m_num || !m_denum) return update;
	update = m_num->CalcDominum(update);
	update = m_denum->CalcDominum(update);
	if (!update) update=new MSistem();
	MFConst z(0.0);
	update->Add(MR_NOT_EQUAL,*m_denum,z);
	return update;
}

void MFDiv::SetNum(MFunction *num){
	if (m_num) m_num->Release();
	m_num=num;
}

void MFDiv::SetDenum(MFunction *denum){
	if (m_denum) m_denum->Release();
	m_denum=denum;
}

void MFDiv::Release(){
	if (m_denum) m_denum->Release();
	if (m_num) m_num->Release();
	delete this;
}