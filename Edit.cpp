#include "Edit.h"
#include "ApplicationManager.h"
#include "Components/Component.h"

Edit::Edit(ApplicationManager* pApp) : Action(pApp) {

}
Edit::~Edit(void) {

}
void Edit::ReadActionParameters() {}
void Edit::Execute() {


	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	if (pManager->GetSelectedCount() != 1) {
		pManager->GetOutput()->PrintMsg("Select one Component to edit");
		return;
	}


	
	Component* pComp = pManager->GetSelectedCountAt(0);
	if (!pComp)
		return;

	pOut->PrintMsg("Enter new label");
	string Newlabel = pIn->GetString(pOut);
	pOut->ClearStatusBar();

	pComp->SetLabel(Newlabel);

	pManager->UpdateInterface();
}

void Edit::Undo() {}
void Edit::Redo() {}