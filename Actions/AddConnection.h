#pragma once
#include "Action.h"
#include "..\Components\Connection.h"

class AddConnection : public Action
{
private:
	GraphicsInfo mGfxInfo;			// The parameters (coordinates) required to draw the connection
	OutputPin* mSrcPin;				// Pointer to the source pin
	InputPin* mDstPin;				// Pointer to the destination pin
	int mDstPinIndex;				// The index of the destination pin

public:
	/* Constructor */
	AddConnection(ApplicationManager* pAppMan);

	/* Reads parameters required for action to execute */
	virtual void ReadActionParameters();

	/* Executes action */
	virtual void Execute();

	/* Undo action */
	virtual void Undo();

	/* Redo action */
	virtual void Redo();

	/* Destructor */
	virtual ~AddConnection();

private:
	/* Detects the source component of the connection */
	bool DetectSourceComponent(int x, int y);

	/* Detects the destination component of the connection */
	bool DetectDestinationComponent(int x, int y);
};
