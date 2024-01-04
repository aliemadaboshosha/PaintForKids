#include "ActionPickByColor.h"
#include "..\ApplicationManager.h"
#include "..\CMUgraphicsLib\colors.cpp" 
#include "..\GUI\GUI.h"
#include "..\Figures\CEllipse.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CHexagon.h"
#include "..\Figures\CFigure.h"

#include "iostream"

ActionPickByColor::ActionPickByColor(ApplicationManager* pApp) :Action(pApp)
{
	no_colors = 0;
	rightSelect = 0;
	wrongSelect = 0;

	for (int i = 0; i < 9; i++)
	{
		colors[i] = 0;
	}
}

color ActionPickByColor::coloreSelected(CFigure* Fig)
{
	if (Fig->GetGfxInfo().isFilled)
	{
		if (Fig->GetGfxInfo().FillClr == BLACK)
			return BLACK;
		else if (Fig->GetGfxInfo().FillClr == BROWN)
			return BROWN;
		else if (Fig->GetGfxInfo().FillClr == PURPLE)
			return PURPLE;
		else if (Fig->GetGfxInfo().FillClr == PINK)
			return PINK;
		else if (Fig->GetGfxInfo().FillClr == RED)
			return RED;
		else if (Fig->GetGfxInfo().FillClr == ORANGE)
			return ORANGE;
		else if (Fig->GetGfxInfo().FillClr == YELLOW)
			return YELLOW;
		else if (Fig->GetGfxInfo().FillClr == GREEN)
			return GREEN;
		else if (Fig->GetGfxInfo().FillClr == BLUE)
			return BLUE;
	}
	return WHITE;
}

//Calculate the Score
void ActionPickByColor::calcScore(int Score)
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

void ActionPickByColor::GetFilledShape()
{
	for (int i = 0; i < pManager->getFigCount(); i++) {
		Fig = pManager->DrawnFigs(i);

		// counting colors exists
		if (Fig->GetGfxInfo().isFilled)
		{
			
			if (Fig->GetGfxInfo().FillClr == BLACK)
				colors[0]++;
			else if (Fig->GetGfxInfo().FillClr == BROWN)
				colors[1]++;
			else if (Fig->GetGfxInfo().FillClr == PURPLE)
				colors[2]++;
			else if (Fig->GetGfxInfo().FillClr == PINK)
				colors[3]++;
			else if (Fig->GetGfxInfo().FillClr == RED)
				colors[4]++;
			else if (Fig->GetGfxInfo().FillClr == ORANGE)
				colors[5]++;
			else if (Fig->GetGfxInfo().FillClr == YELLOW)
				colors[6]++;
			else if (Fig->GetGfxInfo().FillClr == GREEN)
				colors[7]++;
			else if (Fig->GetGfxInfo().FillClr == BLUE)
				colors[8]++;
		}
		else
		{
			colors[9]++;
		}
	}

	for (int i = 0; i < 9; i++)
		if (colors[i] != 0)
		{
			no_colors++;
		}
}

//Execute the action
void ActionPickByColor::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	/*pGUI->ClearStatusBar();*/

	GetFilledShape();

	if (no_colors > 1)
	{
		CFigure* clickedFig;
		// get random number in the range 0 to figCount
		rand_fig_no = rand() % pManager->getFigCount();
		Fig = pManager->DrawnFigs(rand_fig_no);


		if (Fig->GetGfxInfo().isFilled)
		{
			if (Fig->GetGfxInfo().FillClr == BLACK)
			{
				picked_color_no = colors[0];
				pGUI->PrintMessage("Pick all BLACK shapes !");
			}
			else if (Fig->GetGfxInfo().FillClr == BROWN)
			{
				picked_color_no = colors[1];
				pGUI->PrintMessage("Pick all BROWN shapes !");
			}
			else if (Fig->GetGfxInfo().FillClr == PURPLE)
			{
				picked_color_no = colors[2];
				pGUI->PrintMessage("Pick all PURPLE shapes !");
			}
			else if (Fig->GetGfxInfo().FillClr == PINK)
			{
				picked_color_no = colors[3];
				pGUI->PrintMessage("Pick all PINK shapes !");
			}
			else if (Fig->GetGfxInfo().FillClr == RED)
			{
				picked_color_no = colors[4];
				pGUI->PrintMessage("Pick all RED shapes !");
			}
			else if (Fig->GetGfxInfo().FillClr == ORANGE)
			{
				picked_color_no = colors[5];
				pGUI->PrintMessage("Pick all ORANGE shapes !");
			}
			else if (Fig->GetGfxInfo().FillClr == YELLOW)
			{
				picked_color_no = colors[6];
				pGUI->PrintMessage("Pick all YELLOW shapes !");
			}
			else if (Fig->GetGfxInfo().FillClr == GREEN)
			{
				picked_color_no = colors[7];
				pGUI->PrintMessage("Pick all GREEN shapes !");
			}
			else if (Fig->GetGfxInfo().FillClr == BLUE)
			{
				picked_color_no = colors[8];
				pGUI->PrintMessage("Pick all BLUE shapes !");
			}
		}
		else
		{
			picked_color_no = colors[9];
			pGUI->PrintMessage("Pick all UNFILLED shapes !");
		}

		while (picked_color_no > 0)
		{
			pGUI->GetPointClicked(p.x, p.y);

			if (p.y > UI.ToolBarHeight || p.x > (UI.MenuItemWidth * PLAY_ITM_COUNT))
			{
				clickedFig = pManager->GetFigure(p.x, p.y);
				if (clickedFig != NULL&& clickedFig->HiddenStatus() == false)
				{
					// unfilled shape
					if (!(Fig->GetGfxInfo().isFilled) && !(clickedFig->GetGfxInfo().isFilled))
					{
						calcScore(1);
						clickedFig->Hide();
						pGUI->ClearDrawArea();
						pManager->UpdateInterface();
						picked_color_no--;
					}

					// filled color with specific color
					else if (clickedFig->GetGfxInfo().isFilled && clickedFig->GetGfxInfo().FillClr == coloreSelected(Fig))
					{
						calcScore(1);
						clickedFig->Hide();
						pGUI->ClearDrawArea();
						pManager->UpdateInterface();
						picked_color_no--;
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
			else {
				picked_color_no = -1;
				pGUI->ClearStatusBar();
			}
		}
		// end the clicked
		if (picked_color_no == 0)
		{
			calcScore(3);
		}
	}

	else
	{
		pGUI->PrintMessage("You must have at least two types color of figures to play ! ");
	}

	for (int i = 0; i < pManager->getFigCount(); i++)
	{
		pManager->DrawnFigs(i)->Show();
	}
	pManager->UpdateInterface();


}