#ifndef _MRELATION_H
#define _MRELATION_H

class MRelation;

#include "MFunction.h"


#define MR_EQUAL 0x0001
#define MR_MAJOR 0x0002
#define MR_MINOR 0x0004
#define MR_NOT_EQUAL MR_MAJOR|MR_MINOR
#define MR_MAJOR_OR_EQUAL  MR_EQUAL|MR_MAJOR
#define MR_MINOR_OR_EQUAL  MR_EQUAL|MR_MINOR
#define MR_FINITE 0x0008

class MRelation{
	
	protected:
		MFunction *m_lhs;
		MFunction *m_rhs;
		int m_type;
	
	public:
		MRelation(int type=MR_EQUAL,MFunction* lhs=NULL,MFunction* rhs=NULL);
		MRelation(MRelation &origin);
		~MRelation();
		void SetType(int type=MR_EQUAL){
			m_type=type;
		};
		inline int GetType(){
			return m_type;
		};
		bool IsTrue(MVariablesList *variables);
		MVariablesList *GetVariablesList();
		MRelation *Solve(MVariablesList *variables);
		void SetLeftFunction(MFunction &origin);
		void GetRightFunction(MFunction &origin);
		MFunction *GetLeftFunction();
		MFunction *GetRightFunction();

};

#endif