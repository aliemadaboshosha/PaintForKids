#include "ActionBringFront.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionBringFront::ActionBringFront(ApplicationManager* pApp) :Action(pApp)
{

}

void ActionBringFront::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	int selectedIndex = pManager->GetSelectedFigureIndex();
	if (selectedIndex != -1) {
		pManager->BringToFront(selectedIndex);
		pGUI->ClearDrawArea();
		pManager->UpdateInterface();

	}
	else {
		pGUI->PrintMessage("Select One Shape before you can perform this action");
	}
	pManager->ResetPoint();
}