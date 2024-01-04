#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\GUI.h"

//Base class for all figures
class CFigure
{
protected:
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	bool figHidden;
	

	/// Add more parameters if needed.

public:
	CFigure();
	CFigure(GfxInfo FigureGfxInfo);
	void SetSelected(bool );	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	bool HiddenStatus() const;

	virtual void DrawMe(GUI*) const  = 0 ;		//Draw the figure
	
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color
	void ChngFillStts(bool isFilled);
	virtual bool insideFigure(int, int) = 0; // select
	virtual string GetFigureInfo() = 0;	//print figure info on the status bar	//print all figure info on the status bar

	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	
	int CFigure::GetID() const;
	color StringToColor(string s);
	string ColorToString(color c);
	void CFigure::SetID(int id);
	virtual void Save(ofstream& OutFile) = 0;	//Save the figure parameters to the file
	virtual void Load(ifstream& Infile) = 0;	//Load the figure parameters to the file


	//virtual void Rotate() = 0;	//Rotate the figure
	virtual void Resize(GUI* pGUI, float size) = 0;
	//virtual void Move() = 0;		//Move the figure

	void Hide();
	void Show();
	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
	//esra
	GfxInfo CFigure::GetGfxInfo();
};

#endif