#pragma once
#define ACTION_PICK_TYPE_FIGURE_H

#include "..\Figures\CFigure.h"
#include "Action.h"

class ActionPlayBoth : public Action
{

	CFigure* Fig;
	Point p;
	int  no_figs, rand_fig_no, wrongSelect, rightSelect, gameTarget;
	void calcScore(int);
	void GetTargetfigureCount(CFigure*);
	string GetFigureType(CFigure*);
	string GetFigureColor(CFigure*);


public:
	ActionPlayBoth(ApplicationManager* pApp);
	virtual void Execute();
};