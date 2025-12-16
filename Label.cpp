#include "Label.h"
#include "ApplicationManager.h"
#include "GUI/Output.h"
#include "GUI/Input.h"

Label::Label(ApplicationManager* pApp) : Action(pApp) {

}
Label::~Label() {

}
void Label::ReadActionParameters() {

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Enter label");
	LabelCom = pIn->GetString(pOut);
	pOut->ClearStatusBar();

}
void Label::Execute()
{
    if (pManager->GetSelectedCount() != 1)
    {
        pManager->GetOutput()->PrintMsg("Select one Component to label");
        return;
    }
    Component* pComp = pManager->GetSelectedCountAt(0);

    ReadActionParameters();   

    if (pComp)
        pComp->SetLabel(LabelCom);

    pManager->UpdateInterface();
}


void Label::Undo() {}
void Label::Redo() {}