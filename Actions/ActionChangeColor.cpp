#include "ActionChangeColor.h"

ActionChangeColor::ActionChangeColor(ApplicationManager* pApp) :Action(pApp)
{}




//Execute the action
void ActionChangeColor::Execute()
{
	Point P;
	int const itemsCount = 10;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	pGUI->PrintMessage("Please choose the border color");
	Sleep(1000);

	//Read point and store in point P
	if (!pGUI->GetPointClicked(P.x, P.y)) {
		pManager->SetPoint(P.x, P.y);
		return;
	}


	if (P.y < UI.ToolBarHeight * (itemsCount+1) && P.x < UI.MenuItemWidth )
	{
		int colorOrder = (P.y-UI.ToolBarHeight) / UI.ToolBarHeight;
		switch (colorOrder)
		{
		case 0: pGUI->setCrntDrawColor(WHITE); pManager->UpdateFigureColor(WHITE); break;
		case 1: pGUI->setCrntDrawColor(BLACK); pManager->UpdateFigureColor(BLACK); break;
		case 2: pGUI->setCrntDrawColor(BROWN); pManager->UpdateFigureColor(BROWN); break;
		case 3: pGUI->setCrntDrawColor(PURPLE); pManager->UpdateFigureColor(PURPLE); break;
		case 4: pGUI->setCrntDrawColor(PINK); pManager->UpdateFigureColor(PINK); break;
		case 5: pGUI->setCrntDrawColor(RED); pManager->UpdateFigureColor(RED); break;
		case 6: pGUI->setCrntDrawColor(ORANGE); pManager->UpdateFigureColor(ORANGE); break;
		case 7: pGUI->setCrntDrawColor(YELLOW); pManager->UpdateFigureColor(YELLOW); break;
		case 8: pGUI->setCrntDrawColor(GREEN); pManager->UpdateFigureColor(GREEN); break;
		case 9: pGUI->setCrntDrawColor(BLUE); pManager->UpdateFigureColor(BLUE); break;
		}

	}
	else
	{
		pManager->ResetPoint();
		pGUI->PrintMessage("Please choose the border color");

	}

	pGUI->ClearStatusBar();
	pManager->UpdateInterface();

}