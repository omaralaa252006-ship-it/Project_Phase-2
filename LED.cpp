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
	pOut->DrawLED(m_GfxInfo, IsSelected());
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
