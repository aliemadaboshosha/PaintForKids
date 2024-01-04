#define ACTION_PICK_TYPE_FIGURE_H

#include "..\Figures\CFigure.h"
#include "Action.h"

class ActionPickByType : public Action
{
	CFigure* Fig;
	Point p;
	int  no_figs, rand_fig_no, picked_fig_no, wrongSelect, rightSelect;
	int figs[5];
	void calcScore(int score);
	void GetShape();

public:
	ActionPickByType(ApplicationManager* pApp);
	virtual void Execute();
};