#include <CtrlLib/CtrlLib.h> // includes gui library

using namespace Upp;

struct Dialog : public TopWindow { // inherits a dialog from topwindow
	Button b; // defines a button
	Dialog() { // constructor
		SetRect(0,0,Zx(200),Zy(50)); // sets the size
		Add(b.SetLabel("Close dialog").SizePos()); // adds a button full size
		b << [=] { Close(); }; // defines close action through lambda
	}
};

struct MainWindow : public TopWindow { // inherits a main window from topwindow
	Dialog dlg; // defines a dialog
	Button a,b,c; // defines buttons
	MainWindow() { // constructor
		SetRect(0,0,Zx(400),Zy(100)); // sets the size
		// add button
		Add(a.SetLabel("Open or close non-modal, owned dialog").TopPos(0,50).HSizePos()); 
		// add button
		Add(b.SetLabel("Open or close non-modal, ownerless dialog").TopPos(50,50).HSizePos()); 
		// add button
		Add(c.SetLabel("Open modal dialog").TopPos(100,50).HSizePos()); 
		a << [=] { // sets lambda to button
			if(dlg.IsOpen()) // if dialog is open
				dlg.Close(); // closes the dialog
			else
				dlg.Open(this); // opens non-modal owned dialog
		};
		b << [=] { // sets lambda to button
			if(dlg.IsOpen()) // if dialog is open
				dlg.Close(); // closes the dialog
			else
				dlg.OpenMain(); // opens non-modal non-owned dialog
		};
		c << [=] { // sets lambda to button
			if(dlg.IsOpen()) // if dialog is open
				dlg.Close(); // closes the dialog
			else
				dlg.RunAppModal(); // opens modal dialog
		};
	}
};

GUI_APP_MAIN // gui entry point
{
	MainWindow().Run(); // runs the application
}