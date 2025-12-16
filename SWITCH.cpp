#include "SWITCH.h"

SWITCH::SWITCH(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void SWITCH::Operate()
{
	//caclulate the output status as the ORing of the two input pins

	//Add you code here
	if (m_InputPins[0].getStatus() == HIGH)
	{
		m_OutputPin.setStatus(HIGH);
	}
	else
	{
		m_OutputPin.setStatus(LOW);
	}

}

Component* SWITCH::clone() {
	return new SWITCH(*this); // Returns a new SWITCH copy
}

// Function Draw
// Draws 2-input OR gate
void SWITCH::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawSwitch(m_GfxInfo, IsSelected()); {


		if (!m_Label.empty())
		{
			int labelX = m_GfxInfo.x1 + UI.AND2_Width / 2 - (m_Label.length() * 4);
			int labelY = m_GfxInfo.y1 - 15;

			pOut->DrawString(labelX, labelY, m_Label);
		}

	};
}

//returns status of outputpin
int SWITCH::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int SWITCH::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void SWITCH::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}