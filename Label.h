#pragma once
#ifndef _LABEL_H
#define _LABEL_H
using namespace std;
#include "Actions/Action.h"
#include <string>

class Label : public Action
{
private:
	string LabelCom;

public:
	Label(ApplicationManager* pApp);
	virtual ~Label(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif