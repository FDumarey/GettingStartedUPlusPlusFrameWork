#include <Core/Core.h> // includes core library

using namespace Upp;

CONSOLE_APP_MAIN // console entry point
{
	const Vector<String>& cmdline = CommandLine(); // instances cmdline variable
	int i = cmdline.GetCount(); // gets number of arguments
	Cout() << "Number of arguments: " << i << '\n'; // shows number of arguments
	for (int x=0;x<i;x++) // loops through arguments
		Cout() << "Argument " << x << " : " << cmdline[x] << '\n'; // shows arguments
	Cout() << "Computer name: " << GetComputerName() << '\n'; // shows computer name
	Cout() << "User name: " << GetUserName() << '\n'; // shows user name
	Cout() << "Desktop manager: " << GetDesktopManager() << '\n'; // shows desktop manager
	Cout() << "CPU cores: " << CPU_Cores() << '\n'; // shows number of cpu cores
	SetExitCode(99); // sets an application exit code
}