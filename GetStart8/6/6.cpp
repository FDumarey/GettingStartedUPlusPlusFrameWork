#include <Core/Core.h> // includes core library

using namespace Upp;

CONSOLE_APP_MAIN // console entry point
{
	// Ranges
	
	Vector<int> x = {1,3,5,4,100,50,40}; // defines a vector of integers
	DUMP(SubRange(x,3,6)); // trims the collection from position 4 to 7
	DUMP(ConstRange(1,10)); // returns a collection of 10 times "1"
	DUMP(ReverseRange(x)); // reverses the collection x
	DUMP(SortedRange(x)); // sorts the collection x
	DUMP(FilterRange(x, [](int x) {return x > 30;})); // returns a collection with integers greater then 30
	
	
	// Algorithms
	
	DUMP(FindIndex(x,5)); // finds the position of number 5
	DUMP(FindMin(x)); // shows the position of the minimum value
	DUMP(FindMax(x)); // shows the position of the maximum value
	DUMP(Min(x)); // shows the minimum value
	DUMP(Max(x)); // shows the maximum value
	DUMP(Count(x,100)); // counts how many times value "100" is present
	DUMP(Sum(x)); // summates all values
	Sort(x); //uses stablesort(x) if equal values keeps original order at a performance penalty
	DUMP(x);
	DUMP(GetSortOrder(x)); // shows the order of the items as they were sorted
}