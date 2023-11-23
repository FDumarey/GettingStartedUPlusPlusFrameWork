#include <Core/Core.h> // includes core library

using namespace Upp;

CONSOLE_APP_MAIN // console entry point
{
	// U++ special Functions
	
	
	// define a function fn that takes an integer and returns 3* the integer value
	
	Function<int (int)> fn = [](int n) { LOG("Called 3*n"); return 3*n; };
	int n=fn(7); // calls the function with value 7
	DUMP(n);
	
	
	// here the operator << is used to add statements to the function
	// please notice that only the last return will be validated (n squared)
	
	fn << [](int n) { LOG("Called n*n"); return n*n; };
	n = fn(7); // calls the new function with value 7
	DUMP(n);
	
	fn.Clear(); // clears the assignment of the function fn
	n = fn(7); // calls the empty function fn, so this will return 0
	DUMP(n);
	
	
	// define an event, it always returns void
	
	Event<> ev = [] { LOG("Event invoked"); };
	ev(); // calls the event
	
	
	// define a gate, it always returns a boolean, return true if parameter < 10
	
	Gate<int> gt = [](int x) { LOG("Gate invoked with: " << x); return x < 10; };
	bool b=gt(8); // calls the gate function gt with the parameter 8
	DUMP(b);
	
}