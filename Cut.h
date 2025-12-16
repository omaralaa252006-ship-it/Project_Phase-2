#pragma once
#ifndef _CUT_H
#define _CUT_H

#include "Actions/Action.h"

class Cut : public Action
{
public:
	Cut(ApplicationManager* pApp);
	virtual ~Cut(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif