#include <CtrlLib/CtrlLib.h> // includes gui library

using namespace Upp;

#define LAYOUTFILE <GetStart9/6/dlg.lay> // defines the location of the layout file
#include <CtrlCore/lay.h> // imports the layout library

struct MyAppWindow : public WithDlgLayout<TopWindow> { // class inherits a layout dialog class
	MyAppWindow() { // constructor
		CtrlLayout(*this, "My Dialog"); // sets title and set all widgets from the layout file
		ok.Ok() << Acceptor(IDOK); //sets acceptor return value for the ok button
		cancel.Cancel() << Rejector(IDCANCEL); // sets rejector return value for the cancel button
	}
};

GUI_APP_MAIN // entry point for gui application
{
	MyAppWindow app; // instancess a layout dialog window
	app.text.SetData("Some text"); // sets text property of text label
	app.date1 <<= app.date2 <<= app.date3 <<= GetSysDate(); // sets system date to date widgets
	app.date1.ClearModify(); //sets flag to unmodified property for date1 widget
	app.date2.Disable(); // sets disable editing for date2 widget
	app.date3.SetReadOnly(); //sets date3 widget as read-only
	switch (app.Run()) { // gets the return value of the destructor of the class instance
		case IDOK: // if acceptor
			PromptOK("OK was pressed"); // shows message box OK
			break; // breaks switch statement
		case IDCANCEL: // if rejector
			Exclamation("Canceled"); // shows message box canceled
	}
	
	if (app.date1.IsModified()) PromptOK("Date was modified!"); // checks if date1 was modified
	PromptOK((String) app.text.GetData()); // shows the text widget property in a message box
}