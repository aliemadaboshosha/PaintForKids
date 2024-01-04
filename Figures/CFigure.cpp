#include "CFigure.h"

CFigure::CFigure(){
    figHidden = false;
}

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
    figHidden = false;
	ID = 0;

}


void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}

void CFigure::ChngFillStts(bool isFilled)
{
	FigGfxInfo.isFilled = isFilled;
}

void CFigure::SetID(int id)
{
	ID = id;
}

//Gets the figure ID

int CFigure::GetID() const
{
	return ID;
}
color CFigure::StringToColor(string s) {
   
    if (s == "GREEN")
        return GREEN;
    if (s == "BLUE")
        return BLUE;
    if (s == "WHITE")
        return WHITE;
    if (s == "PINK")
        return PINK;
    if (s == "YELLOW")
        return YELLOW;
    if (s == "ORANGE")
        return ORANGE;
    if (s == "MAROON")
        return MAROON;
    if (s == "PURPLE")
        return PURPLE;
    if (s == "RED")
        return RED;
    if (s == "BROWN")
        return BROWN;
    if (s == "RED")
        return RED;
    if (s == "ORANGE")
        return ORANGE;
    return BLACK;
}


string CFigure::ColorToString(color c)
{

    if ((c.ucBlue == BLACK.ucBlue) && (c.ucGreen == BLACK.ucGreen) && (c.ucRed == BLACK.ucRed))
        return "BLACK";
    if ((c.ucBlue == BROWN.ucBlue) && (c.ucGreen == BROWN.ucGreen) && (c.ucRed == BROWN.ucRed))
        return "BROWN";
    if ((c.ucBlue == PURPLE.ucBlue) && (c.ucGreen == PURPLE.ucGreen) && (c.ucRed == PURPLE.ucRed))
        return "PURPLE";
    if ((c.ucBlue == PINK.ucBlue) && (c.ucGreen == PINK.ucGreen) && (c.ucRed == PINK.ucRed))
        return "PINK";
    if ((c.ucBlue == RED.ucBlue) && (c.ucGreen == RED.ucGreen) && (c.ucRed == RED.ucRed))
        return "RED";
    if ((c.ucBlue == ORANGE.ucBlue) && (c.ucGreen == ORANGE.ucGreen) && (c.ucRed == ORANGE.ucRed))
        return "ORANGE";
    if ((c.ucBlue == YELLOW.ucBlue) && (c.ucGreen == YELLOW.ucGreen) && (c.ucRed == YELLOW.ucRed))
        return "YELLOW";
    if ((c.ucBlue == GREEN.ucBlue) && (c.ucGreen == GREEN.ucGreen) && (c.ucRed == GREEN.ucRed))
        return "GREEN";
    if ((c.ucBlue == BLUE.ucBlue) && (c.ucGreen == BLUE.ucGreen) && (c.ucRed == BLUE.ucRed))
        return "BLUE";
    return "NO-FILL";

}

void CFigure::Hide()
{
    figHidden = true;
}
//Gives Current Status
bool CFigure::HiddenStatus() const
{
    return figHidden;
}

//Shows Figures
void CFigure::Show()
{
    figHidden = false;
}
//esraa
GfxInfo CFigure::GetGfxInfo()
{
    return FigGfxInfo;
}
