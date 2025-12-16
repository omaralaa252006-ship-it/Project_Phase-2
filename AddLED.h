#ifndef _ADD_LED_H
#define _ADD_LED_H

#include "Actions\Action.h"
#include "..\Project_Phase-2\LED.h"

class AddLED : public Action
{
private:
	int Cx, Cy;	//Center point
public:
	AddLED(ApplicationManager* pApp);
	virtual ~AddLED(void);

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};

#endif
