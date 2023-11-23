#include <Core/Core.h> // includes core library

using namespace Upp;

CONSOLE_APP_MAIN // console entry point
{
	int x = 365; // defines an integer
	
	//use RLOG for LOGS in release mode
	//use DLOG for LOGS in debug mode
	LOG("Value of x is " << x); // outputs to log
	DUMPHEX(x); // dumps hex value
	
	float pi=3.1415926; // defines floating value
	DUMP(pi); // dumps value
	
	// defines a vector map	
	VectorMap<int, String> map = { {35, "house"}, {21, "appartment"}};
	DUMPM(map); // dumps map container
}