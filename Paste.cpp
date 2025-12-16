#include "Paste.h"
#include "GUI/Input.h"
#include "GUI/Output.h"
#include "ApplicationManager.h"

Paste::Paste(ApplicationManager* pApp) : Action(pApp)
{
}
Paste::~Paste(){}

void Paste::ReadActionParameters()
{
    // Get a pointer to the input interface
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMsg("Click where you want to paste the component");

    // Get the clicked point
    pIn->GetPointClicked(Px,Py);

    pOut->ClearStatusBar();
}

void Paste::Execute()
{
    Component* clip = pManager->GetClipboard();
    if (!clip) {
        pManager->GetOutput()->PrintMsg("Clipbooard is empty");
        return;
    }
    ReadActionParameters();

    Component* newComp = clip->clone();
    GraphicsInfo* gfx = newComp->GetGraphicsInfo();
    int dx = gfx->x2 - gfx->x1;
    int dy = gfx->y2 - gfx->y1;

    gfx->x1 = Px;
    gfx->y1 = Py;
    gfx->x2 = Px+dx;
    gfx->y2 = Py+dy;

    pManager->AddComponent(newComp);
    pManager->ClearSelection();
    pManager->AddToSelection(newComp);
    pManager->GetOutput()->PrintMsg("Component pasted");
    pManager->UpdateInterface();
}

void Paste::Undo() {}
void Paste::Redo() {}