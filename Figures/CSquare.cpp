#include "CSquare.h"
#include <fstream>
#include <iostream>

CSquare::CSquare(Point P1, int len, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
}
CSquare::CSquare(){}
	

void CSquare::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawSquare(TopLeftCorner, length, FigGfxInfo, Selected);
	

}
void CSquare::Resize(GUI* pGUI, float size)
{
	float length_test = length;
	Point test1 = TopLeftCorner;
	Point test2;
	test2.x = test1.x + length;
	test2.y = test1.y + length;
	length_test *= size;
	test2.x = test1.x + length_test;
	test2.y = test1.y + length_test;

	if (test1.y < UI.ToolBarHeight || test2.y > UI.height - UI.StatusBarHeight
		|| test2.x > UI.width || test1.x < 1)
	{
		pGUI->PrintMessage("Square size will be more than Drawing Area");

	}
	else if (length_test < 20)
	{
		pGUI->PrintMessage("Square size will be very small");

	}
	else
	{
		TopLeftCorner = test1;
		length = length_test;
	}


}

bool CSquare::insideFigure(int x, int y)
{
	if (x >= TopLeftCorner.x && x <= (TopLeftCorner.x + length) && y >= TopLeftCorner.y && y <= (TopLeftCorner.y + length))
	{
		return true;
	}
	return false;
}

string CSquare::GetFigureInfo()

{
	string DrawColor = pManager->getColorName(FigGfxInfo.DrawClr);
	string shapeInfo = "ID: " + to_string(ID) + " || Shape: Square || First Point: (" + to_string(TopLeftCorner.x) + ", " + to_string(TopLeftCorner.y) + ")" + " || Side Length: " + to_string(length) + " || Area: " + to_string(length * length) + " Draw Color: " + DrawColor;

	if (FigGfxInfo.isFilled)
		if (FigGfxInfo.isFilled)
		{
			string fillColor = pManager->getColorName(FigGfxInfo.FillClr);
			shapeInfo += " || Filled || Fill Color: " + fillColor;
		}
		else {
			shapeInfo += " || NO FILL";
		}

	return shapeInfo;
}

void CSquare::Save(ofstream& File)
{
	File << "Square\t"
		<< ID << "\t"
		<< TopLeftCorner.x << "\t"
		<< TopLeftCorner.y << "\t"
		<< length << "\t"
		<< ColorToString(FigGfxInfo.DrawClr) << "\t";
	if (this->FigGfxInfo.isFilled)
		File << this->ColorToString(this->FigGfxInfo.FillClr) << "\n";
	else
		File << "No-Fill-color\n";
}

void CSquare::Load(ifstream& file)
{
	string temp;
	file >> this->ID >>
		this->TopLeftCorner.x >>
		this->TopLeftCorner.y >>
		this->length;
	file >> temp;
	this->FigGfxInfo.DrawClr = StringToColor(temp);
	file >> temp;
	if (temp == "No-Fill-color") {
		this->FigGfxInfo.isFilled = false;
	}
	else
	{
		this->FigGfxInfo.FillClr = StringToColor(temp);
		this->FigGfxInfo.isFilled = true;
		cout << "fail";
	}
	this->Selected = false;
	this->FigGfxInfo.BorderWdth = 3;
}

string CSquare::getShapeType()
{
	return "Square";
}

