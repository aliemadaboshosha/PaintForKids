using namespace std;
#include "ApplicationManager.h"
#include <iostream>
#include "Actions/ActionAddSquare.h"
#include"Actions/ActionAddEllipse.h"
#include "Actions/ActionAddHexagon.h"
#include "Actions/ActionChangeColor.h"
#include"Actions/ActionFillColor.h"
#include "Actions\ActionChangeBackground.h"
#include"Actions/ActionSelect.h"
#include"Actions/ActionBringFront.h"
#include"Actions/ActionSendBack.h"
#include "Actions/ActionResize.h"
#include "Actions/ActionPickByType.h"
#include "Actions/ActionDelete.h"
#include "Actions/ActionSwitchToPlayMode.h"
#include "Actions/ActionSwitchToDrawMode.h"
#include "Actions\ActionSave.h"
#include "Actions\ActionLoad.h"
#include"Actions/ActionPlayBoth.h"
#include <string>
#include <string.h>
#include <iostream>
#include<sstream>
#include <iostream>
//Constructor
#include "Actions/ActionPickByColor.h"
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pGUI = new GUI;	
	
	FigCount = 0;
	x = y = -1;

	//initialise selectedCount to 0
	selectedCount = 0;
	selectedfigure = NULL;

		
	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
	{
		FigList[i] = NULL;
		SelectedFigures[i] = NULL;

	}
}

void ApplicationManager::Run()
{
	ActionType ActType;
	do
	{		
		//1- Read user action
		ActType = pGUI->MapInputToActionType();

		//2- Create the corresponding Action
		Action *pAct = CreateAction(ActType);
		
		//3- Execute the action
		ExecuteAction(pAct);

		//4- Update the interface
		UpdateInterface();	

	}while(ActType != EXIT);
	
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
//Creates an action
Action* ApplicationManager::CreateAction(ActionType ActType) 
{
	Action* newAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_SQUARE:
			newAct = new ActionAddSquare(this);
			break;
		case DRAW_ELPS:
			newAct = new ActionAddEllipse(this);
			break;
		case DRAW_HEX:
			newAct = new ActionAddHexagon(this);
			break;
		case CHNG_DRAW_CLR:
			newAct = new ActionChangeColor(this);
			break;
		case CHNG_FILL_CLR:
			newAct = new ActionFillColor(this);
			break;
		case CHNG_BK_CLR:
			newAct = new ActionChangeBackground(this);
			break;

		case SELECT:
			newAct = new ActionSelect(this);
			break; 
		case SAVE:
			newAct = new ActionSave(this, FigCount);
			break;
		case LOAD:
			newAct = new ActionLoad(this);
			break;
        
		case RESIZE:
			newAct = new Resize(this);
			break;
		case SEND_BACK:	//Send a figure to the back of all figures
			newAct = new ActionSendBack(this);
			break;
		case BRNG_FRNT: //Send a figure to the Front of all figures
			newAct = new ActionBringFront(this);
			break;
		case TO_PLAY:
			newAct = new ActionPickByType(this);
			break;
		case PLAY_COLOR:
			newAct = new ActionPickByColor(this);
			break;
		case PLAY_COLOR_TYPE :

			newAct = new ActionPlayBoth(this);
				break;
		case DEL:
			newAct = new ActionDelete(this);
			break;
		case EXIT:
			ExitMessage();
			break;
		case STATUS:	//a click on the status bar ==> no action
			return NULL;
			break;
		case TO_PLAY_MODE:
			newAct = new ActionSwitchToPlayMode(this);
			break;
		case TO_DRAW:
			newAct = new ActionSwitchToDrawMode(this);
			break;
		default:
			newAct = new ActionSelect(this);
			break;

	}	
	return newAct;
}
//////////////////////////////////////////////////////////////////////
//Executes the created Action
void ApplicationManager::ExecuteAction(Action* &pAct) 
{	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}

//Set x and y to coordinates of last selected menu action
void ApplicationManager::SetPoint(int _x, int _y)
{
	x = _x;
	y = _y;
}

void ApplicationManager::ResetPoint()
{
	x = y = -1;
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
		FigList[FigCount-1]->SetID(FigCount-1);
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i]->insideFigure(x, y)) {
			string shapeData = FigList[i]->GetFigureInfo();
			//pGUI->PrintMessage(shapeData);
			return FigList[i];
		}

	}

	return NULL;
}

void ApplicationManager::UpdateFigureColor(color _color) const //Update border color of selected figure(s)
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
			FigList[i]->ChngDrawClr(_color);
	}
}


void ApplicationManager::Deleteselected() //Delete Selected Figures
{
	for (int i = 0; i < FigCount; i++)
	{
		// delete the selected figures
		if (FigList[i]->IsSelected())
		{
			delete FigList[i];
			FigList[i] = NULL;
		}
	}
	// declare number of deleted figures variable
	int nDeleted = 0;

	// Shifting figures to the top of figure list
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] == NULL)
		{
			nDeleted++;
		}
		else
		{
			FigList[i - nDeleted] = FigList[i];
		}
	}

	// set repeated figures pointer to NULL;
	for (int i = nDeleted; i > 0; i--)
	{
		FigList[FigCount - i] = NULL;
	}

	// set figure count to the new value
	FigCount -= nDeleted;
}

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pGUI->ClearDrawArea();

	
	for (int i = 0; i < FigCount; i++) {
		
		if (FigList[i]->HiddenStatus())
		{
		}
		else {
			//cout << FigList[i]->HiddenStatus();
			FigList[i]->DrawMe(pGUI);
		}

	}
		
				//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the interface
GUI *ApplicationManager::GetGUI() const
{	return pGUI; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pGUI;
	
}

void ApplicationManager::UpdateFigureFill(color _color, bool isFilled) const //Update fill color of selected figure(s)
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			FigList[i]->ChngFillStts(isFilled);
			FigList[i]->ChngFillClr(_color);
		}
	}
}



//==================================================================================//
//								Select Functions		     						//
//==================================================================================//


//Returns the number of selected figures
int ApplicationManager::GetSelectedCount() const {
	return selectedCount;
}
////////////////////////////////////////////////////////////////////////////////////
//Returns a pointer to SelectedFigs array
CFigure* const* ApplicationManager::GetSelectedFigures() const {
	return SelectedFigures;
}

///////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::AddSelectedFigure(CFigure* sf) {

	SelectedFigures[selectedCount] = sf;
	selectedCount++;
}

void ApplicationManager::RemoveSelectedFigure(CFigure* sf) {

	for (int i = 0; i < selectedCount; i++) {
		if (SelectedFigures[i] == sf) {
			SelectedFigures[i] = SelectedFigures[selectedCount - 1];
			SelectedFigures[selectedCount - 1] = NULL;
			selectedCount--;

		}
	}
}
///  set selected figure For the select Action
void ApplicationManager::setselectedfigure(CFigure* pFig)
{
	selectedfigure = pFig;
}

CFigure* ApplicationManager::getselectedfigure() const
{
	return selectedfigure;
}


// Changing the Array Order to Send back and front
int ApplicationManager::GetSelectedFigureIndex() {
	int selectedFiguresCount = 0;
	int index = -1;

	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			index = i;
			selectedFiguresCount++;
		}
	}

	if (selectedFiguresCount == 1)
		return index;
	return -1;


}

void ApplicationManager::Resize_figure(GUI* pGUI, float size) const {
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			FigList[i]->Resize(pGUI, size);
		}
	}
}

void ApplicationManager::BringToFront(int index) {
	CFigure* SelectedFigure = FigList[index];
	for (int i = index; i < FigCount - 1; i++)
		FigList[i] = FigList[i + 1];

	FigList[FigCount - 1] = SelectedFigure;
}

void ApplicationManager::SendToBack(int index) {
	CFigure* SelectedFigure = FigList[index];
	for (int i = index; i > 0; i--)
		FigList[i] = FigList[i - 1];

	FigList[0] = SelectedFigure;
}

int ApplicationManager::getFigCount() const
{
	return FigCount;

}
//Transfer figures in FigList to playmode
CFigure* ApplicationManager::DrawnFigs(int i) const
{
	return FigList[i];
}
// exit
int ApplicationManager::ExitMessage()
{
	int msgboxID = MessageBox(
		NULL,
		"Do you want save before exite \n  Click ok to Save\n  Click cancel to leave without Save",
		"Exit",
		MB_OKCANCEL | MB_ICONWARNING
	);

	switch (msgboxID)
	{
	case IDCANCEL:
		exit(0);
		break;
	case IDOK:
		break;

	}
	//thia will execute the save and then exit immediatelly
	Action* newAct = new ActionSave(this,FigCount );
	ExecuteAction(newAct);
	return msgboxID;
}


//==================================================================================//
//						Save & Load Functions		     		                        //
//==================================================================================//


string ApplicationManager::colorToString(color c)
{
	cout << "color";
	std::ostringstream os;
	os << int(c.ucRed) << "\t";
	os << int(c.ucGreen) << "\t";
	os << int(c.ucBlue);

	std::string s = os.str();

	return s;
}

void ApplicationManager::SaveFile(ofstream& outputfile)
{

	for (int i = 0; i < FigCount; ++i)
	{
		cout << "nnnnnnn";
		FigList[i]->Save(outputfile);
	}



}//-----------

void ApplicationManager::deleteALLFig()
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i] = NULL;

	}

	FigCount = 0;

}

color ApplicationManager::stringToColor(string)
{
	return color();
}

/////////////////////////////////////////////////////////////////////////////////////////////

color ApplicationManager::getColorFromString(string s)
{
	if (s == "GREEN")
		return GREEN;
	if (s == "BLUE")
		return BLUE;
	if (s == "WHITE")
		return WHITE;
	if (s == "PINK")
		return PINK;
	if (s == "YELLOW")
		return YELLOW;
	if (s == "ORANGE")
		return ORANGE;
	if (s == "MAROON")
		return MAROON;
	if (s == "PURPLE")
		return PURPLE;
	if (s == "RED")
		return RED;
	if (s == "BROWN")
		return BROWN;
	if (s == "RED")
		return RED;
	if (s == "ORANGE")
		return ORANGE;
	return BLACK;
}

string ApplicationManager::getColorName(color c)
{
	if ((c.ucBlue == BLACK.ucBlue) && (c.ucGreen == BLACK.ucGreen) && (c.ucRed == BLACK.ucRed))
		return "BLACK";
	if ((c.ucBlue == BROWN.ucBlue) && (c.ucGreen == BROWN.ucGreen) && (c.ucRed == BROWN.ucRed))
		return "BROWN";
	if ((c.ucBlue == PURPLE.ucBlue) && (c.ucGreen == PURPLE.ucGreen) && (c.ucRed == PURPLE.ucRed))
		return "PURPLE";
	if ((c.ucBlue == PINK.ucBlue) && (c.ucGreen == PINK.ucGreen) && (c.ucRed == PINK.ucRed))
		return "PINK";
	if ((c.ucBlue == RED.ucBlue) && (c.ucGreen == RED.ucGreen) && (c.ucRed == RED.ucRed))
		return "RED";
	if ((c.ucBlue == ORANGE.ucBlue) && (c.ucGreen == ORANGE.ucGreen) && (c.ucRed == ORANGE.ucRed))
		return "ORANGE";
	if ((c.ucBlue == YELLOW.ucBlue) && (c.ucGreen == YELLOW.ucGreen) && (c.ucRed == YELLOW.ucRed))
		return "YELLOW";
	if ((c.ucBlue == GREEN.ucBlue) && (c.ucGreen == GREEN.ucGreen) && (c.ucRed == GREEN.ucRed))
		return "GREEN";
	if ((c.ucBlue == BLUE.ucBlue) && (c.ucGreen == BLUE.ucGreen) && (c.ucRed == BLUE.ucRed))
		return "BLUE";
	//if ((c.ucBlue == GREEN.ucBlue) && (c.ucGreen == GREEN.ucGreen) && (c.ucRed == GREEN.ucRed))
	//	return "GREEN";
	return "NO-FILL";
}
