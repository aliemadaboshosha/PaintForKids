#ifndef GUI_H
#define GUI_H

#include "..\DEFS.h"
#include "UI_Info.h" 
#include "..\CMUgraphicsLib\CMUgraphics.h"


//This class is responsible for Grphical User Interface handling
//All user input and program outputs MUST be done through this class
//No other class is allowed to perform direct i/o
class GUI	
{
public:	
	window* pWind;	//Pointer to the Graphics Window
public:
	GUI();	
	~GUI();	
	window* CreateWind(int, int, int , int) const; //creates the application window

	/////////// Input Functoinality  /////////////////
	bool GetPointClicked(int &x, int &y) const;//Get coordinate where user clicks
	bool GUI::IsButtonUp(int& x, int& y) const;

	string GetSrting() const ;	 //Returns a string entered by the user
	ActionType MapInputToActionType() const; //Read the user click and map to an action


	/////////// Output Functoinality  ////////////////
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar
	void CreateResizeToolBar() const;   //create the resize bar
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	void GUI::ClearToolBarArea() const; //Clear Tool bar area
	
	// -- Figures Drawing functions
	void DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected = false) const;  //Draw a Square
	void DrawEllipse(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const;  //Draw an Ellipse
	void DrawHexagon(Point P1, Point P2, GfxInfo HexGfxInfo, bool selected) const;

	///TODO: Make similar functions for drawing all other figures.
	
	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width
	void setCrntBKGrandColor(color c);
	bool GUI::getIsFilled() const;
	void GUI::setCrntDrawColor(color _color) const;	//set current drwawing color
	void GUI::setCrntFillColor(color _color, bool isFilled= true) const;	//set current fill color
	void GUI::setCrntBackgroundColor(color _color) const;	//set current background color


};


#endif