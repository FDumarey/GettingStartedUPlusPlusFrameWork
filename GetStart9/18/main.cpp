#include <CtrlLib/CtrlLib.h> // includes gui library

using namespace Upp;

#define IMAGECLASS Tray // defines the image class
#define IMAGEFILE  <GetStart9/18/tray.iml> // defines the image file
#include <Draw/iml.h> // imports the image designer library

struct App : TrayIcon { // inherits our app from the trayicon class
	void LeftDouble() override { // overrides double left click
		Icon(Tray::Icon1()); // switches the tray icon
		// show some ok dialog with text
		PromptOK("You double clicked the tray icon or clicked on menu item Info!"); 
		Icon(Tray::Icon()); // switches the tray icon back to original
	}
	
	void LeftDown() override { // overrides left click
		// show an OS information
		Info("Tray icon example", "You clicked on the tray icon\n""This is an information"); 
	}

	void Menu(Bar& bar) override { // adds a menu to the tray icon application
		// add an info bar that calls left double click
		bar.Add("Info..", [=] {LeftDouble();}); 
		bar.Separator(); // adds a menu separator
		bar.Add("Exit", [=] {Break();}); // adds a exit menu bar that exits the application
	}

	typedef App CLASSNAME; // defines app for callback functions

	App() { // the application constructor
		Icon(Tray::Icon()); // adds a initial icon to the tray icon application
		Tip("This is our Tray icon example"); // adds a tooltip to the tray icon
	}
};
 
GUI_APP_MAIN // gui main entry point
{
	App().Run(); // launches the application
}