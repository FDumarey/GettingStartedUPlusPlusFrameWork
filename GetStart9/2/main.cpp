#include <CtrlLib/CtrlLib.h> // includes gui library

using namespace Upp;

struct MyApp : TopWindow{ // inherits a struct from TopWindow
	DropList font_list; // defines a droplist widget variable
	
	virtual void Paint(Draw& w) override { // overrides the paint event from TopWindow
		const String text = "Programming is fun!"; // defines a string variable
		Font fnt(~font_list, 60); // ~ operator = gets property of droplist, font size 60 pixels
		w.DrawRect(GetSize(),White); // makes the background white
		w.Offset(50,50); // sets an offset of 50 pixels horizontal and vertical
		int x=0; // sets x=0
		Vector<int> dx; // defines a collection of integers
		
		for (char letter : text) { // loops through all characters in the text variable
			int width = fnt[letter]; // [] operator gets letter width
			// ascent = baseline to top of character
			w.DrawRect(x,0,width-1, fnt.GetAscent(), Color(255,255,200)); 
			// descent = baseline to bottom of character
			w.DrawRect(x, fnt.GetAscent(), width-1, fnt.GetDescent(), Color(255,200,255)); 
			// getheight = total height of the character
			w.DrawRect(x+width-1, 0, 1, fnt.GetHeight(), Black()); 
			dx.Add(width+4); // adds 4 to the width of the character and add it to the collection
			x += width; // increases x with the character width
		}
		
		w.DrawRect(0,0,4,4,Black()); // draws a black rectangle
		w.DrawText(0,0,text,fnt); // draws the text in the choosen font
		
		// draw the text in blue color, dx.getcount number of characters
		// and a spacing between the individual characters in the collection dx
		w.DrawText(0,70,text,fnt,Blue(),dx.GetCount(),dx.begin());
		
		w.End(); // ends the offset and clipping settings
	}
	
	void NewFont() { // defines a function when a new font is choosen
		Refresh(); // marks the whole view for repainting
	}
	
	MyApp() {
		for(int i=0; i < Font::GetFaceCount(); i++) // for all known fonts in the OS
			font_list.Add(i, Font::GetFaceName(i)); // adds the name to the droplist widget
		
		// add a control droplist to the application window
		// height toppos from 0 to the minimum size of the widget (ctrl)
		// width from 0 to 200 pixels
		Add(font_list.TopPos(0, MINSIZE).LeftPosZ(0, 200));
		
		font_list <<= 0; // <<= operator will select item 0
		font_list << [=] { NewFont(); }; // << operator adds a lambda function to the selected event of a droplist widget
	}
};


GUI_APP_MAIN // gui entry point
{
	MyApp().Sizeable().Run(); // starts an instance of the Myapp struct in a sizeable window
}