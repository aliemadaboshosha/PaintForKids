#include "ActionFillColor.h"

ActionFillColor::ActionFillColor(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionFillColor::Execute()
{
	Point P;
	int const itemsCount = 10;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	pGUI->PrintMessage("Please choose the fill color");
	//Read point and store in point P
	if (!pGUI->GetPointClicked(P.x, P.y)) {
		pManager->SetPoint(P.x, P.y);
		return;
	}

	if (P.y < UI.ToolBarHeight * (itemsCount+1) && P.x < UI.MenuItemWidth)
	{
		int colorOrder = (P.y - UI.ToolBarHeight) / UI.ToolBarHeight;
		switch (colorOrder)
		{
		case 0: pGUI->setCrntFillColor(WHITE); pManager->UpdateFigureFill(WHITE); break;
		case 1: pGUI->setCrntFillColor(BLACK); pManager->UpdateFigureFill(BLACK); break;
		case 2: pGUI->setCrntFillColor(BROWN); pManager->UpdateFigureFill(BROWN); break;
		case 3: pGUI->setCrntFillColor(PURPLE); pManager->UpdateFigureFill(PURPLE); break;
		case 4: pGUI->setCrntFillColor(PINK); pManager->UpdateFigureFill(PINK); break;
		case 5: pGUI->setCrntFillColor(RED); pManager->UpdateFigureFill(RED); break;
		case 6: pGUI->setCrntFillColor(ORANGE); pManager->UpdateFigureFill(ORANGE); break;
		case 7: pGUI->setCrntFillColor(YELLOW); pManager->UpdateFigureFill(YELLOW); break;
		case 8: pGUI->setCrntFillColor(GREEN); pManager->UpdateFigureFill(GREEN); break;
		case 9: pGUI->setCrntFillColor(BLUE); pManager->UpdateFigureFill(BLUE); break;
		}
	}
	else
		pManager->ResetPoint();

	pGUI->ClearStatusBar();
	pManager->UpdateInterface();
}