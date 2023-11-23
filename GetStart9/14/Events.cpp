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

        virtual void Activate() // overrides activate event
        {
            Log("Activate event called.");
        }

        virtual void Deactivate() // overrides deactivate event
        {
            Log("Deactivate event called.");
        }

        virtual bool Key(dword key, int count) // gets key code and repeat count
        {
        	// show key code, repeat index, description
        	Log(Format("Key(%x, %d) ", (int)key, count) + GetKeyDescEx(key)); 
            return false; // goes to parent objects
        }

        virtual void GotFocus() // overrides get focus event
        {
        	Log("GotFocus event called.");
        }

        virtual void LostFocus() // overrides loose focus event
        {
        	Log("LostFocus event called.");
        }
 
        virtual bool HotKey(dword key) // overrides get hotkey event as top ctrl event
        {
        	// show key code and extended description
        	Log(Format("HotKey(%x) ", (int)key) + GetKeyDescEx(key)); 
            return false; // goes until root ctrl
        }

        virtual void ChildGotFocus() // overrides child ctrl got focus
        {
        	Log("ChildGotFocus event called.");
        }

        virtual void ChildLostFocus() // overrides child loose focus
        {
        	Log("ChildLostFocus event called.");
        }

        virtual void Layout() // overrides change position or size of ctrl
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