#ifndef ACTION_Resize
#define ACTION_Resize

#include "Action.h"
#include "ActionSelect.h"
#include "ActionAddSquare.h"

class Resize : public Action
{
public:
	Resize(ApplicationManager* pApp);

	//Add resize to the ApplicationManager
	virtual void Execute();
};
#endif