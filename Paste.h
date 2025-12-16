#pragma once
#ifndef _Paste_H
#define _Paste_H

#include "Actions/Action.h"

class Paste : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Px, Py;	//Center point of the gate

public:
	Paste(ApplicationManager* pApp);
	virtual ~Paste(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};

#endif