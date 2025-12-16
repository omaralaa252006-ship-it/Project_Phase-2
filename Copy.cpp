#include "Copy.h"
#include "GUI/Input.h"
#include "GUI/Output.h"
#include "ApplicationManager.h"
#include "Components/Component.h"

Copy::Copy(ApplicationManager* pApp) : Action(pApp)
{
}
Copy::~Copy(){}

void Copy::ReadActionParameters()
{
    // No parameters to read for copy action
}

void Copy::Execute()
{
	if (pManager->GetSelectedCount() != 1) {
		pManager->GetOutput()->PrintMsg("Select one Component to copy");
		return;
	}
	
	Component* pComp = pManager->GetSelectedCountAt(0);
	if (pComp)
		pManager->SetClipboard(pComp->clone(), false);
	pManager->GetOutput()->PrintMsg("Component copied");

	pManager->UpdateInterface();
}

void Copy::Undo() {}
void Copy::Redo() {}