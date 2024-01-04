#pragma once
#include "Action.h"
class ActionSwitchToPlayMode : public Action
{
public:
	ActionSwitchToPlayMode(ApplicationManager* pApp);
	void Execute();
};

