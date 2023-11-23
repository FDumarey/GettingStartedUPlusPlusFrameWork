#include <CtrlLib/CtrlLib.h> // includes gui library

using namespace Upp;

GUI_APP_MAIN // gui entry point
{
	TopWindow AppWin; // defines a topwindow form application
	Button button; // defines a button
	button.SetLabel("End").HCenterPos().BottomPos(10); // sets a label and position
	button <<= AppWin.Breaker(); // assigns the breaker function to the button
	AppWin.Add(button); // adds the button object to the form
	AppWin.FullScreen().Run(); // runs the application in full screen
}