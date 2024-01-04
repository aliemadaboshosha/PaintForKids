#pragma once

#ifndef CELLIPSE_H
#define CELLIPSE_H

#include "CFigure.h"
#include "..\ApplicationManager.h"
class CEllipse :public CFigure
{
private:
	Point P1, P2;

public:
	ApplicationManager* pManager = NULL;	//Actions needs AppMngr to do their job

	CEllipse(Point, Point, GfxInfo FigureGfxInfo);
	CEllipse();
	virtual void DrawMe(GUI* pOut) const;
	virtual void Resize(GUI* pGUI, float size) ;
	bool insideFigure(int x, int y);
	string GetFigureInfo();
	void Save(ofstream& File);
	void Load(ifstream& file);


};
#endif