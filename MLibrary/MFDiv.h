#ifndef _MFDIV_H
#define _MFDIV_H

#include "MFunction.h"

class MFDiv:public MFunction{
	protected:
		MFunction *m_num;
		MFunction *m_denum;

	public:
	MFDiv(MFunction *num=NULL,MFunction *denum=NULL);
	virtual MFunction* Clone();
	virtual bool IsOk();
	virtual bool IsConstant(MVariablesList* variables);
	virtual MFunction* Solve(MVariablesList* variables);
	virtual MFunction* Derivate(MVariablesList *variables);
	virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL);
	virtual MSistem* CalcDominum(MSistem *update);
	virtual void Release();
	inline MFunction *GetNum(){
		return m_num;
	};
	inline MFunction *GetDenum(){
		return m_denum;
	};
	void SetNum(MFunction *num);
	void SetDenum(MFunction *denum);
};

#endif