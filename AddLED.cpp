#include "AddLED.h"
#include "LED.h"
#include "ApplicationManager.h"


AddLED::AddLED(ApplicationManager* pApp) :Action(pApp)
{
}

AddLED::~AddLED(void)
{
}

void AddLED::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("LED: Click to add");

	pIn->GetPointClicked(Cx, Cy);
	pOut->ClearStatusBar();
}

void AddLED::Execute()
{
	ReadActionParameters();

	GraphicsInfo GInfo;
	GInfo.x1 = Cx - UI.LED_Width / 2;
	GInfo.x2 = Cx + UI.LED_Width / 2;
	GInfo.y1 = Cy - UI.LED_Height / 2;
	GInfo.y2 = Cy + UI.LED_Height / 2;

	LED* pL = new LED(GInfo);
	pManager->AddComponent(pL);
}

void AddLED::Undo()
{
}

void AddLED::Redo()
{
}
