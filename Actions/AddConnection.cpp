#include "AddConnection.h"
#include "..\ApplicationManager.h"
#include "..\Components\Gate.h"
#include "..\Components\Connection.h"
#include "..\Components\OutputPin.h"
#include "..\Components\InputPin.h"

AddConnection::AddConnection(ApplicationManager* pAppMan) : Action(pAppMan)
{
	mSrcPin = NULL;
	mDstPin = NULL;
	mDstPinIndex = -1;
}

AddConnection::~AddConnection()
{
}

void AddConnection::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->PrintMsg("Connection: Click on the Source Pin");
	
	// Read 1st Click
	pIn->GetPointClicked(mGfxInfo.x1, mGfxInfo.y1);

	// Detect if a valid source component (Output Pin) was clicked
	if (!DetectSourceComponent(mGfxInfo.x1, mGfxInfo.y1))
	{
		pOut->PrintMsg("Invalid Source Pin! Operation Cancelled.");
		return;
	}

	pOut->PrintMsg("Connection: Click on the Destination Pin");

	// Read 2nd Click
	pIn->GetPointClicked(mGfxInfo.x2, mGfxInfo.y2);

	// Detect if a valid destination component (Input Pin) was clicked
	if (!DetectDestinationComponent(mGfxInfo.x2, mGfxInfo.y2))
	{
		pOut->PrintMsg("Invalid Destination Pin! Operation Cancelled.");
		mSrcPin = NULL; // Reset source pin
		return;
	}

	pOut->ClearStatusBar();
}

void AddConnection::Execute()
{
	ReadActionParameters();

	if (mSrcPin && mDstPin)
	{
		Connection* pConn = new Connection(mGfxInfo, mSrcPin, mDstPin);
		mSrcPin->ConnectTo(pConn);
		mDstPin->setConnected(true);
		pManager->AddComponent(pConn);
		pManager->GetOutput()->PrintMsg("Connection Created Successfully");
	}
}

void AddConnection::Undo()
{}

void AddConnection::Redo()
{}

bool AddConnection::DetectSourceComponent(int x, int y)
{
	Component* comp = pManager->GetComponentAt(x, y);

	if (comp == NULL)
		return false;

	// Check if it's a Gate
	Gate* gate = dynamic_cast<Gate*>(comp);
	if (gate)
	{
		// Check if click is near output pin
		int ox, oy;
		gate->GetOutputPinCoordinates(ox, oy);
		if (abs(x - ox) <= 15 && abs(y - oy) <= 15) // Tolerance
		{
			// Verify if output pin is not full
			if (!gate->GetOutputPin()->isFull())
			{
				mSrcPin = gate->GetOutputPin();
				// Update coordinates to exact pin location for drawing
				mGfxInfo.x1 = ox;
				mGfxInfo.y1 = oy;
				return true;
			}
		}
	}
	// Note: Switch doesn't have Input pins but has Output pin. 
	// The provided code used dynamic_cast<Gate*>. SWITCH inherits from Gate in this project.
	// So dynamic_cast<Gate*> works for Switch too.
	// However, Switch has Output Pin.

	return false;
}

#include "..\LED.h"

// ... (existing includes)

// at the top of file or better just add include

bool AddConnection::DetectDestinationComponent(int x, int y)
{
	Component* comp = pManager->GetComponentAt(x, y);

	if (comp == NULL)
		return false;

	Gate* gate = dynamic_cast<Gate*>(comp);
	if (gate)
	{
		int index = gate->GetInputPinIndex(x, y);
		if (index != -1)
		{
			InputPin* pin = gate->GetInputPin(index);
			if (pin && !pin->isConnected())
			{
				mDstPin = pin;
				mDstPinIndex = index;
				// Update coordinates to exact pin location for drawing
				int ix, iy;
				gate->GetInputPinCoordinates(ix, iy, index);
				mGfxInfo.x2 = ix;
				mGfxInfo.y2 = iy;
				return true;
			}
		}
	}
	
	LED* led = dynamic_cast<LED*>(comp);
	if (led)
	{
		InputPin* pin = led->GetInputPin();
		int lx, ly;
		led->GetInputPinCoordinates(lx, ly);
		
		if (abs(x - lx) <= 15 && abs(y - ly) <= 15)
		{
			if (pin && !pin->isConnected())
			{
				mDstPin = pin;
				// LED has only one input, index 0 implicitly
				mDstPinIndex = 0;
				mGfxInfo.x2 = lx;
				mGfxInfo.y2 = ly;
				return true;
			}
		}
	}

	return false;
}
