#include "select.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include "ApplicationManager.h"


Select::Select(ApplicationManager* pApp) : Action(pApp)
{
}
Select::~Select(){}
void Select::ReadActionParameters()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Select a Component");

    // read the point selected
    pIn->GetPointClicked(ClickedX,ClickedY);
    pOut->ClearStatusBar();
}
void Select::Execute()
{
    ReadActionParameters();

    Output* pOut = pManager->GetOutput();
    Component* clickedComp = pManager->GetComponentAt(ClickedX, ClickedY);

    if (clickedComp) {
        if (clickedComp->IsSelected()) {
            // Unselect
            pManager->RemoveFromSelection(clickedComp);
            pOut->PrintMsg("Component is unselected");
        }
        else {
            // Select
            pManager->AddToSelection(clickedComp);
            pOut->PrintMsg("Component is selected");
        }
    }
    else {
        pManager->ClearSelection();
        pOut->PrintMsg("All components are unselected");
    }

    pManager->UpdateInterface();
}

void Select::Undo() {}
void Select::Redo() {}