#include "MFTan.h"
#include "MFConst.h"
#include "MFMul.h"
#include "MFDiv.h"
#include "MFPow.h"
#include "MFCos.h"

MFTan::MFTan(MFunction *argument){
	if (argument) m_argument=argument->Clone();
	else m_argument=NULL;
	m_type=MF_TAN;
}

MFunction* MFTan::Clone(){
	return new MFTan(m_argument);
}

bool MFTan::IsOk(){
	if (!m_argument) return false;
	if (!m_argument->IsOk()) return false;
	return true;
}

bool MFTan::IsConstant(MVariablesList* variables){
	if (m_argument)
		if(!m_argument->IsConstant(variables)) return false;
	return true;
}

MFunction* MFTan::Solve(MVariablesList* variables){
	if (!m_argument) return new MFConst(0.0);
	MFunction *argument=m_argument->Solve(variables);
	if (argument->GetType()==MF_CONST){
		double value=tan(((MFConst*)argument)->GetValue());
		argument->Release();
		return new MFConst(value);
	}
	MFTan *ret=new MFTan();
	ret->SetArgument(argument);
	return ret;
}

MFunction* MFTan::Derivate(MVariablesList *variables){
	if (!m_argument) return NULL;
	if (m_argument->IsConstant(variables)) return new MFConst(0.0);
	MFunction *fn=m_argument->Derivate(variables);
	if (!fn) return NULL;
	MFMul *ret= new MFMul();
	ret->SetRhs(fn);
	MFDiv *lhs= new MFDiv();
	MFConst *num= new MFConst(1.0);
	lhs->SetNum(num);
	MFCos *arg= new MFCos(m_argument);
	MFPow *denum= new MFPow();
	MFConst *exp= new MFConst(2.0);
	denum->SetBase(arg);
	denum->SetExponent(exp);
	lhs->SetDenum(denum);
	ret->SetLhs(lhs);
	return ret;
}

MVariablesList* MFTan::GetVariablesList(MVariablesList *list){
	if (!m_argument) return list;
	return m_argument->GetVariablesList(list);
}

MSistem* MFTan::CalcDominum(MSistem *update){
	if (!m_argument) return update;
	return m_argument->CalcDominum(update);
}

void MFTan::SetArgument(MFunction *argument){
	if (m_argument) m_argument->Release();
	m_argument=argument;
}

void MFTan::Release(){
	if (m_argument)	m_argument->Release();
	delete this;
}