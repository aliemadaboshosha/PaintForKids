#include "ActionSwitchToPlayMode.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionSwitchToPlayMode::ActionSwitchToPlayMode(ApplicationManager* pApp) :Action(pApp)
{}

void ActionSwitchToPlayMode::Execute()
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
