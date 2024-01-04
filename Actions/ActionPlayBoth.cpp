#include "ActionPlayBoth.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CEllipse.h"
#include  "..\Figures\CHexagon.h"

#include<string.h>
#include <iostream>

using namespace std;
ActionPlayBoth::ActionPlayBoth(ApplicationManager* pApp) :Action(pApp)
{
	gameTarget = 0;
	no_figs = 0;
	rightSelect = 0;
	wrongSelect = 0;



}
//Calculate the Score
void ActionPlayBoth::calcScore(int Score)
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	//print message for the player 
	string Message;

	if (Score == 1)
	{
		rightSelect++;
		Message = "Right!, Your score is: " + to_string(rightSelect) + " Right, and " + to_string(wrongSelect) + " Wrong.";
	}
	else if (Score == 2)
	{
		wrongSelect++;
		Message = "Wrong!, Your score is: " + to_string(rightSelect) + " Right, and " + to_string(wrongSelect) + " Wrong.";
	}
	else
	{
		if (rightSelect > wrongSelect)
		{
			Message = "Congratulations You win!, Your score is : " + to_string(rightSelect) + " Right, and : " + to_string(wrongSelect) + " Wrong.";
		}
		else if (rightSelect == wrongSelect && rightSelect != 0)
		{
			Message = "Try again it's Draw!, Your score is : " + to_string(rightSelect) + " Right, and : " + to_string(wrongSelect) + " Wrong.";
		}
		else
		{
			Message = "Hard Luck,Try again!, Your score is : " + to_string(rightSelect) + " Right, and : " + to_string(wrongSelect) + " Wrong.";
		}

	}

	pGUI->PrintMessage(Message);

}



string ActionPlayBoth::GetFigureType(CFigure* figure)
{
	string typeOfFigure = "";

	if (dynamic_cast<CSquare*>(figure))
	{
		typeOfFigure = "Squares";
	}
	else if (dynamic_cast<CEllipse*>(figure))
	{
		typeOfFigure = "Ellipses";

	}

	else if (dynamic_cast<CHexagon*>(figure))
	{
		typeOfFigure = "Hexagon";

	}
	return typeOfFigure;
}

string ActionPlayBoth::GetFigureColor(CFigure* figure)
{
	string colorOfFigure = "UNFILLED";
	if (figure->GetGfxInfo().isFilled)
	{


		if (figure->GetGfxInfo().FillClr == WHITE)
			colorOfFigure = "WHITE";
		if (figure->GetGfxInfo().FillClr == BLACK)
			colorOfFigure = "BLACK";
		else if (figure->GetGfxInfo().FillClr == BROWN)
			colorOfFigure = "BROWN";
		else if (figure->GetGfxInfo().FillClr == PURPLE)
			colorOfFigure = "PURPLE";
		else if (figure->GetGfxInfo().FillClr == PINK)
			colorOfFigure = "PINK";
		else if (figure->GetGfxInfo().FillClr == RED)
			colorOfFigure = "RED";
		else if (figure->GetGfxInfo().FillClr == ORANGE)
			colorOfFigure = "ORANGE";
		else if (figure->GetGfxInfo().FillClr == YELLOW)
			colorOfFigure = "YELLOW";
		else if (figure->GetGfxInfo().FillClr == GREEN)
			colorOfFigure = "GREEN";
		else if (figure->GetGfxInfo().FillClr == BLUE)
			colorOfFigure = "BLUE";
	}
	return colorOfFigure;

}


void ActionPlayBoth::GetTargetfigureCount(CFigure* target)
{
	for (int i = 0; i < pManager->getFigCount(); i++)
	{
		CFigure* Currentfig = pManager->DrawnFigs(i);

		if ((GetFigureType(target) == GetFigureType(Currentfig)) && (GetFigureColor(target) == GetFigureColor(Currentfig)))
		{
			gameTarget++;
		}

	}
}


//Execute the action
void ActionPlayBoth::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	/*pGUI->ClearStatusBar();*/


	if (pManager->getFigCount() > 1)
	{
		CFigure* clickedFig;
		// get random number in the range 0 to figCount
		rand_fig_no = rand() % pManager->getFigCount();
		Fig = pManager->DrawnFigs(rand_fig_no);
		cout << (rand() % pManager->getFigCount()) << endl;
		string colorOfFigure = GetFigureColor(Fig);


		string typeOfFigure = GetFigureType(Fig);




		pGUI->PrintMessage("Pick up all the " + typeOfFigure + " with color " + colorOfFigure);


		GetTargetfigureCount(Fig);



		while (gameTarget > 0)  //picked_fig_no->by3rf ba2y kam figure to select to win or lose
		{
			pGUI->GetPointClicked(p.x, p.y);
			if (p.y > UI.ToolBarHeight || p.x > (UI.MenuItemWidth * PLAY_ITM_COUNT))
			{
				clickedFig = pManager->GetFigure(p.x, p.y);

				if (clickedFig != NULL && clickedFig->HiddenStatus() == false)
				{

					if ((GetFigureType(Fig) == GetFigureType(clickedFig)) && (GetFigureColor(Fig) == GetFigureColor(clickedFig)))
					{
						calcScore(1);
						clickedFig->Hide();
						pGUI->ClearDrawArea();
						pManager->UpdateInterface();

						gameTarget--;
					}
					else
					{
						calcScore(2);
						clickedFig->Hide();
						pGUI->ClearDrawArea();
						pManager->UpdateInterface();

					}

				}
			}
			else
			{
				gameTarget = -1;
				pGUI->ClearStatusBar();
			}
		}
		// end the clicked
		if (gameTarget == 0)
		{
			calcScore(3);
		}
	}

	else
	{
		pGUI->PrintMessage("You must have at least two colored types of figures to start this game ! ");
	}

	for (int i = 0; i < pManager->getFigCount(); i++)
	{
		pManager->DrawnFigs(i)->Show();
	}
	pManager->UpdateInterface();//display all seen with the figures array

}