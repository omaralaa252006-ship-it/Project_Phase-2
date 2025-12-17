//#include "Move.h"
//#include "ApplicationManager.h"
//#include "GUI/Output.h"
//#include "GUI/Input.h"
//#include "Components/Component.h"
//#include "Select.h"
//
//Move::Move(ApplicationManager* pApp) : Action(pApp) {
//
//}
//Move::~Move(void) {
//
//}
//void Move::ReadActionParameters() {
//
//	Output* pOut = pManager->GetOutput();
//	Input* pIn = pManager->GetInput();
//
//	//Print Action Message
//	pOut->PrintMsg("Click new location");
//	pIn->GetPointClicked(newX,newY);
//	pOut->ClearStatusBar();
//
//}
//void Move::Execute() {
//	if (isSelected()) 
//	Component* pComp = pManager->GetSelectedComponent();
//	if (!pComp)
//		return;
//	ReadActionParameters();
//
//	GraphicsInfo* pGfx = pComp->GetGraphicsInfo();
//	pGfx->x1 = newX;
//	pGfx->y1 = newY;
//}
//void Move::Undo(){}
//void Move::Redo(){}