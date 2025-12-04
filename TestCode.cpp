#include "GUI\Input.h"
#include "GUI\Output.h"

//This is a test code to test the Input and Output classes

int main()
{
	const int Y_OFFSET_GATE = 200;
	int x,y;

	//Create Input and Output objects to test
	Output *pOut = new Output();;
	Input *pIn = pOut->CreateInput();

	//Starting the test
	pOut->PrintMsg("This demo is to test input and output classes, Click anywhere to start the test");
	pIn->GetPointClicked(x,y);	//Wait for any click


	///////////////////////////////////////////////////////////////////////////////////
	// TEST 1:	Create The FULL Tool bar, the drawing area and the status bar	
	//			This has already been done through the constrcutor of class Output
	///////////////////////////////////////////////////////////////////////////////////

	pOut->PrintMsg("TEST1: Drawing Tool bar and Status bar, Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	
	///////////////////////////////////////////////////////////////////////////////////
	// TEST 2:	Drawing all the Components with all possible states: Normal, highlighted
	//			
	///////////////////////////////////////////////////////////////////////////////////
	
	pOut->PrintMsg("TEST2: Now we will show that Output class can draw any Component in any state, Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	GraphicsInfo GfxInfo;  //to be used with draw function of the class Ouput
	
	/// 2.1- AND2 Gate test
	pOut->PrintMsg("Drawing 2-input AND gate, Normal and Highlighted,  Click to continue");
	
	//Drawing Normal AND2 gate
	GfxInfo.x1 = 100;	GfxInfo.y1 = 100;
	pOut->DrawAND2(GfxInfo);

	//Drawing Highlighted AND2 gate
	GfxInfo.x1 = 100;	GfxInfo.y1 = 200;
	pOut->DrawAND2(GfxInfo, true);

	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawingArea();

	/// 2.2- NAND2 Gate test
	pOut->PrintMsg("Drawing 2-input NAND gate, Normal and Highlighted, Click to continue");

	// Drawing Normal NAND2 gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 100;
	pOut->DrawNAND2(GfxInfo, false);

	// Drawing Highlighted NAND2 gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 200;
	pOut->DrawNAND2(GfxInfo, true);

	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawingArea();


	/// 2.3- OR2 and NOR2 Gates test
	pOut->PrintMsg("Drawing 2-input OR and NOR gates, Normal and Highlighted, Click to continue");

	
	// Drawing Normal OR2 gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 100;
	pOut->DrawOR2(GfxInfo, false);

	// Drawing Highlighted OR2 gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 200;
	pOut->DrawOR2(GfxInfo, true);

	
	// Drawing Normal NOR2 gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 100 + Y_OFFSET_GATE; // Y=350
	pOut->DrawNOR2(GfxInfo, false);

	// Drawing Highlighted NOR2 gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 200 + Y_OFFSET_GATE; // Y=450
	pOut->DrawNOR2(GfxInfo, true);

	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawingArea();


	/// 2.4- XOR2 and XNOR2 Gates test
	pOut->PrintMsg("Drawing 2-input XOR and XNOR gates, Normal and Highlighted, Click to continue");

	
	// Drawing Normal XOR gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 100;
	pOut->DrawXOR(GfxInfo, false);

	// Drawing Highlighted XOR gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 200;
	pOut->DrawXOR(GfxInfo, true);


	// Drawing Normal XNOR2 gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 100 + Y_OFFSET_GATE; // Y=350
	pOut->DrawXNOR2(GfxInfo, false);

	// Drawing Highlighted XNOR2 gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 200 + Y_OFFSET_GATE; // Y=450
	pOut->DrawXNOR2(GfxInfo, true);

	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawingArea();


	/// 2.5- Buffer and Inverter Gates test
	pOut->PrintMsg("Drawing Buffer and Inverter Gates, Normal and Highlighted, Click to continue");

	
	// Drawing Normal Buffer gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 100;
	pOut->DrawBuff(GfxInfo, false);

	// Drawing Highlighted Buffer gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 200;
	pOut->DrawBuff(GfxInfo, true);

	
	// Drawing Normal Inverter gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 100 + Y_OFFSET_GATE; // Y=350
	pOut->DrawINV(GfxInfo, false);

	// Drawing Highlighted Inverter gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 200 + Y_OFFSET_GATE; // Y=450
	pOut->DrawINV(GfxInfo, true);

	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawingArea();


	/// 2.6- AND3, NOR3, and XOR3 Gates test
	pOut->PrintMsg("Drawing 3-input AND, NOR, and XOR Gates, Normal and Highlighted, Click to continue");

	
	// Drawing Normal AND3 gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 100;
	pOut->DrawAND3(GfxInfo, false);

	// Drawing Highlighted AND3 gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 200;
	pOut->DrawAND3(GfxInfo, true);

	
	// Drawing Normal NOR3 gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 100 + Y_OFFSET_GATE; 
	pOut->DrawNOR3(GfxInfo, false);

	// Drawing Highlighted NOR3 gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 200 + Y_OFFSET_GATE; 
	pOut->DrawNOR3(GfxInfo, true);

	// --- XOR3 ---
	// Drawing Normal XOR3 gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 100 + 2 * Y_OFFSET_GATE; 
	pOut->DrawXOR3(GfxInfo, false);

	// Drawing Highlighted XOR3 gate
	GfxInfo.x1 = 100; GfxInfo.y1 = 200 + 2 * Y_OFFSET_GATE;
	pOut->DrawXOR3(GfxInfo, true);

	pIn->GetPointClicked(x, y);	
	pOut->ClearDrawingArea();


	/// 2.7- Switch and LED test
	pOut->PrintMsg("Drawing Switch and LED, Normal and Highlighted, Click to continue");

	
	// Drawing Normal Switch
	GfxInfo.x1 = 100; GfxInfo.y1 = 100;
	pOut->DrawSwitch(GfxInfo, false);

	// Drawing Highlighted Switch
	GfxInfo.x1 = 100; GfxInfo.y1 = 200;
	pOut->DrawSwitch(GfxInfo, true);

		// Drawing Normal LED
	GfxInfo.x1 = 100; GfxInfo.y1 = 100 + Y_OFFSET_GATE; 
	pOut->DrawLED(GfxInfo, false);

	// Drawing Highlighted LED
	GfxInfo.x1 = 100; GfxInfo.y1 = 200 + Y_OFFSET_GATE;
	pOut->DrawLED(GfxInfo, true);

	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawingArea();


	/// 2.8- Connections
	pOut->PrintMsg("Drawing connections, Normal, Highlighted, straight, and broken,  Click to continue");
		
	
	const int X_START = 100;
	const int Y_START = 100;
	const int Y_OFFSET = 150;
	const int Y_SPACING = 250;

	// Straight Normal - Vertical
	GfxInfo.x1 = X_START; GfxInfo.y1 = Y_START;
	GfxInfo.x2 = X_START; GfxInfo.y2 = Y_START + 100;
	pOut->DrawConnection(GfxInfo, false);

	// Straight Normal - Horizontal
	GfxInfo.x1 = X_START; GfxInfo.y1 = Y_START + Y_OFFSET;
	GfxInfo.x2 = X_START + 200; GfxInfo.y2 = Y_START + Y_OFFSET;
	pOut->DrawConnection(GfxInfo, false);

	// Straight Highlighted - Vertical
	GfxInfo.x1 = X_START + 50; GfxInfo.y1 = Y_START;
	GfxInfo.x2 = X_START + 50; GfxInfo.y2 = Y_START + 100;
	pOut->DrawConnection(GfxInfo, true);

	// Straight Highlighted - Horizontal
	GfxInfo.x1 = X_START + 250; GfxInfo.y1 = Y_START + Y_OFFSET;
	GfxInfo.x2 = X_START + 450; GfxInfo.y2 = Y_START + Y_OFFSET;
	pOut->DrawConnection(GfxInfo, true);

	// 3. Orthogonal Path (Normal) 
	GfxInfo.x1 = X_START; GfxInfo.y1 = Y_START + Y_SPACING; 
	GfxInfo.x2 = X_START + 200; GfxInfo.y2 = Y_START + Y_SPACING + 100; 
	pOut->DrawConnection(GfxInfo, false);

	// 4. Orthogonal Path (Highlighted)
	GfxInfo.x1 = X_START + 250; GfxInfo.y1 = Y_START + Y_SPACING;
	GfxInfo.x2 = X_START + 450; GfxInfo.y2 = Y_START + Y_SPACING + 100;
	pOut->DrawConnection(GfxInfo, true);


	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->ClearDrawingArea();



	


	///////////////////////////////////////////////////////////////////////////////////
	// TEST 3: Read strings from the user
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMsg("TEST3: Now Time to test class Input, Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	
	pOut->PrintMsg("Testing Input ability to read strings");

	///TODO: Add code here to 
	// 1- Read a string from the user on the status bar and print it inside the drawing area

	string userText = pIn->GetSrting(pOut);
	pOut->DrawString(150, 150, userText);

	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawingArea();

	///////////////////////////////////////////////////////////////////////////////////
	// TEST 4: Check for the user action
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMsg("TEST4: Testing Input ability to detect User Action, click anywhere");

	ActionType ActType;
	
	///TODO:  You must add a case for each action
	//Add cases for the missing actions below
	do
	{
		ActType = pIn->GetUserAction();

		switch (ActType)
		{
		case ADD_Buff:
				pOut->PrintMsg("Action: add a buffer gate , Click anywhere");
				break;

		case ADD_INV:
				pOut->PrintMsg("Action: add an inverter gate , Click anywhere");
				break;

		case ADD_AND_GATE_2:
				pOut->PrintMsg("Action: add 2-input AND gate , Click anywhere");
				break;

		case ADD_NAND_GATE_2:
				pOut->PrintMsg("Action: add 2-input NAND gate , Click anywhere");
				break;

		case ADD_OR_GATE_2:
				pOut->PrintMsg("Action: add 2-input OR gate , Click anywhere");
				break;

		case ADD_NOR_GATE_2:
				pOut->PrintMsg("Action: add 2-input NOR gate , Click anywhere");
				break;

		case ADD_XOR_GATE_2:
				pOut->PrintMsg("Action: add 2-input XOR gate , Click anywhere");
				break;

		case ADD_XNOR_GATE_2:
				pOut->PrintMsg("Action: add 2-input XNOR gate , Click anywhere");
				break;

		case SELECT:
				pOut->PrintMsg("Action: a click on the Drawing area, Click anywhere");
				break;
			
		case STATUS_BAR:
				pOut->PrintMsg("Action: a click on the Status Bar, Click anywhere");
				break;
 
		case DSN_TOOL:
				pOut->PrintMsg("Action: a click on empty area in the Design Tool Bar, Click anywhere");
				break;

		case SIM_MODE:
				pOut->PrintMsg("Action: Switch to Simulation Mode, creating simualtion tool bar");
				pOut->ClearToolBar();
				pOut->CreateSimulationToolBar();
				break;

		case DSN_MODE:
				pOut->PrintMsg("Action: Switch to Design Mode, creating Design tool bar");
				pOut->CreateDesignToolBar();
				break;

		case ADD_AND_GATE_3:
			pOut->PrintMsg("Action: add 3-input AND gate, Click anywhere");
			break;

		case ADD_NOR_GATE_3:
			pOut->PrintMsg("Action: add 3-input NOR gate, Click anywhere");
			break;

		case ADD_XOR_GATE_3:
			pOut->PrintMsg("Action: add 3-input XOR gate, Click anywhere");
			break;

			
		case ADD_Switch:
			pOut->PrintMsg("Action: add Switch, Click anywhere");
			break;

		case ADD_LED:
			pOut->PrintMsg("Action: add LED, Click anywhere");
			break;

		case ADD_CONNECTION:
			pOut->PrintMsg("Action: add Wire Connection, Click anywhere");
			break;

			
		case ADD_Label:
			pOut->PrintMsg("Action: Add Label to component, Click anywhere");
			break;

		case EDIT_Label:
			pOut->PrintMsg("Action: Edit Label, Click anywhere");
			break;

		case DEL:
			pOut->PrintMsg("Action: Delete component/connection, Click anywhere");
			break;

		case MOVE:
			pOut->PrintMsg("Action: Move component, Click anywhere");
			break;

			
		case COPY:
			pOut->PrintMsg("Action: Copy component, Click anywhere");
			break;

		case CUT:
			pOut->PrintMsg("Action: Cut component, Click anywhere");
			break;

		case PASTE:
			pOut->PrintMsg("Action: Paste component, Click anywhere");
			break;

			
		case SAVE:
			pOut->PrintMsg("Action: Save Circuit to file, Click anywhere");
			break;

		case LOAD:
			pOut->PrintMsg("Action: Load Circuit from file, Click anywhere");
			break;

			
		case UNDO:
			pOut->PrintMsg("Action: Undo last action, Click anywhere");
			break;

		case REDO:
			pOut->PrintMsg("Action: Redo last action, Click anywhere");
			break;

		case Create_TruthTable:
			pOut->PrintMsg("Action: Create Truth Table, Click anywhere");
			break;

		case Change_Switch:
			pOut->PrintMsg("Action: Toggle Switch state, Click anywhere");
			break;
		case Simulation:
			pOut->PrintMsg("Action: simulating circuit, Click anywhere");
			break;
		case EXIT:				
				break;
		}
	}while(ActType != EXIT);


	/// Exiting
	pOut->PrintMsg("Action: EXIT, test is finished, click anywhere to exit");
	pIn->GetPointClicked(x,y);

	
	delete pIn;
	delete pOut;	
	return 0;
}


