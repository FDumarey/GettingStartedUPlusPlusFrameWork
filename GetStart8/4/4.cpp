#include <Core/Core.h> // uses core library

using namespace Upp;

CONSOLE_APP_MAIN // console entry point
{
	// FileIn, FileOut and FileAppend streams
	
	FileOut out("test.txt"); // writes to a stream file
	if (!out)  // checks if succesfull
	{ 
		LOG("Failed to create the file stream");
		return;
	}
	out << "Some number: " << 123 << " and point: " << Point(1,2); // writes to the stream
	out.Close(); // closes the stream
	
	FileIn in("test.txt"); // opens a file stream
	if (!in) // checks if succesfull
	{
		LOG("Failed to open the file");
		return;
	}
	in.Seek(0); // sets the stream cursor at position 0
	DDUMP((char)in.Peek()); // gets one byte from the stream
	DDUMP(in.GetLine()); // gets a full line from the stream
	in.Seek(0); // sets the stream cursor at position 0
	DUMP(in.Get(10)); // gets the first 10 bytes from the stream
	in.Close(); // closes the stream
	
	FileAppend out2("test.txt"); // appends to an existing file stream
	out2 << "\nSome more text"; // appends some bytes
	out2.Close(); // closes the append stream
	DUMP(LoadFile("test.txt")); // loads the full stream in one time
	
	
	// SizeStream
	
	SizeStream szs; // defines a SizeStream
	szs << "1234567"; // sends data to the counter
	DUMP(szs.GetSize()); // reads the byte counter
	
	
	// StringStream
	
	StringStream sin("123456"); // defines a String stream and send data to it
	
	
	// CompareStream
	
	CompareStream cs(sin); // defines a Compare stream
	cs.Put("12345"); // puts data in the Compare stream
	DUMP(cs.IsEqual()); // checks the equality of the Compare stream
	
	
	// TeeStream
	
	TeeStream tee(sin, sin); // defines a Tee stream
	tee << "Test tee stream"; // puts data in the two streams simultaneously
	tee.Close(); // closes the stream
	DUMP(sin.GetResult()); // shows the resulting stream
	
	
	// Serialization
	
	StringStream ss3; // defines a String stream
	int x = 123; // defines an integer
	Color h = White(); //defines a U++ custom type
	ss3 % x % h; // % = Serialize function, converts all types to stream
	StringStream ss4(ss3.GetResult()); // defines a stream for de serialization
	int x2; // defines the integer
	Color h2; // defines the custom Color type
	ss4 % x2 % h2; // operator % is used to de serialize here
	DUMP(x2);
	DUMP(h2);
	
	
	// Streams and structures
	
	struct foo // defines a structure
	{
		int number; // an integer
		Color color; // a custom Color type
		void Serialize (Stream& s) // defines a Serialize function
		{
			s % number % color; // % operator for serialization
		}
	};
	
	foo Myfoo; // defines a struct object to write to
	Myfoo.number = 321; // sets property number
	Myfoo.color = Blue(); // sets property color
	String data = StoreAsString(Myfoo);  // this will use the Serialize function
	              // StoreAsFile will output to a file
	
	foo Myfoo2; // defines a struct object to read from
	LoadFromString(Myfoo2, data); // this will DeSerialize the stream
	// LoadFromFile will load from a file
	
	DUMP(Myfoo2.number); // shows the number
	DUMP(Myfoo2.color); // shows the color
}