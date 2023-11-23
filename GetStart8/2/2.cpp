#include <Core/Core.h> // includes core library

using namespace Upp;

CONSOLE_APP_MAIN // console entry point
{
	// One example
	One<int> s;
	DUMP(bool(s)); //true if container has an element
	int *b = ~s; // ~ operator = gets pointer of One
	
	// Any example
	Any x;
	x.Create<String>() = "Hello"; // defines a string variable
	if (x.Is<String>()) // checks if string
		LOG("Any is now a string type with value: " << x.Get<String>()); // logs info
}