#ifndef ACTION_CHANGE_FILL_H
#define ACTION_CHANGE_FILL_H

#include "Action.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"

//Change Fill Action class
class ActionFillColor : public Action
{
public:
	ActionFillColor(ApplicationManager* pApp);

	//Change fill of figure(s)
	virtual void Execute();

};

#endif