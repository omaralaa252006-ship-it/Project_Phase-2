#include "ApplicationManager.h"
#include "Actions\AddConnection.h"
#include "Actions\AddANDgate2.h"
#include "AddORgate2.h"
#include "AddNANDgate2.h"
#include "AddNORgate2.h"
#include "AddXORgate2.h"
#include "AddXNORgate2.h"
#include "AddANDgate3.h"
#include "AddNORgate3.h"
#include "AddXORgate3.h"
#include "AddBUFFgate.h"
#include "AddINVgate.h"
#include "AddSwitch.h"
#include "DeleteAction.h"
#include "Select.h"
#include "Label.h"
#include "Edit.h"
#include "Copy.h"
#include "Cut.h"
#include "Paste.h"
#include "AddLED.h"



ApplicationManager::ApplicationManager()
{
	CompCount = 0;
	SelectedCount = 0;
	ClipboardComp = nullptr;
	IsCut = false;

	for (int i = 0; i < MaxCompCount; i++)
	{
		CompList[i] = NULL;
		SelectedComps[i] = NULL;
	}
	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
}
////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	if (CompCount >= MaxCompCount) return;
	CompList[CompCount++] = pComp;		
}
////////////////////////////////////////////////////////////////////

Component* ApplicationManager::GetComponentAt(int x, int y) {
	for (int i = CompCount - 1;i >= 0;i--) {
		GraphicsInfo* pGfx = CompList[i]->GetGraphicsInfo();
	 
		if (x >= pGfx->x1 && x <= pGfx->x2 && y >= pGfx->y1 && y <= pGfx->y2)
			return CompList[i];
	
	}
	return nullptr;
}

void ApplicationManager::DeleteComponent(Component* pComp)
{

	if (!pComp)
		return;
	RemoveFromSelection(pComp);

	for (int i = 0;i < CompCount;i++) {
		if (CompList[i] == pComp) {

			for (int j = i;j < CompCount - 1;j++)
				CompList[j] = CompList[j + 1];

			CompList[CompCount - 1] = nullptr;
			CompCount--;
			delete pComp;
			return;
		}
	}
}

void ApplicationManager::AddToSelection(Component* pComp) {
	if (!pComp) { return; }

	for (int i = 0;i < SelectedCount;i++)
		if (SelectedComps[i] == pComp) return;

	SelectedComps[SelectedCount++] = pComp;
	pComp->SetSelected(true);
}

void ApplicationManager::RemoveFromSelection(Component* pComp) {
	for (int i = 0;i < SelectedCount;i++) {
		if (SelectedComps[i] == pComp) {
			pComp->SetSelected(false);
			for (int j = i;j < SelectedCount-1;j++)
				SelectedComps[j] = SelectedComps[j + 1];
			SelectedComps[SelectedCount - 1] = nullptr;
			SelectedCount--;
			return;
		
		}
	}
}

void ApplicationManager::ClearSelection()
{
	for (int i = 0; i < SelectedCount; i++)
		if (SelectedComps[i]) SelectedComps[i]->SetSelected(false);

	SelectedCount = 0;
}


int ApplicationManager::GetSelectedCount()const{
	return SelectedCount;
}

Component* ApplicationManager::GetSelectedCountAt(int index)const {
	if (index < 0 || index >= SelectedCount) return nullptr;
	return SelectedComps[index];
}

void ApplicationManager::SetClipboard(Component* pComp, bool cut) {
	ClipboardComp = pComp;
	IsCut = cut;
}

Component* ApplicationManager::GetClipboard() {
	return ClipboardComp;
}

bool ApplicationManager::GetIsCut()const {
	return IsCut;
}


//////////////////////////////////////////////////////////////////
void ApplicationManager::SelectComponentsInRect(int x1, int y1, int x2, int y2)
{
	ClearSelection(); // Clear previous selection

	for (int i = 0; i < CompCount; i++)
	{
		Component* comp = CompList[i];
		GraphicsInfo* gfx = comp->GetGraphicsInfo();

		// Select if the component overlaps the rectangle
		if (!(gfx->x2 < x1 || gfx->x1 > x2 || gfx->y2 < y1 || gfx->y1 > y2))
		{
			AddToSelection(comp);
		}
	}
}
////////////////////////////////////////////////////////////////////////


ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return InputInterface->GetUserAction(); 	
}
////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);	
			break;

		case ADD_OR_GATE_2:
			pAct = new AddORgate2(this);
			break;

		case ADD_NAND_GATE_2:
			pAct = new AddNANDgate2(this);
			break;

		case ADD_NOR_GATE_2:
			pAct = new AddNORgate2(this);
			break;

		case ADD_XOR_GATE_2:
			pAct = new AddXORgate2(this);
			break;

		case ADD_XNOR_GATE_2:
			pAct = new AddXNORgate2(this);
			break;

		case ADD_AND_GATE_3:
			pAct = new AddANDgate3(this);
			break;

		case ADD_NOR_GATE_3:
			pAct = new AddNORgate3(this);
			break;

		case ADD_XOR_GATE_3:
			pAct = new AddXORgate3(this);
			break;

		case ADD_Buff:
			pAct = new AddBUFFgate(this);
			break;

		case ADD_INV:
			pAct = new AddINVgate(this);
			break;

		case ADD_Switch:
			pAct = new AddSwitch(this);
			break;

		case ADD_LED:
			pAct = new AddLED(this);
			break;//TODO: Create AddLED Action here

		case DEL:
			pAct = new DeleteAction(this);
			break;

		case SELECT:
			pAct = new Select(this);
			break;

		case EDIT_Label:
			pAct = new Edit(this);
			break;

		case ADD_Label:
			pAct = new Label(this);
			break;
			
		case COPY:
			pAct = new Copy(this);
			break;

		case CUT:
			pAct = new Cut(this);
			break;



		case PASTE:
			pAct = new Paste(this);
			break;

		case ADD_CONNECTION:
			pAct = new AddConnection(this);
			break;

			// Handle switching between modes
		case SIM_MODE:
			// Switch to simulation mode and update toolbar
			UI.AppMode = SIMULATION;
			// Clear existing toolbar before drawing the simulation toolbar to avoid overlap
			OutputInterface->ClearToolBar();
			OutputInterface->CreateSimulationToolBar();
			break;

		case DSN_MODE:
			// Switch back to design mode and update toolbar
			UI.AppMode = DESIGN;
			// Clear existing toolbar before drawing the design toolbar to avoid overlap
			OutputInterface->ClearToolBar();
			OutputInterface->CreateDesignToolBar();
			break;

		case EXIT:
			///TODO: create ExitAction here
			break;
	}
	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
	OutputInterface->ClearDrawingArea();
		for(int i=0; i<CompCount; i++)
			CompList[i]->Draw(OutputInterface);

}

////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
	
}
int ApplicationManager::GetCompCount() const {
	return CompCount;
}

Component* ApplicationManager::GetComponent(int index) const {
	if (index >= 0 && index < CompCount)
		return CompList[index];
	return nullptr;
}
