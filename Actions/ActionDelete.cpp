#include "ActionDelete.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include "string.h"
#include "iostream"

using namespace std;


ActionDelete::ActionDelete(ApplicationManager* pApp) :Action(pApp)
{}

void ActionDelete::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	//Print message to the user
	pGUI->PrintMessage("Are you sure you want to Delete this figure? (y/n)");

	// get the user answer
	string answer = pGUI->GetSrting();

	//check if answer is yes or no
	if (answer == "y" || answer == "Y")
	{
		pManager->Deleteselected();
	}
	else
	{
		pGUI->PrintMessage("Delete not excuted your figures are safe");
		return;
	}

	pGUI->ClearStatusBar(); // clear Status bar

	pGUI->ClearDrawArea(); //Clear all figures
}