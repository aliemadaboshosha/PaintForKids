#include "ActionChangeBackground.h"

ActionChangeBackground::ActionChangeBackground(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionChangeBackground::Execute()
{
	Point P;
	int const itemsCount = 10;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	pGUI->PrintMessage("Please choose the background color");
	//Read point and store in point P
	if (!pGUI->GetPointClicked(P.x, P.y)) {
		pManager->SetPoint(P.x, P.y);
		return;
	}




	if (P.y < UI.ToolBarHeight * (itemsCount + 1) && P.x < UI.MenuItemWidth)
	{
		int colorOrder = (P.y - UI.ToolBarHeight) / UI.ToolBarHeight;
		switch (colorOrder)
		{
				case 0: pGUI->setCrntBackgroundColor(WHITE); break;
				case 1: pGUI->setCrntBackgroundColor(BLACK); break;
				case 2: pGUI->setCrntBackgroundColor(BROWN); break;
				case 3: pGUI->setCrntBackgroundColor(PURPLE); break;
				case 4: pGUI->setCrntBackgroundColor(PINK); break;
				case 5: pGUI->setCrntBackgroundColor(RED); break;
				case 6: pGUI->setCrntBackgroundColor(ORANGE); break;
				case 7: pGUI->setCrntBackgroundColor(YELLOW); break;
				case 8: pGUI->setCrntBackgroundColor(GREEN); break;
				case 9: pGUI->setCrntBackgroundColor(BLUE); break;

		}

	}
	else
	{
		pManager->ResetPoint();
		pGUI->PrintMessage("Please choose the BackGround color");

	}

	pGUI->ClearStatusBar();

	
	pManager->UpdateInterface();

}