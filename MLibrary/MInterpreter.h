#ifndef _MINTERPRETER_H
#define _MINTERPRETER_H

#include "MFunction.h"
#include "MFAbs.h"
#include "MFAcos.h"
#include "MFAcotan.h"
#include "MFAdd.h"
#include "MFAsin.h"
#include "MFAtan.h"
#include "MFConst.h"
#include "MFCos.h"
#include "MFCotan.h"
#include "MFDiv.h"
#include "MFExp.h"
#include "MFLn.h"
#include "MFLog.h"
#include "MFLog10.h"
#include "MFMul.h"
#include "MFOpp.h"
#include "MFPow.h"
#include "MFSin.h"
#include "MFSub.h"
#include "MFTan.h"
#include "MFVar.h"
#include "MRelation.h"
#include "MSistem.h"
#include "MVariableElement.h"
#include "MVariablesList.h"

struct FListElement{
	wchar_t op;
	MFunction *func;
	FListElement *next;
};

class MInterpreter{
	protected:
		unsigned int m_pos;
	public:
		wchar_t error[255];

	public:
		MInterpreter();
		MFunction *GenerateFunction(const wchar_t*fStr);
		wchar_t *Clean(wchar_t * str) const;

	protected:
		bool AnalizeParentesis(const wchar_t *fStr);
		bool AnalizePlane(const wchar_t *fStr, MFunction **pt,wchar_t delimiter=')');
		unsigned int IsFunction(const wchar_t *fStr);
		bool AnalizeFunction(const wchar_t *fStr, MFunction **pt);
		bool AnalizeCharCoerency(const wchar_t *fStr);
		bool CreateList(const wchar_t *fStr, FListElement **pt, wchar_t delimiter);
		bool ConvertList(FListElement *pt);
		bool ConvertElement(const wchar_t *fStr, MFunction **pt);
};

#endif