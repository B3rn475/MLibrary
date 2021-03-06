#ifndef _MFOPP_H
#define _MFOPP_H

#include "MFunction.h"

class MFOpp:public MFunction{
	protected:
		MFunction *m_fn;

	public:
	MFOpp(MFunction *fn=NULL);
	virtual MFunction* Clone();
	virtual bool IsOk();
	virtual bool IsConstant(MVariablesList* variables);
	virtual MFunction* Solve(MVariablesList* variables);
	virtual MFunction* Derivate(MVariablesList *variables);
	virtual MVariablesList* GetVariablesList(MVariablesList *list=NULL);
	virtual MSistem* CalcDominum(MSistem *update);
	virtual void Release();
	inline MFunction *GetFn(){
		return m_fn;
	}
	void SetFn(MFunction *fn);
};

#endif