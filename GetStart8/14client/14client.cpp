#include <Core/Core.h> // includes core library
#include <Core/SSL/SSL.h> // includes ssl library

using namespace Upp;

CONSOLE_APP_MAIN // console entry point
{
	String request; // variable for user requests
	Cout() << "Connecting to server\n";
	do // loops until user enters exit command
	{
		Cout() << "Enter your server request, exit to finish:\n";
		request = ReadStdIn(); // reads request from console
		TcpSocket client; // defines a tcp socket client
		if(!client.Connect("127.0.0.1",1234)) // tries to connect to the server
		{
			Cout() << "Connection to server failed!\n"; // connect failed
			SetExitCode(99); // sets return code
			return; // exits application
		}
		client.Put(request + '\n'); // sents the request to the server
		Cout() << "Server answer from: " << request << " : " << client.GetLine() << '\n'; // gets the response from the server
		client.Close(); // closes the connection
	}
	while (request != "exit"); // loops until the request is "exit"
}