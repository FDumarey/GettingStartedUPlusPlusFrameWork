#include <Core/Core.h> // includes core library
#include <Core/SSL/SSL.h> // includes ssl library

using namespace Upp;

CONSOLE_APP_MAIN // console entry point
{
	Cout() << "Initializing TCP listener on port: 1234\n";
	TcpSocket server; // defines a tcp socket server object
	if (!server.Listen(1234,5)) // opens port 1234 with 5 queues
	{
		Cout() << "Error initializing port 1234 on current host!\n"; // error setup listener
		SetExitCode(99); // sets an exit code 99
		return; // returns to console
	}
	Cout() << "Server ready, waiting for requests.\n";
	for (;;) // does an unlimited loop
	{
		TcpSocket answer; // defines a tcp socket for the client connection
		if (answer.Accept(server)) // if there is an incoming connection
		{
			String clientreq = answer.GetLine(); // gets a line from the client connection
			Cout() << "Client requests: " << clientreq << " , from: " << answer.GetPeerAddr() << '\n'; // gets info
			if (clientreq == "hello") // checks the client request string
				answer.Put("ehlo"); // puts an answer on the tcp socket stack for the client
			else
				answer.Put("got your message"); // puts an answer on the tcp socket stack for the client
			answer.Put("\n"); // sents a newline to the client
		}
	}
}