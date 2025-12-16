#include "DeleteAction.h"
#include "ApplicationManager.h"
#include "Components/Component.h"
#include "GUI/Output.h"

DeleteAction::DeleteAction(ApplicationManager* pApp) : Action(pApp) {

}
DeleteAction::~DeleteAction() {

}

void DeleteAction::ReadActionParameters()
{
    // Nothing needed for delete
}
/*
void DeleteAction::Execute()
{
    Output* pOut = pManager->GetOutput();

    int selectedCount = pManager->GetSelectedCount();
    if (selectedCount == 0)
    {
        pOut->PrintMsg("No components selected to delete");
        return;
    }

    // Delete all selected components
    Component* temp[90];
    for (int i = 0;i < selectedCount;i++) // iterate backward to avoid shifting issues
    temp[i]= pManager->GetSelectedCountAt(i);

    for (int i = 0;i < selectedCount;i++)
    pManager->DeleteComponent(temp[i]);
        
	pManager->ClearSelection();
	pManager->UpdateInterface();
    pOut->PrintMsg("Selected components are deleted");

	}
    */

void DeleteAction::Execute()
{
    Output* pOut = pManager->GetOutput();

    int selectedCount = pManager->GetSelectedCount();
    if (selectedCount == 0)
    {
        pOut->PrintMsg("No components selected to delete");
        return;
    }

    // Allocate exact-size array on the heap (avoid fixed-size stack buffer)
    Component** temp = new Component * [selectedCount];

    for (int i = 0; i < selectedCount; ++i)
        temp[i] = pManager->GetSelectedCountAt(i);

    for (int i = 0; i < selectedCount; ++i)
        pManager->DeleteComponent(temp[i]);

    delete[] temp; // free heap memory

    pManager->ClearSelection();
    pManager->UpdateInterface();
    pOut->PrintMsg("Selected components are deleted");
}



void DeleteAction::Undo(){}
void DeleteAction::Redo(){}


