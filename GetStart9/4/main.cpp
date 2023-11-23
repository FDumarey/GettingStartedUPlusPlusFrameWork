#include <CtrlLib/CtrlLib.h> // includes gui library

using namespace Upp;

struct MyApp: TopWindow{ // defines a topwindow structure
	Image image; // defines a bitmap
	
	virtual void Paint(Draw& w) override { // overrides the paint method
		w.DrawRect(GetSize(),Cyan());  // makes the background cyan
		w.DrawImage(10,10,image); // draws the bitmap
		w.DrawImage(80,30,image); // draws the bitmap again to see the alpha channel in action
	}
	
	MyApp() {
		ImageDraw iw(100,40); // defines a bitmap drawing context
		// rectangle on alpha layer, defined by GrayColor(x)
		iw.Alpha().DrawRect(0,0,100,40,GrayColor(0)); 
		// ellipse on alpha layer, 255 = non-transparant
		iw.Alpha().DrawEllipse(0,0,100,40,GrayColor(255)); 
		iw.DrawEllipse(0,0,100,40,Yellow()); // draws a yellow ellipse
		iw.DrawText(26,10,"Image", Arial(16).Bold()); // draws some text
		image=iw; // sets the bitmap to the series of imagedraw operations
	}
};

GUI_APP_MAIN // gui entry point
{
	MyApp().Sizeable().Run(); // runs an sizeable window instance of the struct/class
}