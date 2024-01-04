#include "..\ApplicationManager.h"
#include "Action.h"
#include "..\GUI\GUI.h"
#include "ActionResize.h"
#include <iostream>

Resize::Resize(ApplicationManager* pApp) :Action(pApp)
{}

void Resize::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("");


	if (pManager->GetSelectedCount())
	{
		ActionType pAct;
		do {
			pGUI->CreateResizeToolBar();
			UI.InterfaceMode = MODE_SIZE;
			pAct = pGUI->MapInputToActionType();
			pGUI->PrintMessage("");
			switch (pAct) {

			case HALF:
				pGUI->ClearDrawArea();
				pManager->Resize_figure(pGUI, 0.5);
				pManager->UpdateInterface();
				break;
			case QUARTER:
				pGUI->ClearDrawArea();
				pManager->Resize_figure(pGUI, 0.25);
				pManager->UpdateInterface();
				break;
			case DOUBLE1:
				pGUI->ClearDrawArea();
				pManager->Resize_figure(pGUI, 2);
				pManager->UpdateInterface();
				break;
			case QUADRUPLE:
				pGUI->ClearDrawArea();
				pManager->Resize_figure(pGUI, 4);
				pManager->UpdateInterface();
				break;
			case BACK2:
				UI.InterfaceMode = MODE_DRAW;
				pGUI->CreateDrawToolBar();
				pGUI->PrintMessage("");
				break;
			}
		} while (pAct != BACK2);


	}//pGUI->CreateDrawToolBar();

	else
	{
		pGUI->PrintMessage("there isn't a selected figure.. Please Select :)");
		//Sleep(1000);
	}


	//pManager->setLastSaveState(false);
}