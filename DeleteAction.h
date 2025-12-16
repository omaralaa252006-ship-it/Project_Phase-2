#pragma once
#ifndef _DELETEACTION_H
#define _DELETEACTION_H

#include "Actions/Action.h"

class DeleteAction : public Action
{
public:
	DeleteAction(ApplicationManager* pApp);
	virtual ~DeleteAction(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};

#endif