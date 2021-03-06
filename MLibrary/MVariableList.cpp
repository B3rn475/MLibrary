#include "MVariablesList.h"

MVariablesList::MVariablesList(){
	m_pt=NULL;
	m_count=0;
}
MVariablesList::MVariablesList(MVariablesList &origin){
	MVariablesList();
	for(int i=0;i<origin.Count();i++){
		Add(origin.GetItem(i));
	}
}

MVariablesList::~MVariablesList(){
	if (m_count==0) return;
	while (DeleteElement(0)){}
}

MVariableElement *MVariablesList::Add(const wchar_t *name, double value){
	MvariablesItem **temp=&m_pt;
	while((*temp)!=NULL){
		temp=&((*temp)->next);
	}
	(*temp)=(MvariablesItem*)malloc(sizeof(MvariablesItem));
	(*temp)->next=NULL;
	(*temp)->link=new MVariableElement(name,value);
	m_count++;
	return (*temp)->link;
}

MVariableElement *MVariablesList::Add(MVariableElement *element){
	return Add(element->GetName(),element->GetValue());
}

MVariableElement *MVariablesList::GetItem(int index){
	if (index<0 || index>=Count()) return NULL;
	MvariablesItem *temp=m_pt;
	for (int i=0;i<index;i++){
		temp=temp->next;
	}
	return temp->link;
}

MVariableElement *MVariablesList::GetItem(const wchar_t *name){
	if (!name) return NULL;
	MvariablesItem *temp=m_pt;
	for (int i=0;i<Count();i++){
		if (!wcscmp(name,temp->link->GetName())){
			return temp->link;
		}
		temp=temp->next;
	}
	return NULL;
}

int MVariablesList::FindItem(const wchar_t *name){
	if (!name) return NULL;
	MvariablesItem *temp=m_pt;
	for (int i=0;i<Count();i++){
		if (!wcscmp(name,temp->link->GetName())){
			return i;
		}
		temp=temp->next;
	}
	return -1;
}

int MVariablesList::DeleteElement(int index){
	if (index<0 || index>=Count()) return -1;
	MvariablesItem **temp=&m_pt;
	for (int i=0;i<index;i++){
		temp=&((*temp)->next);
	}
	MvariablesItem *toDel=(*temp);
	(*temp)=(*temp)->next;
	delete toDel->link;
	free(toDel);
	return --m_count;
}

int MVariablesList::DeleteElement(const wchar_t *name){
	return DeleteElement(FindItem(name));
}
