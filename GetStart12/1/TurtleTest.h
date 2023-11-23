#ifndef _TurtleTest_TurtleTest_h
#define _TurtleTest_TurtleTest_h // header guard

#include <Turtle/Turtle.h> // includes the turtle library

namespace Upp {

class TurtleTest : public TopWindow { // inherits class from topwindow for our virtual gui

private:
	MenuBar menu; // adds a menubar
	StatusBar status; // adds a statusbar

	void FileMenu(Bar& bar); // the file menu function
	void MainMenu(Bar& bar); // the main menu function
	void About(); // the about function

public:
	TurtleTest(); // the constructor for the class
};

}
#endif