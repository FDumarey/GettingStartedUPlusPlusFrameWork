#include <Core/Core.h> // includes core library
#include <Core/SSL/SSL.h> // includes SSL library

using namespace Upp;

CONSOLE_APP_MAIN // console entry point
{
	Cout() << "Enter the URL:\n";
	String url = ReadStdIn(); // reads the url string
	String proxy = ""; // defines a proxy if needed
	HttpRequest http(url); // defines httprequest with url
	http.Proxy(proxy); // defines the proxy server
	String contents = http.Execute(); // executes the whole http request
	Cout() << "Error: " << http.GetErrorDesc() << '\n'; // gets the error code if any
	Cout() << "Status: " << http.GetStatusCode() << " , " << http.GetReasonPhrase() << '\n'; // gets the http status code
	Cout() << "Content: " << contents.GetLength() << " bytes" << '\n'; // gets the length of the http content
	Cout() << "Press ENTER to see the contents\n";
	url = ReadStdIn(); // waits for enter
	Cout() << contents.ToString() << '\n'; // shows the contents of the http request
}