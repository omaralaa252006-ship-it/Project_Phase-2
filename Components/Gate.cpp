#include "Gate.h"
#include "..\GUI\UI_Info.h"
#include <cmath>

//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin
Gate::Gate(int r_Inputs, int r_FanOut):m_OutputPin(r_FanOut)
{
	//Allocate number of input pins (equals r_Inputs)
	m_InputPins = new InputPin[r_Inputs];
	m_Inputs = r_Inputs;	//set no. of inputs of that gate
	
	//Associate all input pins to this gate
	for(int i=0; i<m_Inputs; i++)
		m_InputPins[i].setComponent(this);
}

void Gate::GetOutputPinCoordinates(int& x, int& y)
{
	x = m_GfxInfo.x2;
	y = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
}

void Gate::GetInputPinCoordinates(int& x, int& y, int index)
{
	x = m_GfxInfo.x1;
	// Height is assumed 50
	if (m_Inputs == 1)
	{
		y = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
	}
	else if (m_Inputs == 2)
	{
		if (index == 0) y = m_GfxInfo.y1 + 13;
		else y = m_GfxInfo.y2 - 13;
	}
	else if (m_Inputs == 3)
	{
		if (index == 0) y = m_GfxInfo.y1 + 10;
		else if (index == 1) y = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
		else y = m_GfxInfo.y2 - 10;
	}
}

int Gate::GetInputPinIndex(int x, int y)
{
	// Check distance to each input pin
	for (int i = 0; i < m_Inputs; i++)
	{
		int px, py;
		GetInputPinCoordinates(px, py, i);
		// Tolerance logic: Check if click is close enough
		if (abs(x - px) <= 10 && abs(y - py) <= 10)
			return i;
	}
	return -1;
}

OutputPin* Gate::GetOutputPin()
{
	return &m_OutputPin;
}

InputPin* Gate::GetInputPin(int index)
{
	if (index >= 0 && index < m_Inputs)
		return &m_InputPins[index];
	return NULL;
}