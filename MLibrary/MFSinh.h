#ifndef _MFSINH_H
#define _MFSINH_H

#include "MFunction.h"

class MFSinh:public MFunction{
	protected:
		MFunction *m_argument;

	public:
	MFSinh(MFunction *argument=NULL);
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
	}
	void SetArgument(MFunction *argument);
};

#endif