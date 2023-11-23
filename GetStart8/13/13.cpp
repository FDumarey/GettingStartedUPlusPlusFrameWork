#include <Core/Core.h> // includes core library

using namespace Upp;

CONSOLE_APP_MAIN // console entry point
{
	uint64 RandomArray [10]; // defines array for Random64 array function
	Cout() << "Random generator functions \n\n";
	Cout() << "Random(100) function: " << Random(100) << '\n'; // random number from 0 to 100
	Cout() << "Random64(999999999) function: " << Random64(999999999) << '\n'; // random 64-bit number from 0 to 999999999
	Random64(RandomArray, 10); // gets 10 random 64-bit unsigned integer numbers
	for (int i=0; i<10; i++) Cout() << "Random64(array," << i <<") : " << RandomArray[i] << '\n'; // prints array
	SeedRandom(100); // sets a random seed
	Cout() << "Randomf function with seed 100: " << Randomf() << '\n'; // random number with seed between 0 and 1
}