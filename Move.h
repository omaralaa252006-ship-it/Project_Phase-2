#pragma once
#ifndef _MOVE_H
#define _MOVE_H

#include "Actions/Action.h"

class Move : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int newX,newY;	//Center point of the gate

public:
	Move(ApplicationManager* pApp);
	virtual ~Move(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};

#endif