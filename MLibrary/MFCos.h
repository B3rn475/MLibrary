#ifndef _MFCOS_H
#define _MFCOS_H

#include "MFunction.h"

class MFCos:public MFunction{
	protected:
		MFunction *m_argument;

	public:
	MFCos(MFunction *argument=NULL);
	virtual MFunction* Clone();
	virtual bool IsOk();
	virtual bool IsConstant(MVariablesList* variables);
	virtual MFunction* Solve(MVariablesList* variables);
	virtual MFunction* Derivate(MVariablesList *variables);
	virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL);
	virtual MSistem* CalcDominum(MSistem *update);
	inline MFunction *GetArgument(){
		return m_argument;
	}
	void SetArgument(MFunction *argument);
	virtual void Release();
};

#endif