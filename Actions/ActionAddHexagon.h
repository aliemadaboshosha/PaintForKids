#ifndef ACTION_ADD_Hexagon_H
#define ACTION_ADD_Hexagon_H

#include "Action.h"


class ActionAddHexagon : public Action
{
public:
	ActionAddHexagon(ApplicationManager* pApp);

	//Add ellipse to the ApplicationManager
	virtual void Execute();

};


#endif