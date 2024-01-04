#include "ActionAddHexagon.h"
#include "..\Figures\CHexagon.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionAddHexagon::ActionAddHexagon(ApplicationManager* pApp) :Action(pApp)
{}
void ActionAddHexagon::Execute()
{
    Point P1, P2;

    // Get a Pointer to the Interface
    GUI* pGUI = pManager->GetGUI();

    GfxInfo HexGfxInfo;
    HexGfxInfo.isFilled = pGUI->getIsFilled(); // Default is not filled
    // Get drawing, filling colors, and pen width from the interface
    HexGfxInfo.DrawClr = pGUI->getCrntDrawColor();
    HexGfxInfo.FillClr = pGUI->getCrntFillColor();
    HexGfxInfo.BorderWdth = pGUI->getCrntPenWidth();

    // Step 1 - Read hexagon data from the user
    pGUI->PrintMessage("New Hexagon: Click at first point");

    // Read 1st point and store it in point P1
    if (!pGUI->GetPointClicked(P1.x, P1.y)) {
        pManager->SetPoint(P1.x, P1.y);
        return;
    }

    // Check if the first point is in the valid drawing area
    if (P1.y < UI.ToolBarHeight || P1.y > UI.height - UI.StatusBarHeight || P1.x < UI.MenuItemWidth) {
        pGUI->PrintMessage("Please choose a valid point.");
        return;
    }

    pGUI->PrintMessage("New Hexagon: Click at second point");

    // Read 2nd point and store it in point P2
    if (!pGUI->GetPointClicked(P2.x, P2.y)) {
        pManager->SetPoint(P2.x, P2.y);
        return;
    }

    // Check if the second point is in the valid drawing area
    if (P2.y < UI.ToolBarHeight || P2.y > UI.height - UI.StatusBarHeight || P2.x < UI.MenuItemWidth) {
        pGUI->PrintMessage("Please choose a valid point.");
        return;
    }

    pGUI->ClearStatusBar();

    // Step 2 - Prepare Hexagon data

   // Calculate the top-left and bottom-right corners of the hexagon
    Point topLeft;
    topLeft.x = P1.x < P2.x ? P1.x : P2.x;
    topLeft.y = P1.y < P2.y ? P1.y : P2.y;

    Point bottomRight;
    bottomRight.x = P1.x > P2.x ? P1.x : P2.x;

    // Adjust bottomRight.x to ensure it doesn't exceed the drawing area
    if (bottomRight.x > UI.width - UI.MenuItemWidth) {
        bottomRight.x = UI.width - UI.MenuItemWidth;
    }

    bottomRight.y = P1.y > P2.y ? P1.y : P2.y;

    // Check if any part of the hexagon goes beyond the drawing area
    if (topLeft.x < UI.MenuItemWidth || topLeft.y < UI.ToolBarHeight || bottomRight.y > UI.height - UI.StatusBarHeight) {
        pGUI->PrintMessage("Hexagon exceeds drawing area. Please choose a valid size.");
        return;
    }

    //حساب النقطة اقصى اليمين
    Point center;
    center.x = (topLeft.x + bottomRight.x) / 2;
    center.y = (topLeft.y + bottomRight.y) / 2;

    // Calculate the side length of the hexagon
    int sideLength = static_cast<int>(sqrt(pow(P2.x - P1.x, 2) + pow(P2.y - P1.y, 2)));

    // Calculate the right point of the hexagon
    Point rightPoint;
    rightPoint.x = center.x + sideLength;
    rightPoint.y = center.y;

    // Check if any part of the hexagon goes beyond the drawing area
    if (rightPoint.x > UI.width) {
        pGUI->PrintMessage("Hexagon exceeds drawing area. Please choose a valid size.");
        pGUI->ClearDrawArea();
        return;
    }


    // Step 3 - Create a Hexagon with the calculated corners and graphics information
    CHexagon* H = new CHexagon(topLeft, bottomRight, HexGfxInfo);

    // Step 4 - Add the Hexagon to the list of figures
    pManager->AddFigure(H);


}
