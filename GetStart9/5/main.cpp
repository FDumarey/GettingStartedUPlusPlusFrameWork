#include <CtrlLib/CtrlLib.h> // includes gui library

using namespace Upp;

GUI_APP_MAIN // Print jobs need GUI entry point for drawing operations
{
	int i;
	PrinterJob pd("My printer job"); // defines a printerjob instance with a title
	i = PromptYesNo("Landscape?");
	DUMP(i);
	if(i) // do we want a landscape printer job?
        pd.Landscape(); // sets the print job to landscape
	if (pd.Execute()) { // if the printerjob is executing
		Draw& w = pd.GetDraw(); // gets a drawing context to the printer job
		w.StartPage(); // starts a new printer page
		w.DrawText(200,1200, "Hello World!", Arial(600)); // coordinates are dots = 1/600 of an inch
		w.EndPage(); // ends this page
		w.StartPage(); // starts a new page
		w.DrawText(200,1200,"Second page", Roman(600)); // puts some text on the second page
		w.EndPage(); // ends the second page
	}
}