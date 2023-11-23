#include <Core/Core.h> // includes core library
#include <shellapi.h> // for ShellExecute win32 api

using namespace Upp;

CONSOLE_APP_MAIN // console entry point
{
	Cout() << "Opening the explorer and selecting bootmgr file in c: system drive\n";
	String strArgs = "/select, C:\\bootmgr"; // defines some arguments
	ShellExecute(0, "open", "explorer.exe", strArgs, 0, SW_NORMAL); // executes shell command
	
	Cout() << "Launching web browser to U++ home site\n";
	LaunchWebBrowser("https://www.ultimatepp.org/index.html"); // executes the default web browser
}