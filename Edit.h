#pragma once
#ifndef _EDIT_H
#define _EDIT_H

#include "Actions/Action.h"

class Edit : public Action
{
public:
	Edit(ApplicationManager* pApp);
	virtual ~Edit(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif