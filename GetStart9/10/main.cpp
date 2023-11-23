#include <CtrlLib/CtrlLib.h> // includes gui library

using namespace Upp;

struct MyApp : TopWindow{ // inherits a form from topwindow
	void Drawthings(Draw& w, const String& txt) // function to draw some things
	{
		w.DrawEllipse(10,10,50,50,Green(),2,Cyan); // draws a circle
		w.DrawText(70,10, txt, Roman(30).Bold()); // sets text from parameter
	}
	
	virtual void Paint(Draw& w) override // overrides paint function
	{
		w.DrawRect(GetSize(),White()); // draws white background
		Drawthings(w, "Normal"); // normal drawing
		
		w.Offset(100,100); // sets an offset of 100,100 pixels
		Drawthings(w, "Offset"); // draws offset things
		w.End(); // ends offset
		
		w.Offset(0,200); // offsets 0,200 pixels
		w.Clip(20,20,200,80); // clips rectangle from 20,20 width 200 height 80
		Drawthings(w, "Clipping"); // draws clipping things
		w.End(); // ends clipping
		w.End(); // ends offset
		
		w.Clipoff(10,300,300,40); // clipping and offset from 10,300 width 300 height 40
		Drawthings(w, "Offset and Clipping"); // draws offset and clipping things
		w.End(); // ends clipping and offset
	}
};

GUI_APP_MAIN // gui entry point
{
	MyApp().Sizeable().Run(); // runs a resizable form
}