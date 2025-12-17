#include "LED.h"
#include "Components/Component.h"

LED::LED(const GraphicsInfo& r_GfxInfo) : Component(r_GfxInfo)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;

	m_InputPin.setComponent(this);
}

void LED::Operate()
{
	// LED just absorbs the input status. 
	// The InputPin status is set by the Connection.
}

void LED::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawLED(m_GfxInfo, IsSelected()); {


		if (!m_Label.empty())
		{
			int labelX = m_GfxInfo.x1 + UI.AND2_Width / 2 - (m_Label.length() * 4);
			int labelY = m_GfxInfo.y1 - 15;

			pOut->DrawString(labelX, labelY, m_Label);
		}

	};
}

int LED::GetOutPinStatus()
{
	return -1; // LED has no output pin
}

int LED::GetInputPinStatus(int n)
{
	// LED has one input pin, n is ignored or should be checked
	return m_InputPin.getStatus();
}

void LED::setInputPinStatus(int n, STATUS s)
{
	m_InputPin.setStatus(s);
}

Component* LED::clone()
{
	return new LED(*this);
}

InputPin* LED::GetInputPin()
{
	return &m_InputPin;
}

void LED::GetInputPinCoordinates(int& x, int& y)
{
	x = m_GfxInfo.x1;
	y = (m_GfxInfo.y1 + m_GfxInfo.y2) / 2;
}
