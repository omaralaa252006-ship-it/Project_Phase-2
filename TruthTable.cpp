#include "TruthTable.h"
#include "ApplicationManager.h"
#include "Components/Connection.h"
#include <cstring>
#include <sstream>

/* Constructor */
TruthTable::TruthTable(ApplicationManager* pAppMan) : Action(pAppMan) {
	mSwitchesCount = 0;
	mLedsCount = 0;
	mRows = 0;
	mColumns = 0;
	mSwitches = nullptr;
	mLeds = nullptr;
	mSwitchesDefault = nullptr;
	mWrite.open("TruthTable.txt");
	// clear file
	if (mWrite.is_open()) {
		mWrite.close();
	}
	mCanDraw = true;
}

TruthTable::~TruthTable() {
	if (mSwitches) delete [] mSwitches;
	if (mLeds) delete [] mLeds;
	if (mSwitchesDefault) delete [] mSwitchesDefault;
	if (mWrite.is_open()) mWrite.close();
}


void TruthTable::ReadActionParameters() // collect switches and leds from ApplicationManager
{
	
	int compCount = pManager->GetCompCount(); // find switches and leds among components
	mSwitchesCount = 0; // 1st count switches and leds
	mLedsCount = 0;
	for (int i = 0; i < compCount; ++i) {
		Component* c = pManager->GetComponent(i);
		// use (Runtime Type Information (RTTI)) via dynamic_cast
		SWITCH* s = dynamic_cast<SWITCH*>(c);
		LED* l = dynamic_cast<LED*>(c);
		if (s) ++mSwitchesCount;
		if (l) ++mLedsCount;
	}

	// allocate arrays
	if (mSwitches) delete [] mSwitches;
	if (mLeds) delete [] mLeds;
	if (mSwitchesDefault) delete [] mSwitchesDefault;

	if (mSwitchesCount > 0) {
		mSwitches = new SWITCH*[mSwitchesCount];
		mSwitchesDefault = new int[mSwitchesCount];
	} else {
		mSwitches = nullptr;
		mSwitchesDefault = nullptr;
	}
	if (mLedsCount > 0) {
		mLeds = new LED*[mLedsCount];
	} else {
		mLeds = nullptr;
	}

	// 2nd pass: fill them
	int si = 0, li = 0;
	for (int i = 0; i < compCount; ++i) {
		Component* c = pManager->GetComponent(i);
		SWITCH* s = dynamic_cast<SWITCH*>(c);
		LED* l = dynamic_cast<LED*>(c);
		if (s) {
			mSwitches[si] = s;
			// store default state (0 for LOW, 1 for HIGH)
			mSwitchesDefault[si] = (s->GetOutPinStatus() == HIGH) ? 1 : 0;
			++si;
		}
		if (l) {
			mLeds[li] = l;
			++li;
		}
	}

	mColumns = mSwitchesCount + mLedsCount;
}

////// evaluate the whole circuit by calling Operate on connections and components/ ////
static void EvaluateCircuit(ApplicationManager* pManager)
{
	
	int n = pManager->GetCompCount(); // call Operate() on every component in order
	for (int i = 0; i < n; ++i) {
		Component* c = pManager->GetComponent(i);
		c->Operate();
	}
}

// alfunction will generate truth table and display or save it
void TruthTable::Execute()
{
	
	ReadActionParameters(); // collect elements

	// no switches or leds -> show message
	Output* pOut = pManager->GetOutput();
	if (mSwitchesCount == 0) {
		pOut->PrintMsg("No switches in the circuit to generate truth table.");
		return;
	}

	// limit the display whichh is 5 inputs
	int maxDisplayInputs = 5;

	// total rows = 2^n
	int rows = 1;
	for (int i = 0; i < mSwitchesCount; ++i) rows *= 2;
	mRows = rows;

	bool saveToFile = (mSwitchesCount > maxDisplayInputs);
	if (saveToFile) {
		// open file for writing complete truth table
		mWrite.open("TruthTable.txt");
		if (!mWrite.is_open()) {
			pOut->PrintMsg("Failed to open TruthTable.txt for writing.");
			return;
		}
	}

	// prepare layout parameters
	int leftMargin = 20;
	int top = UI.ToolBarHeight + 10;
	int headerHeight = 20;
	int lineHeight = 18; // spacing between rows
	int colWidth = 60; // wider column width for readability

	// Print header to file if saving
	if (saveToFile) {
		// write switch labels
		for (int i = 0; i < mSwitchesCount; ++i) {
			string lbl = mSwitches[i]->GetLabel();
			if (lbl.empty()) lbl = string("S") + to_string(i+1);
			mWrite << lbl << "\t";
		}
		// write LED labels
		for (int j = 0; j < mLedsCount; ++j) {
			string lbl = mLeds[j]->GetLabel();
			if (lbl.empty()) lbl = string("L") + to_string(j+1);
			mWrite << lbl << "\t";
		}
		mWrite << "\n";
	}

	// If drawing on screen, draw header labels first
	if (!saveToFile) {
		int x = leftMargin;
		// Draw switch headers
		for (int i = 0; i < mSwitchesCount; ++i) {
			string lbl = mSwitches[i]->GetLabel();
			if (lbl.empty()) lbl = string("S") + to_string(i+1);
			pOut->DrawString(x, top, lbl);
			x += colWidth;
		}
		// Draw LED headers
		x += 10; // small gap between input and output columns
		for (int j = 0; j < mLedsCount; ++j) {
			string lbl = mLeds[j]->GetLabel();
			if (lbl.empty()) lbl = string("L") + to_string(j+1);
			pOut->DrawString(x, top, lbl);
			x += colWidth;
		}
		// move start of rows below header
		top += headerHeight + 4;
	}

	// iterate rows
	for (int r = 0; r < rows; ++r) {
		// set switches according to bits of r
		for (int s = 0; s < mSwitchesCount; ++s) {
			int bit = (r >> (mSwitchesCount - 1 - s)) & 1; // MSB first
			mSwitches[s]->setInputPinStatus(1, bit ? HIGH : LOW); // For SWITCH, setInputPinStatus expects input pin; SWITCH uses input pin 1
		}

		EvaluateCircuit(pManager);
		// collect LED outputs
		if (saveToFile) {
			for (int s = 0; s < mSwitchesCount; ++s) {
				mWrite << (((r >> (mSwitchesCount - 1 - s)) & 1) ? '1' : '0') << '\t';
			}
			for (int l = 0; l < mLedsCount; ++l) {
				int st = mLeds[l]->GetInputPinStatus(1);
				mWrite << (st == HIGH ? '1' : '0') << '\t';
			}
			mWrite << '\n';
		} else {
			int x = leftMargin;
			// draw switch values
			for (int s = 0; s < mSwitchesCount; ++s) {
				char buf[4];
				std::snprintf(buf, sizeof(buf), "%c", (((r >> (mSwitchesCount - 1 - s)) & 1) ? '1' : '0'));
				pOut->DrawString(x, top + r * lineHeight, string(buf));
				x += colWidth;
			}
			// gap between inputs and outputs
			x += 10;
			// draw LED values
			for (int l = 0; l < mLedsCount; ++l) {
				int st = mLeds[l]->GetInputPinStatus(1);
				char buf[4];
				std::snprintf(buf, sizeof(buf), "%c", (st == HIGH ? '1' : '0'));
				pOut->DrawString(x, top + r * lineHeight, string(buf));
				x += colWidth;
			}
		}
	}

	if (saveToFile) {
		mWrite.close();
		// Confirm via status bar with filename
		pOut->PrintMsg("Truth table written to TruthTable.txt");
	} else {
		pOut->PrintMsg("Truth table drawn on screen");
	}

	// restore switches to their original states
	for (int s = 0; s < mSwitchesCount; ++s) {
		mSwitches[s]->setInputPinStatus(1, mSwitchesDefault[s] ? HIGH : LOW);
	}

	// final update
	pManager->UpdateInterface();
}

