#include <CtrlLib/CtrlLib.h> // includes gui library

using namespace Upp;

struct MyApp : TopWindow { // makes a structure (class) and inherit TopWindow
	
	// override the Paint function of TopWindow and get the design context in reference w
	virtual void Paint(Draw& w) override { 
		
		w.DrawRect(GetSize(), White()); // set the background of the frame to color white
		w.DrawRect(10,10,60,80,Green()); // draw a green rectangle
		
		w.DrawLine(100,10,60,80,4,Green()); // draw a green line width 4 pixels
		
		// draw an ellipse filled with light blue, width 5 pixels and contour color red
		w.DrawEllipse(310,20,80,60,LtBlue(),5,Red()); 
		
		// draw an arc in a rectangle from point 1 to point 2, width 3 in cyan color
		w.DrawArc(RectC(410,20,80,60),Point(10,10),Point(450,80),3,Cyan()); 
		
		Vector<Point> p; // define a collection of type point
		// add some coordinates to the collection
		p << Point(30,110) << Point(60,180) << Point(10,150) << Point(30,110); 
		w.DrawPolygon(p,Blue()); // draw a closed polygon in blue
		w.DrawPolyline(p,4,Black()); // draw continuous lines width 4 and in black color
		
		// get a save bitmap from the CtrlImg library and put at coordinates
		w.DrawImage(40,240, CtrlImg::save()); 
		// rescale the same bitmap and only use alpha color in blue
		w.DrawImage(220,330,80,80,CtrlImg::save(),Blue()); 
		
		// set text in Arial bold on the screen
		w.DrawText(20,280,"Hello World!",Arial(50).Bold()); 
		// set the text with rotation in Courier underlined font
		w.DrawText(320,380,100, "Hello World!", Courier(100).Underline()); 
	}
};

GUI_APP_MAIN // a macro for the entry point of a GUI application
{
	// Run an instance of MyApp topwindow with a sizeable form (minimize, maximize, scale)
	MyApp().Sizeable().Title("Title").Icon(CtrlImg::Computer()).Run(); 
}