#ifndef _COMPONENT_H
#define _COMPONENT_H

using namespace std;
#include "..\Defs.h"
#include "..\GUI\Output.h"
#include <string>


//Base class for classes Gate, Switch, and LED.
class Component
{
protected:
	string m_Label;
	bool m_Selected;
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component

public:
	Component(const GraphicsInfo &r_GfxInfo);

	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;	//for each component to Draw itself
	
	void SetSelected(bool s);
	bool IsSelected() const;
	void ToggleSelected();

	GraphicsInfo* GetGraphicsInfo();

	virtual Component* clone() = 0; //for copy and paste

	void SetLabel(const string& label);
	string GetLabel() const;
	
	
	virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	
	virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.

	virtual void Edit();

	Component();
	//Destructor must be virtual
	virtual ~Component();
	
};

#endif
