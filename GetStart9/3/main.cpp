#include <CtrlLib/CtrlLib.h> // includes gui library

using namespace Upp;

struct MyApp: TopWindow { // defines a class of topwindow
	Drawing drawing; // sets of drawing operations to form a vector image
	
	virtual void Paint(Draw& w) override { // overrides the paint event of topwindow
		w.DrawRect(GetSize(), White()); // paints the background white
		w.DrawDrawing(10,10,50,60, drawing); // paints the drawing vector within the bounds
		w.DrawDrawing(100,10,150,100, drawing); // paints the drawing vector within other bounds
		w.DrawDrawing(10,110,300,300, drawing); // paints the drawing vector within other bounds
	}
	
	MyApp() {
		DrawingDraw iw(200,200); // defines a vector drawing with size 200*200
		iw.DrawEllipse(10,10,180,100, Cyan()); // draws an ellipse in the vector context
		iw.DrawImage(100,100, CtrlImg::exclamation()); // draws a bitmap in the vector context
		iw.DrawRect(20,100,30,30, Blue); // draws a rectangle in the vector context
		drawing = iw; // copies the drawing operations to a vector instance
	}
};

GUI_APP_MAIN // gui entry point
{
	MyApp().Sizeable().Run(); // runs the topwindow object
}