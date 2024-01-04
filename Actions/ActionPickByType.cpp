#include "ActionPickByType.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CEllipse.h"
#include  "..\Figures\CHexagon.h"
using namespace std;
ActionPickByType::ActionPickByType(ApplicationManager* pApp) :Action(pApp)
{
	no_figs = 0;
	rightSelect = 0;
	wrongSelect = 0;

	for (int i = 0; i < 5; i++)
	{
		figs[i] = 0;		// set all figures with 0
	}

}
//Calculate the Score
void ActionPickByType::calcScore(int Score)
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
void ActionPickByType::GetShape()
{
	for (int i = 0; i < pManager->getFigCount(); i++)
	{
		Fig = pManager->DrawnFigs(i);
		if (dynamic_cast<CSquare*>(Fig))
			figs[0]++;   //figs-> array of figures in runtime for count figures, assign every index to a figure to check then ++ 
		else if (dynamic_cast<CEllipse*>(Fig))
			figs[1]++;
		else if (dynamic_cast<CHexagon*>(Fig))
			figs[2]++;
		
	}
	for (int i = 0; i < 5; i++)  //loop to know count of all figures 
	{
		if (figs[i] != 0)  //lw msh b zero +count, 3shan y3rf eh elshakel ele msh 3andy,helps for random figures
			no_figs++;
	}
}

//Execute the action
void ActionPickByType::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	/*pGUI->ClearStatusBar();*/

	GetShape();

	if (no_figs > 1)
	{
		CFigure* clickedFig;
		// get random number in the range 0 to figCount
		rand_fig_no = rand() % pManager->getFigCount();
		Fig = pManager->DrawnFigs(rand_fig_no);


		if (dynamic_cast<CSquare*>(Fig))
		{
			picked_fig_no = figs[0];
			pGUI->PrintMessage("Pick up all the Squares !");

		}
		else if (dynamic_cast<CEllipse*>(Fig))
		{
			picked_fig_no = figs[1];
			pGUI->PrintMessage("Pick up all the Ellipses !");
		}

		else if (dynamic_cast<CHexagon*>(Fig))
		{
			picked_fig_no = figs[2];
			pGUI->PrintMessage("Pick up all the Hexagon !");
		}
		
		while (picked_fig_no > 0)  //picked_fig_no->by3rf ba2y kam figure to select to win or lose
		{
			pGUI->GetPointClicked(p.x, p.y);
			if (p.y > UI.ToolBarHeight || p.x > (UI.MenuItemWidth * PLAY_ITM_COUNT))
			{
				clickedFig = pManager->GetFigure(p.x, p.y);//WHAT IS THIS?

				if (clickedFig != NULL&& clickedFig->HiddenStatus() == false)
				{

					if ((dynamic_cast<CSquare*>(clickedFig)) && (dynamic_cast<CSquare*>(Fig)))
					{
						calcScore(1);
						clickedFig->Hide();
						pGUI->ClearDrawArea();
						pManager->UpdateInterface();
						
						picked_fig_no--;
					}
					else if ((dynamic_cast<CEllipse*>(clickedFig)) && (dynamic_cast<CEllipse*>(Fig)))
					{
						calcScore(1);
						clickedFig->Hide();
						pGUI->ClearDrawArea();
						pManager->UpdateInterface();
						
						picked_fig_no--;
					}
					else if ((dynamic_cast<CHexagon*>(clickedFig)) && (dynamic_cast<CHexagon*>(Fig)))
					{
						calcScore(1);
						clickedFig->Hide();
						pGUI->ClearDrawArea();
						pManager->UpdateInterface();
						
						picked_fig_no--;
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
				picked_fig_no = -1;
				pGUI->ClearStatusBar();
			}
		}
		// end the clicked
		if (picked_fig_no == 0)
		{
			calcScore(3);
		}
	}

	else
	{
		pGUI->PrintMessage("You must have at least two types of figures to play ! ");
	}

	for (int i = 0; i < pManager->getFigCount(); i++)
	{
		pManager->DrawnFigs(i)->Show();
	}
	pManager->UpdateInterface();

}