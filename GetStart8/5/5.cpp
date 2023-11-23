#include <Core/Core.h> // includes core library

using namespace Upp;

CONSOLE_APP_MAIN
{
	// Vector basics
	
	Vector<int> v; // defines a vector of type integer
	v.Add(1); // adds "1" to the container
	DUMP(v);
	v << 4 << 5; // adds numbers to the container
	v.Append({6, 7}); // adds numbers
	for(int i=0; i < v.GetCount(); i++) // does for all elements
		LOG(v[i]);
	
	
	// Vector operations
	
	v.Insert(2,10); // insert numbers 10 at position 3
	v.Remove(0); // removes the first element
	DUMP(v);
	v.Get(13,-1); //gets 14th element in array, if not exists return second argument (-1)
	Sort(v); // sorts the vector container
	DUMP(v);
	
	
	// Vector transfers
	
	Vector<int> v1; // defines another vector
	v1 = pick(v); // moves elements from v to v1
	DUMP(v);
	DUMP(v1);
	v = clone(v1); // copies elements from v1 to v
	DUMP(v);
	
	
	// Array container
	
	Array<std::string> as; // defines a classic Array, std::string is not moveable
	as.Add("Test"); // adds an element
	for (auto s : as) // goes to the full range
		DUMP(s.c_str());
	
	
	// Bidirectional containers
	
	BiVector<int> n; // defines a bidirectional vector
	n.AddHead(1); // adds a value at the beginning
	n.AddTail(100); // adds a value at the end
	DUMP(n);
	n.DropHead(); // drops a value at the beginning
	DUMP(n);
	
	
	// Index containers
	
	Index<String> ndx; // defines an index
	ndx.Add("alfa"); // adds some elements
	ndx.Add("beta");
	ndx.Add("gamma");
	ndx.Add("delta");
	ndx.Add("kappa");
	DUMP(ndx);
	DUMP(ndx.Find("beta")); // gets the index for an element we search
	ndx.Set(1,"alfa"); // replaces the element at position 2 with a new element
	DUMP(ndx);
	ndx.FindAdd("one"); // if not found add the element to the container
	DUMP(ndx);
	ndx.Unlink(2); // unlinks the element at position 3, Find will ignore it
	DUMP(ndx.IsUnlinked(2)); // checks if an element at position 3 is unlinked
	ndx.Put("foo"); // puts "foo" at an unlinked place, if non it will add the element
	ndx.Sweep(); // removes all unlinked elements
	DUMP(ndx);
	ndx.Remove(1); // removes element at position 2
	ndx.Insert(0,"new"); // inserts "new" at position 1
	DUMP(ndx);
	
	
	// VectorMap, ArrayMap containers
	
	VectorMap<String, int> m; // defines a vectormap of String and integer
	m.Add("A",1); // adds a value pair
	m.Add("C",4); // adds another value pair
	DUMP(m);
	DUMP(m.GetKeys()); // gets all the keys from the container (strings)
	DUMP(m.GetValues()); // gets all the values from the container (integers)
	m.GetValues()[1] = 100; // returns the element that contain value 1 and set it to 100
	DUMP(m);
	DUMP(m.Find("C")); // finds key "C", FindNext is available. Returns the element position
	DUMP(m.Get("C")); // gets the value for key "C"
	m.SetKey(1, "D"); // sets the key for element at position 2 at "D"
	
	
	// InVector, InArray
	// fast insert and remove operations (10x faster than Vector, Array)
	// but 10x slower on operator []
	
	InVector<int> v2; // defines an invector container
	for(int i = 0; i < 1000000; i++)
		v2.Add(i); // adds a lot of integers
	v2.Insert(0, -1); // inserts -1 at position 1, this is very fast
	DUMP(v2.FindLowerBound(55)); // finds the lower bound for 55
	
	
	// SortedIndex, SortedVectorMap, SortedArrayMap
	SortedIndex<int> x; // defines a sorted index
	x.Add(5); // adds some integers to the container
	x.Add(3);
	x.Add(7);
	x.Add(1);
	DUMPC(x); // you will notice that elements are sorted
	DUMP(x.Find(3)); // finds the position of element 3
	DUMP(x.FindLowerBound(3)); // finds the lower bound of element 3
	DUMP(x.FindUpperBound(6)); // finds the upper bound of element 6
	
	SortedVectorMap<String, int> ms; // defines a sorted vectormap
	ms.Add("zulu", 11); // adds some keys and values
	ms.Add("frank", 12);
	ms.Add("alfa", 13);
	
	DUMPM(ms);	// the keys are automatically sorted
}