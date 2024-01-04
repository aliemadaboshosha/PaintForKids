#include "GUI.h"
#include "iostream"
using namespace std;


//constructor make necessary initializations
GUI::GUI()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1300;
	UI.height = 700;
	UI.wx = 5;
	UI.wy =5;

	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 50;
	
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = WHITE;		//Messages color
	UI.BkGrndColor = WHITE;	//Background color
	UI.HighlightColor = LIGHTGRAY;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 5;	//width of the figures frames

	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Project PD_MANS_INTAKE_44");
	
	CreateDrawToolBar();
	CreateStatusBar();
	//CreatePlayToolBar();
	
}


//======================================================================================//
//								Input Functions										    //
//======================================================================================//


bool GUI::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
	int MenuItemsCount;
	switch (UI.InterfaceMode) {
	case MODE_DRAW:
		MenuItemsCount = 19;
		break;
	case MODE_PLAY:
		MenuItemsCount = 5;
		break;
	}

	if (y > 0 && y < UI.ToolBarHeight && x > 0 && x < MenuItemsCount * UI.MenuItemWidth)
		return false;
	return true;
}



bool GUI::IsButtonUp(int& x, int& y) const
{
	return (pWind->GetButtonState(LEFT_BUTTON, x, y) == BUTTON_UP);	//Return true if left mouse button is up
}

string GUI::GetSrting() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if(Key == 8 )	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label+= Key;
		PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType GUI::MapInputToActionType() const
{
	//GUI::PrintExitAction();

	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_SQUR:return DRAW_SQUARE;
			case ITM_ELPS: return DRAW_ELPS;
			case ITM_HEXA:return DRAW_HEX;
			case ITM_CLR: return CHNG_DRAW_CLR;
			case ITM_FILL: return CHNG_FILL_CLR;
			case ITM_BG: return CHNG_BK_CLR;
			case ITM_SELECT: return SELECT;
			case ITM_BACK: return SEND_BACK;
			case ITM_FRNT: return BRNG_FRNT;
			case ITM_RESIZE:return RESIZE;
			//case ITM_TO_PLAY: return TO_PLAY;
			//case ITM_PICK_COLOR:return PLAY_COLOR;
			case ITM_TO_PLAY_MODE: return TO_PLAY_MODE;
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			case ITM_DEL: return DEL;
			case ITM_EXIT: return EXIT;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else if (UI.InterfaceMode == MODE_SIZE)
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			switch (ClickedItemOrder)
			{

			case ITM_HALF:
				return HALF;
			case ITM_QUARTER:
				return QUARTER;
			case ITM_DOUBLE:
				return DOUBLE1;
			case ITM_QUADRUPLE:
				return QUADRUPLE;
			case ITM_BACK2:
				return BACK2;

			}
		}


	}
	else	//GUI is in PLAY mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{

			case ITM_Pick_By_TYPE: return TO_PLAY;
			case ITM_SELECT_FILL: return PLAY_COLOR;
				
			case ITM_SELECT_Type_FILL: return 	PLAY_COLOR_TYPE;

			case ITM_SWICH_DRAW: return TO_DRAW;
			case ITM_SELECT2: return SELECT;
			case ITM_EXIT2: return EXIT;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

	}

	

}
//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white Square
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_SQUR] = "images\\MenuItems\\Menu_Sqr.jpg";
	MenuItemImages[ITM_ELPS] = "images\\MenuItems\\Menu_Elps.jpg";
	MenuItemImages[ITM_HEXA] = "images\\MenuItems\\MenuHexagon.jpg";
	MenuItemImages[ITM_CLR] = "images\\MenuItems\\MenuColor.jpg";
	MenuItemImages[ITM_FILL] = "images\\MenuItems\\MenuFill.jpg";
	MenuItemImages[ITM_BG] = "images\\MenuItems\\MenuBackground.jpg";
	MenuItemImages[ITM_SELECT] = "images\\MenuItems\\Menu_Select.jpg";
	MenuItemImages[ITM_RESIZE] = "images\\MenuItems\\resize.jpg";
	MenuItemImages[ITM_TO_PLAY_MODE] = "images\\MenuItems\\Playmode.jpg";
	
	MenuItemImages[ITM_BACK] = "images\\MenuItems\\MenuSendBack.jpg";
	MenuItemImages[ITM_FRNT] = "images\\MenuItems\\MenuBringFront.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";

	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\Save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\load.jpg";


	//TODO: Prepare images for each menu item and add it to the list
	MenuItemImages[ITM_DEL] = "images\\MenuItems\\Menu_Del.jpg";

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);


	int const itemsCount = 10;

	//Get a Pointer to the Interface

	//Prepare Color menu images directorys///////////////////////////////////////
	string ColorItemImages[itemsCount];
	for (int i = 1; i <= itemsCount; i++)
		sprintf(&ColorItemImages[i - 1][0], "images\\Colors\\%02d.jpg", i);

	//Draw Color menu items one image at a time
	pWind->DrawImage(&ColorItemImages[0][0], 0, 1 * UI.ToolBarHeight, UI.MenuItemWidth, UI.ToolBarHeight);

	for (int i = 1; i < itemsCount; i++)
		pWind->DrawImage(&ColorItemImages[i][0], 0, (i + 1) * UI.ToolBarHeight, UI.MenuItemWidth, UI.ToolBarHeight);
//////////////////////////////////////////////////////////////////////////////////////

	//Draw a line under the toolbar
	pWind->SetPen(GRAY, 1);
	pWind->DrawLine(0, UI.ToolBarHeight-1, UI.width, UI.ToolBarHeight-1);	


}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreatePlayToolBar() const
{
	ClearToolBarArea();
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[ITM_SELECT_FILL] = "images\\MenuItems\\byFill.jpg";
	MenuItemImages[ITM_Pick_By_TYPE] = "images\\MenuItems\\pick.jpg";
	MenuItemImages[ITM_SELECT_Type_FILL] = "images\\MenuItems\\Figure&Color.jpg";
	MenuItemImages[ITM_SWICH_DRAW] = "images\\MenuItems\\back.jpg";
	MenuItemImages[ITM_EXIT2] = "images\\MenuItems\\Menu_Exit.jpg";
	MenuItemImages[ITM_SELECT2] = "images\\MenuItems\\select_arrow.jpg";
	

	//Draw menu item one image at a time
	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

		//Draw a line under the toolbar
	pWind->SetPen(GRAY, 1);
	pWind->DrawLine(0, UI.ToolBarHeight - 1, UI.width, UI.ToolBarHeight - 1);


}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);



	//Prepare Color menu images directorys///////////////////////////////////////

	int const itemsCount = 10;
	string ColorItemImages[itemsCount];
	for (int i = 1; i <= itemsCount; i++)
		sprintf(&ColorItemImages[i - 1][0], "images\\Colors\\%02d.jpg", i);

	//Draw Color menu items one image at a time
	pWind->DrawImage(&ColorItemImages[0][0], 0, 1 * UI.ToolBarHeight, UI.MenuItemWidth, UI.ToolBarHeight);

	for (int i = 1; i < itemsCount; i++)
		pWind->DrawImage(&ColorItemImages[i][0], 0, (i + 1) * UI.ToolBarHeight, UI.MenuItemWidth, UI.ToolBarHeight);
	//////////////////////////////////////////////////////////////////////////////////////

	
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
bool GUI::getIsFilled() const {
	return UI.isFilled;
}////////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateResizeToolBar() const
{
	ClearToolBarArea();
	UI.InterfaceMode = MODE_SIZE;

	string MenuItemImages[SIZE_ITM_COUNT];
	MenuItemImages[ITM_HALF] = "images\\MenuItems\\Half.jpg";
	MenuItemImages[ITM_QUARTER] = "images\\MenuItems\\QX.jpg";
	MenuItemImages[ITM_DOUBLE] = "images\\MenuItems\\X2.jpg";
	MenuItemImages[ITM_QUADRUPLE] = "images\\MenuItems\\X4.jpg";
	MenuItemImages[ITM_BACK2] = "images\\MenuItems\\back.jpg";

	for (int i = 0; i < SIZE_ITM_COUNT; i++)
		for (int i = 0; i < SIZE_ITM_COUNT; i++)
			pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(CORNFLOWERBLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

void GUI::ClearToolBarArea() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}

color GUI::getCrntDrawColor() const	//get current drwawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::setCrntDrawColor(color _color) const	//set current drwawing color
{
	UI.DrawColor = _color;
}
//////////////////////////////////////////////////////////////////////////////////////////


color GUI::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::setCrntFillColor(color _color, bool isFilled) const	//set current fill color
{
	UI.isFilled = isFilled;
	UI.FillColor = _color;
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::setCrntBKGrandColor(color c) {
	UI.BkGrndColor = c;
}

void GUI::setCrntBackgroundColor(color _color) const	//set current background color
{
	UI.BkGrndColor = _color;
}
//////////////////////////////////////////////////////////////////////////////////////////

int GUI::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}




//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void GUI::DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
	{
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	}
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;



	pWind->DrawRectangle(P1.x, P1.y, P1.x + length, P1.y + length, style);

}

void GUI::DrawEllipse(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawEllipse(P1.x, P1.y, P2.x, P2.y, style);


}

void GUI::DrawHexagon(Point P1, Point P2, GfxInfo HexGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = HexGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, HexGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (HexGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(HexGfxInfo.FillClr);
	}
	else
		style = FRAME;

	int lengthx = abs(P1.x - P2.x);
	int lengthy = abs(P1.y - P2.y);

	int arrx[6] = { P1.x,P1.x + lengthx, P1.x + 1.5 * lengthx,P1.x + lengthx,P1.x,P1.x - 0.5 * lengthx };
	int arry[6] = { P1.y,P1.y,P1.y + 0.5 * lengthy,P1.y + lengthy,P1.y + lengthy,P1.y + 0.5 * lengthy };

	pWind->DrawPolygon(arrx, arry, 6, style);

}


//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

