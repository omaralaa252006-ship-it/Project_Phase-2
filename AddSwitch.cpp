#include "AddSwitch.h"
#include "OR2.h"
#include "ApplicationManager.h"


AddSwitch::AddSwitch(ApplicationManager* pApp) :Action(pApp)
{
}

AddSwitch::~AddSwitch(void)
{
}

void AddSwitch::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Switch: Click to add the Switch");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddSwitch::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners
	int Len = UI.OR2_Width;
	int Wdth = UI.OR2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the OR2 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	SWITCH* pA = new SWITCH(GInfo, OR2_FANOUT);
	pManager->AddComponent(pA);
}

void AddSwitch::Undo()
{
}

void AddSwitch::Redo()
{
}