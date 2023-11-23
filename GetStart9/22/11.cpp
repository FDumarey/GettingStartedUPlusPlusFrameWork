#include <CtrlLib/CtrlLib.h> // includes gui library

using namespace Upp;

struct TimerExample : TopWindow { // makes timer class windowed
	ArrayCtrl list; // defines array control list gui element
	TimeCallback tm; // defines a timecallback object
	
	void Alarm() { // a callback function for the timer
		list.Add("Timer invoked at " + AsString(GetSysTime())); // adds time to list
	}
	
	TimerExample() { // constructor
		list.NoHeader().AddColumn(); // adds list with one column
		Add(list.SizePos()); // shows list adapted to window size
		SetTimeCallback(-2000, [=] {Alarm();}); // uses settimecallback method
		tm.Set(-1000, [=] {Alarm();}); // uses timecallback method
	}
};


GUI_APP_MAIN
{
	TimerExample().Run(); // runs the timer example class
}