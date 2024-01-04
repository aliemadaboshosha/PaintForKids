#include "ActionSendBack.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionSendBack::ActionSendBack(ApplicationManager* pApp) :Action(pApp)
{

}

void ActionSendBack::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	int selectedIndex = pManager->GetSelectedFigureIndex();
	if (selectedIndex != -1) {
		pManager->SendToBack(selectedIndex);
		pGUI->ClearDrawArea();
		pManager->UpdateInterface();

	}
	else {
		pGUI->PrintMessage("Select One Shape before you can perform this action");
	}
	pManager->ResetPoint();
}