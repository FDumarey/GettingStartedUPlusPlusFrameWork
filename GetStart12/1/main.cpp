#include "TurtleTest.h" // includes header file

using namespace Upp;

TurtleTest::TurtleTest() // defines the constructor
{
	Sizeable().Zoomable(); // makes the window sizeable and zoomable
	Maximize(); // maximizes the window to the screen size
	Title("U++ Turtle window"); // sets the title of the window
	Icon(CtrlImg::Network()); // sets a icon to the window
	AddFrame(menu); // adds a menu frame
	AddFrame(status); // adds a status bar frame
	menu.Set([=](Bar& bar){MainMenu(bar);}); // links the callback function to the menu
	status = "Welcome to the Turtle engine of U++"; // sets status bar label field
}

void TurtleTest::About() // the about function
{
	// show dialog window
	PromptOK("{{1@5 [@9= This is the]::@2 [A5@0 U`+`+ Turtle web engine example}}"); 
}

void TurtleTest::FileMenu(Bar& bar) // when clicking on the file menu
{
	bar.Add("About..", [=] {About();}); // adds a menu item and its callback function
	bar.Separator(); // adds a separator to the menu
	bar.Add("Exit", [=] {Close();}); // adds a menu item and its callback function
}

void TurtleTest::MainMenu(Bar& bar) // defines the main menu
{
	bar.Sub("File", [=](Bar& bar) {FileMenu(bar);}); // adds a menu header and its callback function
}

void AppMainLoop() // the main loop for the web server
{
	// "Main" stuff should go in here...

	TurtleTest().Run(); // runs the GUI application, our self made class
}

CONSOLE_APP_MAIN // makes a console application, entry point
{

	// MemoryLimitKb(100000000); // Can aid preventing DDoS attacks.

	TurtleServer guiserver; // defines a turtleserver instance
	guiserver.Host("localhost"); // sets the host name of the web server
	guiserver.HtmlPort(8000); // sets the default web server TCP port
	guiserver.MaxConnections(100); // sets the maximum number of connections
	RunTurtleGui(guiserver, AppMainLoop); // runs the guiserver with the main loop function
}