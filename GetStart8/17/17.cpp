#include <CtrlCore/CtrlCore.h> // includes core library

using namespace Upp;

CONSOLE_APP_MAIN // console entry point
{
	Cout() << "Putting some test on the clipboard\n";
	ClearClipboard(); // clears the clipboard contents
	WriteClipboardText("This is some text on the clipboard\n"); // adds text to clipboard
	Cout() << ReadClipboardText() << '\n'; // reads text from clipboard
	Cout() << "Appending some other text to the clipboard\n";
	AppendClipboardText("This is some appended text on the clipboard\n"); // appends text to clipboard
}