#include <Core/Core.h> // includes core library

using namespace Upp;

CONSOLE_APP_MAIN // console entry point
{
	Date date = GetSysDate(); // defines date variable
	DUMP(date);
	DUMP((int)date.year);
	DUMP((int)date.month);
	DUMP((int)date.day);
	
	Time time = GetSysTime(); // defines time variable
	DUMP(time);
	DUMP((int)time.hour);
	DUMP((int)time.minute);
	DUMP((int)time.second);
}