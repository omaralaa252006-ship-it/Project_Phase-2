#ifndef _LED_H
#define _LED_H

#include "Components/Component.h"
#include "Components/InputPin.h"

class LED : public Component
{
	InputPin m_InputPin;
public:
	LED(const GraphicsInfo& r_GfxInfo);
	virtual void Operate();
	virtual void Draw(Output* pOut);

	virtual int GetOutPinStatus();	//returns -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.

	virtual Component* clone() override;
	
	InputPin* GetInputPin();
	void GetInputPinCoordinates(int& x, int& y);
};

#endif
