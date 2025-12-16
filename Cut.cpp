#include "Cut.h"
#include "ApplicationManager.h"
#include "GUI/Output.h"
#include "GUI/Input.h"
#include "Components/Component.h"

Cut::Cut(ApplicationManager* pApp) : Action(pApp) {}
Cut::~Cut(){}

void Cut::ReadActionParameters()
{

}

void Cut::Execute()
{
	if (pManager->GetSelectedCount() != 1) {
		pManager->GetOutput()->PrintMsg("Select one Component to cut");
		return;
	}

	Component* pComp = pManager->GetSelectedCountAt(0);
	if (pComp) {
		pManager->SetClipboard(pComp->clone(), true);
		pManager->DeleteComponent(pComp);
	}

	pManager->ClearSelection();
	pManager->UpdateInterface();
	pManager->GetOutput()->PrintMsg("Component cut");

}

void Cut::Undo() {}
void Cut::Redo() {}


