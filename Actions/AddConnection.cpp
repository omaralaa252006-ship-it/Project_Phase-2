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

	// If direct click didn't find a component, search in a small radius
	if (comp == NULL)
	{
		const int searchOffsets[] = {-20, -10, 0, 10, 20};
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				comp = pManager->GetComponentAt(x + searchOffsets[i], y + searchOffsets[j]);
				if (comp != NULL)
					break;
			}
			if (comp != NULL)
				break;
		}
	}

	if (comp == NULL)
		return false;

	// Check if it's a Gate (all gates including SWITCH have output pins)
	Gate* gate = dynamic_cast<Gate*>(comp);
	if (gate)
	{
		// Clicking anywhere on the gate uses its output pin
		// No need to click exactly on the pin location
		if (!gate->GetOutputPin()->isFull())
		{
			mSrcPin = gate->GetOutputPin();
			// Get exact pin coordinates for drawing
			int ox, oy;
			gate->GetOutputPinCoordinates(ox, oy);
			mGfxInfo.x1 = ox;
			mGfxInfo.y1 = oy;
			return true;
		}
	}

	return false;
}



#include "..\LED.h"

// ... (existing includes)

// at the top of file or better just add include

bool AddConnection::DetectDestinationComponent(int x, int y)
{
	Component* comp = pManager->GetComponentAt(x, y);

	// If direct click didn't find a component, search in a small radius
	if (comp == NULL)
	{
		const int searchOffsets[] = {-20, -10, 0, 10, 20};
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				comp = pManager->GetComponentAt(x + searchOffsets[i], y + searchOffsets[j]);
				if (comp != NULL)
					break;
			}
			if (comp != NULL)
				break;
		}
	}

	if (comp == NULL)
		return false;

	// Check if it's a Gate - find first available (unconnected) input pin
	Gate* gate = dynamic_cast<Gate*>(comp);
	if (gate)
	{
		// Try to find the first unconnected input pin
		// First, try to match by click position if possible
		int index = gate->GetInputPinIndex(x, y);
		if (index != -1)
		{
			InputPin* pin = gate->GetInputPin(index);
			if (pin && !pin->isConnected())
			{
				mDstPin = pin;
				mDstPinIndex = index;
				int ix, iy;
				gate->GetInputPinCoordinates(ix, iy, index);
				mGfxInfo.x2 = ix;
				mGfxInfo.y2 = iy;
				return true;
			}
		}
		
		// If no pin matched by position, find first unconnected pin
		for (int i = 0; i < 3; i++) // Gates have max 3 inputs
		{
			InputPin* pin = gate->GetInputPin(i);
			if (pin && !pin->isConnected())
			{
				mDstPin = pin;
				mDstPinIndex = i;
				int ix, iy;
				gate->GetInputPinCoordinates(ix, iy, i);
				mGfxInfo.x2 = ix;
				mGfxInfo.y2 = iy;
				return true;
			}
		}
	}
	
	// Check if it's an LED - clicking anywhere uses its input pin
	LED* led = dynamic_cast<LED*>(comp);
	if (led)
	{
		InputPin* pin = led->GetInputPin();
		if (pin && !pin->isConnected())
		{
			mDstPin = pin;
			mDstPinIndex = 0;
			int lx, ly;
			led->GetInputPinCoordinates(lx, ly);
			mGfxInfo.x2 = lx;
			mGfxInfo.y2 = ly;
			return true;
		}
	}

	return false;
}

