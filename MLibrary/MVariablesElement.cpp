#include "MVariableElement.h"

MVariableElement::MVariableElement(const wchar_t* name,double value){
	this->SetName(name);
	this->SetValue(value);
}
MVariableElement::MVariableElement(MVariableElement &origin){
	(*this)=origin;
}
void MVariableElement::SetName(const wchar_t* name){
	if (!name) return;
	wcscpy_s(m_name,variables_MAX_NAME_LEN+1,name);
}