#include "ActionSwitchToDrawMode.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionSwitchToDrawMode::ActionSwitchToDrawMode(ApplicationManager* pApp):Action(pApp)
{}

	void ActionSwitchToDrawMode::Execute()
	{

		GUI* pGUI = pManager->GetGUI();
		UI.InterfaceMode = MODE_DRAW;
		pGUI->CreateDrawToolBar();
		pGUI->PrintMessage("Welcome Back To Draw Mode");

	}
/*
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("");

	if (pManager->GetSelectedCount())
	{
		ActionType pAct;
			pGUI->CreatePlayToolBar();
			UI.InterfaceMode = MODE_PLAY;
	}
	else
	{
		pGUI->PrintMessage("there isn't a selected figure.. Please Select :)");
	}
}


*/