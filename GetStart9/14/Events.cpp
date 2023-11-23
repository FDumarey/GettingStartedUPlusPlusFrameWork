#include <CtrlLib/CtrlLib.h> // includes gui library

using namespace Upp;

String GetKeyDescEx(int key) // function to return extended key description
{
		String desc = GetKeyDesc(key & ~K_KEYUP); // gets extended key string
        if(key & K_KEYUP) desc << " UP"; // if key_up event add text
        return desc; // returns description string
}

struct App : TopWindow // defines app from a windows forms class
{
		ArrayCtrl  log; // defines an array control

        void Log(const String& s) // function to write to array control
        {
        	log.Add(s); // adds a string to the control
            log.GoEnd(); // sets cursor at last position
        }

        void Activate() override // overrides activate event
        {
            Log("Activate event called.");
        }

        void Deactivate() override // overrides deactivate event
        {
            Log("Deactivate event called.");
        }

        bool Key(dword key, int count) override // gets key code and repeat count
        {
        	// show key code, repeat index, description
        	Log(Format("Key(%x, %d) ", (int)key, count) + GetKeyDescEx(key)); 
            return false; // goes to parent objects
        }

        void GotFocus() override // overrides get focus event
        {
        	Log("GotFocus event called.");
        }

        void LostFocus() override // overrides loose focus event
        {
        	Log("LostFocus event called.");
        }
 
        bool HotKey(dword key) override // overrides get hotkey event as top ctrl event
        {
        	// show key code and extended description
        	Log(Format("HotKey(%x) ", (int)key) + GetKeyDescEx(key)); 
            return false; // goes until root ctrl
        }

        void ChildGotFocus() override // overrides child ctrl got focus
        {
        	Log("ChildGotFocus event called.");
        }

        void ChildLostFocus() override // overrides child loose focus
        {
        	Log("ChildLostFocus event called.");
        }

        void Layout() override // overrides change position or size of ctrl
        {
        	Log("Layout event called.");
        }

        App() // default constructor
        {
        	SetFrame(InsetFrame()); // sets a inset frame
            AddFrame(InsetFrame()); // adds a inset frame
            log.AddColumn("Ctrl form events:"); // adds one column to the array control
            Add(log.HSizePos().BottomPosZ(0, 300)); // adds a array control to the form
        }
};

GUI_APP_MAIN // main gui entry point
{
	App().Sizeable().Zoomable().Run(); // runs the application with a sizeable form
}