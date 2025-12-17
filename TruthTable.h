#pragma once
#include "Actions/Action.h"
#include "ApplicationManager.h"
#include "Components/Component.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include "../Project_Phase-2/LED.h"
#include "../Project_Phase-2/SWITCH.h"
#include "Components\Gate.h"
#include "Components\Connection.h"
#include <fstream>
#include <string>
//#include <queue>
using namespace std;

class TruthTable : public Action
{
	LED** mLeds;            // List of leds
	SWITCH** mSwitches;     // List of switches
	int* mSwitchesDefault;
	int mRows;                
	int mColumns;            
	int mSwitchesCount;        
	int mLedsCount;            
	window* pWind;            // Pointer to the graphical Window object
	bool mCanDraw;            // If you can write on window or not
	ofstream mWrite;        // txt file to write al truth table

public:
	TruthTable(ApplicationManager* pApp);
	virtual ~TruthTable();

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual void Undo() override { }
	virtual void Redo() override { }

};


