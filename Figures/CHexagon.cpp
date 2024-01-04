#include "CHexagon.h"
#include <fstream>
#include <iostream>
#include "..\ApplicationManager.h"
CHexagon::CHexagon(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	BottomRightCorner = P2;
	VerticalLen = abs(P1.y - P2.y);
	HorizentalLen = abs(P1.x - P2.x);


}
CHexagon::CHexagon() {};


void CHexagon::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawHexagon(TopLeftCorner, BottomRightCorner, FigGfxInfo, Selected);

}
void CHexagon::Resize(GUI* pGUI, float size)
{
    float newVerticalLen = VerticalLen * size;
    float newHorizontalLen = HorizentalLen * size;

    // Calculate the new bottom right corner based on the resizing factor
    int newBottomRightX = TopLeftCorner.x + newHorizontalLen;
    int newBottomRightY = TopLeftCorner.y + newVerticalLen;

    // Check if the resized hexagon will fit within the drawing area
    if (newBottomRightY > UI.height - UI.StatusBarHeight
        || newBottomRightX > UI.width
        || TopLeftCorner.x < 1)
    {
        pGUI->PrintMessage("Hexagon size will be more than Drawing Area");
    }
    // Check if the resized hexagon will be too small
    else if (newHorizontalLen < 10 || newVerticalLen < 10)
    {
        pGUI->PrintMessage("Hexagon size will be very small");
    }
    else
    {
        // Update the dimensions
        VerticalLen = newVerticalLen;
        HorizentalLen = newHorizontalLen;

        // Update the bottom right corner
        BottomRightCorner.x = TopLeftCorner.x + HorizentalLen;
        BottomRightCorner.y = TopLeftCorner.y + VerticalLen;
    }
}



bool CHexagon::insideFigure(int x, int y)
{
	int lengthx = abs(TopLeftCorner.x - BottomRightCorner.x);
	int lengthy = abs(TopLeftCorner.y - BottomRightCorner.y);

	int xCenter = (BottomRightCorner.x + TopLeftCorner.x) / 2;
	int yCenter = (BottomRightCorner.y + TopLeftCorner.y) / 2;

	int arrx[6] = { TopLeftCorner.x,TopLeftCorner.x + lengthx, TopLeftCorner.x + 1.5 * lengthx,TopLeftCorner.x + lengthx,TopLeftCorner.x,TopLeftCorner.x - 0.5 * lengthx };
	int arry[6] = { TopLeftCorner.y,TopLeftCorner.y,TopLeftCorner.y + 0.5 * lengthy,TopLeftCorner.y + lengthy,TopLeftCorner.y + lengthy,TopLeftCorner.y + 0.5 * lengthy };

	float areax1 = (0.5) * abs(x * (arry[0] - arry[1]) + arrx[0] * (arry[1] - y) + arrx[1] * (y - arry[0]));
	float areax2 = (0.5) * abs(x * (arry[1] - arry[2]) + arrx[1] * (arry[2] - y) + arrx[2] * (y - arry[1]));
	float areax3 = (0.5) * abs(x * (arry[2] - arry[3]) + arrx[2] * (arry[3] - y) + arrx[3] * (y - arry[2]));
	float areax4 = (0.5) * abs(x * (arry[3] - arry[4]) + arrx[3] * (arry[4] - y) + arrx[4] * (y - arry[3]));
	float areax5 = (0.5) * abs(x * (arry[4] - arry[5]) + arrx[4] * (arry[5] - y) + arrx[5] * (y - arry[4]));
	float areax6 = (0.5) * abs(x * (arry[5] - arry[0]) + arrx[5] * (arry[0] - y) + arrx[0] * (y - arry[5]));
	float areax = areax1 + areax2 + areax3 + areax4 + areax5 + areax6;

	float totalarea = lengthy * lengthx * 1.5;
	Area = totalarea;
	if (areax == totalarea)
		return true;
	else
		return false;

}
string CHexagon::GetFigureInfo()


{
	string DrawColor = pManager->getColorName(FigGfxInfo.DrawClr);
	string shapeInfo = "ID: " + to_string(ID) + " || Shape: HEXAGON || First Point: (" + to_string(TopLeftCorner.x) + ", " + to_string(TopLeftCorner.y) + ")" + " || Second Point: (" + to_string(BottomRightCorner.x) + ", " + to_string(BottomRightCorner.y) + ")" + " || Area:(" + to_string(Area) + ")" + " || Draw Color: " + DrawColor;
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

void CHexagon::Save(ofstream& File)
{
	File << "Hexagon\t"
		<< ID << "\t"
		<< TopLeftCorner.x << "\t"
		<< TopLeftCorner.y << "\t"
		<< BottomRightCorner.x << "\t"
		<< BottomRightCorner.y << "\t"
		<< ColorToString(FigGfxInfo.DrawClr) << "\t";
	if (this->FigGfxInfo.isFilled)
		File << this->ColorToString(this->FigGfxInfo.FillClr) << "\n";
	else
		File << "No-Fill-color\n";
}
void CHexagon::Load(ifstream& file)
{
	string temp;
	file >> this->ID >>
		this->TopLeftCorner.x >>
		this->TopLeftCorner.y >>
		this->BottomRightCorner.x >>
		this->BottomRightCorner.y;
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