#include <CtrlLib/CtrlLib.h> // uses gui library

using namespace Upp;

struct App : TopWindow {
	ArrayCtrl  log; // creates a array control widget

	void Log(const String& s) // function to add data
	{
		log.Add(s); // adds a line
		log.GoEnd(); // goes to last line
	}

	void MouseEnter(Point p, dword keyflags) override
	{
		Log(Format("MouseEnter(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
	}
	
	void MouseLeave() override
	{
		Log("MouseLeave");
	}

	void MouseMove(Point p, dword keyflags) override
	{
		Log(Format("MouseMove(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
	}

	void LeftDown(Point p, dword keyflags) override
	{
		Log(Format("LeftDown(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
	}

	void LeftDouble(Point p, dword keyflags) override
	{
		Log(Format("LeftDouble(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
	}

	void LeftTriple(Point p, dword keyflags) override
	{
		Log(Format("LeftTriple(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
	}
	
	void LeftDrag(Point p, dword keyflags) override 
	{
		Log(Format("LeftDrag(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
	}
	
	void LeftHold(Point p, dword keyflags) override 
	{
		Log(Format("LeftHold(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
	}

	void LeftRepeat(Point p, dword keyflags) override
	{
		Log(Format("LeftRepeat(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
	}

	void LeftUp(Point p, dword keyflags) override
	{
		Log(Format("LeftUp(Point(%d, %d), %x)", p.x, p.y, (int)keyflags));
	}

	void MouseWheel(Point p, int zdelta, dword keyflags) override
	{
		Log(Format("MouseWheel(Point(%d, %d), %d, %x)", p.x, p.y, zdelta, (int)keyflags));
	}
	
	App() // default constructor
	{
		SetFrame(InsetFrame()); // sets outer frame
		AddFrame(InsetFrame()); // sets inner frame
		log.AddColumn("Mouse events:"); // adds a arrayctrl column
		Add(log.HSizePos().BottomPosZ(0, 300)); // adds a lower pane for the log
	}
};

GUI_APP_MAIN // main gui entry point
{
	App().Run(); // runs the application
}