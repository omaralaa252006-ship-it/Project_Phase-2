#pragma once
#ifndef _COPY_H
#define _COPY_H

#include "Actions/Action.h"

class Copy : public Action
{

public:
	Copy(ApplicationManager* pApp);
	virtual ~Copy(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif