#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY,	//Playing mode
	MODE_SIZE // Resize Mode
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_SQUR,		//Square item in menu
	ITM_ELPS,		//Ellipse item in menu
	ITM_HEXA,		//Hexagon item in menu
	ITM_CLR,		//OutLineColor
	ITM_FILL,		//inner color 
	ITM_BG,
	ITM_SELECT,		//SELECT item in menu
	ITM_RESIZE,
	//ITM_TO_PLAY,
	ITM_TO_PLAY_MODE,
	ITM_BACK,		//Send shape to back
	ITM_FRNT,		//Bring shape to front
	ITM_SAVE,
	ITM_LOAD,
	//ITM_PICK_COLOR,


	//TODO: Add more items names here
	ITM_DEL,		//delete with love

	ITM_EXIT,		//Exit item
	
	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};

enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	
	//TODO: Add more items names here
	ITM_Pick_By_TYPE,		// to selecte figure by type
	ITM_SELECT_FILL,		// to selecte figure by fill
	ITM_SELECT_Type_FILL,	// to selecte figure by fill and type
	ITM_SELECT2,
	ITM_SWICH_DRAW,			// switch item in menu
	ITM_EXIT2,				//Exit item
	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};
enum SizeMenuItem // The items of colors
{
	
	ITM_HALF,
	ITM_QUARTER,
	ITM_DOUBLE,
	ITM_QUADRUPLE,
	ITM_BACK2,
	SIZE_ITM_COUNT
};



__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;
	
	int	width, height,	//Window width and height
		wx , wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;		//Width of each item in toolbar menu
	
	bool isFilled;
	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes

	/// Add more members if needed
	
}UI;	//create a global object UI

#endif