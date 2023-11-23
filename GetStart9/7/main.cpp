#include <CtrlLib/CtrlLib.h> // uses gui library

using namespace Upp;

class MouseCtrl : public Ctrl // defines an inherited control for the widget
{
	public:
		virtual Value GetData() const; // default data get property
		virtual void SetData(const Value& v); // default set data property
		virtual void Paint(Draw& w); // to paint the widget
		virtual void LeftDown(Point, dword); // left mouse click
		virtual void MiddleDown(Point, dword); // middle mouse click
		virtual void RightDown(Point, dword); // right mouse click
		virtual void MouseMove(Point, dword); // mouse move function
		MouseCtrl(); // default constructor
		MouseCtrl& SetFont(Font f); // SetFont property function
		MouseCtrl& Ink(Color c); // Ink property function
		MouseCtrl& Paper(Color c); // Paper property function
				
	private:
		String text, text2; // variables that hold text fields
		Font font; // the font used for the widget
		Color ink, paper; // the colors used for the widget
};

Value MouseCtrl::GetData() const
{
	return text; // returns the mouse button field
}

void MouseCtrl::SetData(const Value& v)
{
	text = v; // sets the mouse button field
	Refresh(); // refreshes the control
}

void MouseCtrl::Paint(Draw& w)
{
	Size size = GetSize(); // gets the size of the widget
	w.DrawRect(size, paper); // draws a rectangle
	Size txtsize = GetTextSize(text, font); // gets text size
	size.cx = (size.cx - txtsize.cx) / 2; // sets width
	size.cy = (size.cy - txtsize.cy * 2) / 2; // sets height
	w.DrawText(size.cx, size.cy - txtsize.cy / 2, text, font, ink); // draws text field 1
	w.DrawText(size.cx, size.cy + txtsize.cy / 2, text2, font, ink); // draws text field 2
}

void MouseCtrl::LeftDown(Point, dword)
{
	text = "Left"; // changes text field 1
	Refresh(); // refreshes the control
}

void MouseCtrl::MiddleDown(Point, dword)
{
	text = "Middle"; // changes text field 1
	Refresh(); // refreshes the control
}

void MouseCtrl::RightDown(Point, dword)
{
	text = "Right"; // changes text field 1
	Refresh(); // refreshes the control
}

void MouseCtrl::MouseMove(Point pos, dword)
{
	text2 = Format("[%d:%d]", pos.x, pos.y); // sets field 2 to the coordinates
	Refresh(); // refreshes the control
}

MouseCtrl::MouseCtrl()
{
	text = "---"; // inits field 1 value
	text2 = "0:0"; // inits field 2 value
	ink = SBlack; // inits color of text
	paper = SWhite; // inits color of background
	font = StdFont(); // inits the text font
	SetFrame(BlackFrame()); // inits the frame
}

MouseCtrl& MouseCtrl::SetFont(Font f)
{
	font = f; // sets the font variable
	Refresh(); // refreshes the control
	return *this; // returns current control
}

MouseCtrl& MouseCtrl::Ink(Color c)
{
	ink = c; // sets the ink variable
	Refresh(); // refreshes the control
	return *this; // returns current control
}

MouseCtrl& MouseCtrl::Paper(Color c)
{
	paper = c; // sets the paper variable
	Refresh(); // refreshes the control
	return *this; // returns current control
}

#define LAYOUTFILE <GetStart9/7/MouseCtrl.lay> // defines the layout file
#include <CtrlCore/lay.h> // includes layout classes and macros

GUI_APP_MAIN // defines a gui entry point
{
	WithGetStart<TopWindow> app; // macro generated template from layout name
	app.mousectrl <<= "Click"; // uses the setdata operator
	CtrlLayout(app); // draws the controls on the form
	app.Run(); // shows and run the application
	PromptOK(AsString(~app.mousectrl)); // uses the getdata operator
}