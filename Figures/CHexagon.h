
#ifndef CHexagon_H
#define CHexagon_H

#include "CFigure.h"
#include "..\ApplicationManager.h"

class CHexagon : public CFigure
{
private:
	Point TopLeftCorner;
	Point BottomRightCorner;
	int VerticalLen;
	int HorizentalLen;
public:
	ApplicationManager* pManager = NULL;	//Actions needs AppMngr to do their job
	int Area;
	CHexagon(Point, Point, GfxInfo FigureGfxInfo);
	CHexagon();
	virtual void DrawMe(GUI* pOut) const;
	void Resize(GUI* pGUI, float size); 
	bool insideFigure(int x, int y);
	string GetFigureInfo();
	void Save(ofstream& File);
	void Load(ifstream& file);
};

#endif
