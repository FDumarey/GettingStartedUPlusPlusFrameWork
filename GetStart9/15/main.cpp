#include <CtrlLib/CtrlLib.h> // includes gui library

using namespace Upp;

#define LAYOUTFILE <GetStart9/15/layouttabs.lay> // defines the tabs layout file
#include <CtrlCore/lay.h> // converts to templates

struct FirstTabDlg : WithTab1<ParentCtrl> { // uses tab1 layout with parentctrl inheritance
	typedef FirstTabDlg CLASSNAME; // defines the classname
	FirstTabDlg(); // constructor prototype
};

FirstTabDlg::FirstTabDlg() // constructor for first tab
{
	CtrlLayout(*this); // places widgets into positions
}

struct SecondTabDlg : WithTab2<ParentCtrl> { // uses tab2 layout with parentctrl inheritance
	typedef SecondTabDlg CLASSNAME; // defines the classname
	SecondTabDlg(); // constructor prototype
};

SecondTabDlg::SecondTabDlg() // constructor for second tab
{
	CtrlLayout(*this); // places widgets into position
}

#undef LAYOUTFILE // undefines the first layout file
#define LAYOUTFILE <GetStart9/15/layoutmain.lay> // defines the main layout file
#include <CtrlCore/lay.h> // converts to templates

struct MainDlg : WithMain<TopWindow> { // uses main layout with topwindow inheritance
	typedef MainDlg CLASSNAME; // defines the classname
	FirstTabDlg  tab1; // instances a tab 1
	SecondTabDlg tab2; // instances a tab 2
	void DoDialog(); // info dialog prototype
	MainDlg(); // constructor prototype
};

void MainDlg::DoDialog() // information dialog function
{
	WithInfo<TopWindow> dlg; // variant without class, good for simple modal dialogs
	// ok means dialog has normal 'ok' button that needs setting up
	CtrlLayoutOK(dlg, "Information dialog"); 
	if(dlg.Execute() != IDOK) // if OK button is pressed
		return; // exits function
}

MainDlg::MainDlg() // main constructor
{
	CtrlLayout(*this, "Layouts"); // sets the widgets and the windows title
	tab.Add(tab1.SizePos(), "First page"); // adds tab1 instance to the tabctrl
	tab.Add(tab2.SizePos(), "Second page"); // adds tab2 instance to the tabctrl
	tab1.btnInfo << [=] {DoDialog();}; // sets lambda function for info ok button
}

GUI_APP_MAIN // main gui entry point
{
	MainDlg().Run(); // runs the main application
}