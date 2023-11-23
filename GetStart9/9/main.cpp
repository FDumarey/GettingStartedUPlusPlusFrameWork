#include <CtrlLib/CtrlLib.h> // includes gui library

using namespace Upp;

#define IMAGECLASS ImagesImg // checks class in image designer, right click image
#define IMAGEFILE <GUIMenus/images.iml> // package and file name of iml file
#include <Draw/iml.h> // image drawing classes

struct MyAppWindow : TopWindow { // defines an application window
	MenuBar menu; // defines a menu bar
	ToolBar tool; // defines a toolbar
	StatusBar status; // defines a status bar
	Button lt,rt,lb,rb,lv,ht,hv,cb,rc; // defines some buttons
	
	typedef MyAppWindow CLASSNAME; // needed for THISFN macro
	
	void Exit() { // defines an exit function
		if(PromptOKCancel("Exit MyApp?")) // prompts sure
			Break(); // stops the application
	}
	
	void SubMenu (Bar& bar){ // defines a sub menu
		// no image so only menu item, help = help text for status bar
		bar.Add("Exit", [=] { Exit(); }).Help("This invokes the Exit command"); 
		bar.Separator(); // both separator for menu and toolbar
		// copy image from image designer object; toolbar & menu with tooltip
		bar.Add("ExitImg", ImagesImg::ImgExit(), [=] { Exit(); }); 
		bar.Separator(); // inserts separator
		// no text, so only toolbar with icon
		bar.Add(ImagesImg::ImgTool1(), [=] { Exit(); }).Help("This invokes the Fn1 toolbar command"); 
		// no text, so only toolbar with icon
		bar.Add(ImagesImg::ImgTool2(), [=] { Exit(); }).Help("This invokes the Fn2 toolbar command"); 
	}
	
	void MainMenu (Bar& bar){ // defines the main menu
		bar.Sub("Menu", [=](Bar& bar) { SubMenu(bar); }); // adds a sub menu
	}
	
	void RightDown(Point, dword) override { // adds a right click function
		MenuBar::Execute([=](Bar& bar){bar.Add("Exit", [=]{Exit();});}); // draws a context menu
	}
			
	MyAppWindow() { // default constructor
		Title("My Application with menus").Sizeable(); // defines sizeable from with title
		AddFrame(menu); // top frame menu
		AddFrame(TopSeparatorFrame()); // adds a top separator frame
		AddFrame(tool); // top frame toolbar
		AddFrame(status); // adds a status bar
		AddFrame(InsetFrame()); // adds an inset frame
		menu.Set([=](Bar& bar){MainMenu(bar);}); // draws menu
		menu.WhenHelp = status; // sets the help text output to the status statusbar object
		tool.Set([=](Bar& bar){SubMenu(bar);}); // draws toolbar
		tool.WhenHelp = status; // sets the help text output to the status statusbar object
		
		*this // current object
			<< lt.SetLabel("left-top").LeftPos(10,200).TopPos(10,40) // operator << = add action
			<< rt.SetLabel("right-top").RightPos(10,200).TopPos(10,40) // adds click button
			<< lb.SetLabel("left-bottom").LeftPos(10,200).BottomPos(10,40) // adds click button
			<< rb.SetLabel("right-bottom").RightPos(10,200).BottomPos(10,40) // adds click button
			<< lv.SetLabel("left-vsize").LeftPos(10,200).VSizePos(60,60) // adds click button
			<< ht.SetLabel("hsize-top").HSizePos(220,220).TopPos(10,40) // adds click button
			<< hv.SetLabel("hsize-vsize").HSizePos(220,220).VSizePos(60,60) // adds click button
			<< cb.SetLabel("hcenter-bottom").HCenterPos(200).BottomPos(10,40) // adds click button
			<< rc.SetLabel("right-vcenter").RightPos(10,200).VCenterPos(40); // adds click button
	}
};

GUI_APP_MAIN // main gui entry point
{
	MyAppWindow app; // defines an instance of the app struct
	app.Run(); // runs the application
}