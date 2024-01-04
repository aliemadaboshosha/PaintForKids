#include "ActionAddSquare.h"
#include "..\Figures\CSquare.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionAddSquare::ActionAddSquare(ApplicationManager * pApp):Action(pApp)
{}

//Execute the action
void ActionAddSquare::Execute() 
{
	Point P1,P2;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo SqrGfxInfo;
	SqrGfxInfo.isFilled = pGUI->getIsFilled();	//default is not filled
	//get drawing, filling colors and pen width from the interface
	SqrGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	SqrGfxInfo.FillClr = pGUI->getCrntFillColor();
	SqrGfxInfo.BorderWdth = pGUI->getCrntPenWidth();

	/*while (true)
	{*/
		//Step 1 - Read Square data from the user
		pGUI->PrintMessage("New Square: Click at first point");
		//Read 1st point and store in point P1
	//Read 1st point and store in point P1
		if (!pGUI->GetPointClicked(P1.x, P1.y)) {
			pManager->SetPoint(P1.x, P1.y);
			return;
		}

		if (P1.y < UI.ToolBarHeight || P1.y > UI.height - UI.StatusBarHeight || P1.x < UI.MenuItemWidth)
		{
			bool flag = false; //false as long as the click is in wrong place
			pGUI->PrintMessage("Please, Choose a valid Point");
			while (!flag)
			{
				//pGUI->GetPointClicked(P1.x, P1.y); //Get Pasting Point
				if (!pGUI->GetPointClicked(P1.x, P1.y)) {
					pManager->SetPoint(P1.x, P1.y);
					return;
				}

				if (!(P1.y < UI.ToolBarHeight || P1.y > UI.height - UI.StatusBarHeight || P1.x < UI.MenuItemWidth))
					flag = 1;
			}
		}




		pGUI->PrintMessage("New Square: Click at second point");
		//Read 2nd point and store in point P2
		//pGUI->GetPointClicked(P2.x, P2.y);
		if (!pGUI->GetPointClicked(P2.x, P2.y)) {
			pManager->SetPoint(P2.x, P2.y);
			return;
		}

		if (P2.y < UI.ToolBarHeight || P2.y > UI.height - UI.StatusBarHeight || P2.x < 0)
		{
			bool flag = false; //false as long as the click is in wrong place
			pGUI->PrintMessage("Please, Choose a valid Point");
			while (!flag)
			{
				//pGUI->GetPointClicked(P2.x, P2.y);

				if (!pGUI->GetPointClicked(P2.x, P2.y)) {
					pManager->SetPoint(P2.x, P2.y);
					return;
				}

				if (!(P2.y < UI.ToolBarHeight || P2.y > UI.height - UI.StatusBarHeight || P2.x < 0))
					flag = 1;
			}
		}



		pGUI->ClearStatusBar();


		//Step 2 - prepare square data
		//User has entered two points P1&P2
		//2.1- Identify the Top left corner of the square
		Point topLeft;
		topLeft.x = P1.x < P2.x ? P1.x : P2.x;
		topLeft.y = P1.y < P2.y ? P1.y : P2.y;

		//2.2- Calcuate square side legnth
		//The square side length would be the longer distance between the two points coordinates
		int SideLength = max(abs(P1.x - P2.x), abs(P1.y - P2.y));

		if (P1.y + SideLength > UI.height - UI.StatusBarHeight ||
			P2.y + SideLength > UI.height - UI.StatusBarHeight ||
			P1.x + SideLength > UI.width || P2.x + SideLength > UI.width)
		{
			pGUI->PrintMessage("invalid");
			bool flag = true;
			return;
		}


		//Step 3 - Create a Square with the parameters read from the user
		CSquare* R = new CSquare(topLeft, SideLength, SqrGfxInfo);

		//Step 4 - Add the Square to the list of figures
		pManager->AddFigure(R);

}
