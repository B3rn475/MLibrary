#include "MFAsin.h"
#include "MFConst.h"
#include "MFMul.h"
#include "MFPow.h"
#include "MFSub.h"


MFAsin::MFAsin(MFunction *argument){
	if (argument) m_argument=argument->Clone();
	else m_argument=NULL;
	m_type=MF_ASIN;
}

MFunction* MFAsin::Clone(){
	return new MFAsin(m_argument);
}

bool MFAsin::IsOk(){
	if (!m_argument) return false;
	if (!m_argument->IsOk()) return false;
	return true;
}

bool MFAsin::IsConstant(MVariablesList* variables){
	if (m_argument)
		if(!m_argument->IsConstant(variables)) return false;
	return true;
}

MFunction* MFAsin::Solve(MVariablesList* variables){
	if (!m_argument) return new MFConst(0.0);
	MFunction *argument=m_argument->Solve(variables);
	if (argument->GetType()==MF_CONST){
		double value=asin(((MFConst*)argument)->GetValue());
		delete argument;
		return new MFConst(value);
	}
	MFAsin *ret=new MFAsin();
	ret->SetArgument(argument);
	return ret;
}

MFunction* MFAsin::Derivate(MVariablesList *variables){
	if (!m_argument) return NULL;
	if (m_argument->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_argument->Derivate(variables);
	if (!fn) return NULL;
	MFMul *ret= new MFMul();
	ret->SetRhs(fn);
	MFPow *arg= new MFPow();
	MFSub *aarg = new MFSub();
	MFPow *aarghs = new MFPow(m_argument);
	aarghs->SetExponent(new MFConst(2.0));
	aarg->SetLhs(new MFConst(1.0));
	aarg->SetRhs(aarghs);
	arg->SetBase(aarg);
	arg->SetExponent(new MFConst(-0.5));
	ret->SetLhs(arg);
	return ret;
}

MVariablesList* MFAsin::GetVariablesList(MVariablesList *list){
	if (!m_argument) return list;
	return m_argument->GetVariablesList(list);
}

MSistem* MFAsin::CalcDominum(MSistem *update){
	if (!m_argument) return update;
	update = m_argument->CalcDominum(update);
	if (!update) update=new MSistem();
	MFConst z(-1.0);
	update->Add(MR_MAJOR_OR_EQUAL,*m_argument,z);
	z.SetValue(1.0);
	update->Add(MR_MINOR_OR_EQUAL,*m_argument,z);
	return update;
}

void MFAsin::SetArgument(MFunction *argument){
	if (m_argument) delete m_argument;
	m_argument=argument;
}

void MFAsin::Release(){
	if (m_argument) m_argument->Release();
	delete this;
}