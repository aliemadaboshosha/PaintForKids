#pragma once
#include "Action.h"
class ActionDelete : public Action
{

public:
	ActionDelete(ApplicationManager* pApp);
	void Execute();
};