#ifndef _MFLOG10_H
#define _MFLOG10_H

#include "MFunction.h"

class MFLog10:public MFunction{
	protected:
		MFunction *m_argument;

	public:
	MFLog10(MFunction *argument=NULL);
	virtual MFunction* Clone();
	virtual bool IsOk();
	virtual bool IsConstant(MVariablesList* variables);
	virtual MFunction* Solve(MVariablesList* variables);
	virtual MFunction* Derivate(MVariablesList *variables);
	virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL);
	virtual MSistem* CalcDominum(MSistem *update);
	virtual void Release();
	inline MFunction *GetArgument(){
		return m_argument;
	};
	void SetArgument(MFunction *argument);
};

#endif