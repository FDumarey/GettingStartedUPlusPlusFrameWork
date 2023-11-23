#include <Core/Core.h> // includes core library
#include <Core/SSL/SSL.h> // includes ssl library

using namespace Upp;

CONSOLE_APP_MAIN // console entry point
{
	TcpSocket server; // defines a server tcp socket
    if(!server.Listen(443, 5)) { // checks if listener on port 443 with 5 queues is okay
        Cout() << ("Cannot open server port for listening\r\n"); // shows error message
		SetExitCode(99); // sets console exit code
        return; // exits the application
    }

    for(;;) { // does a endless loop
        TcpSocket socket; // defines a client socket incoming connection
        Cout() << "Waiting for connections...\n";
        if(socket.Accept(server)) { // if an incoming server connection is seen
            Cout() << "Connection accepted, initializing SSL\n";
            socket.SSLCertificate(LoadFile(GetDataFile("code.crt")),
                                  LoadFile(GetDataFile("code.key")),
                                  false); // defines the certificate and private key for SSL
            if(!socket.StartSSL()) { // tries to start the SSL connection
                Cout() << "Failed to start SSL, error: " << socket.GetErrorDesc() << '\n'; // error
                continue; // continues the application
            }
            while(socket.SSLHandshake()); // tries a SSL handshake between server and client
            if(socket.IsError()) { // checks for errors
                Cout() << "SSL handshake failed, error: " << socket.GetErrorDesc() << '\n'; // error
                continue; // continues application
            }
            Cout() << ("SSL succesfully established\n");
            HttpHeader http; // defines a http header object
            if(!http.Read(socket)) { // reads the http header request from the client
                Cout() << "Failed getting HTTPS header\n"; // error
                continue; // continues the application
            }
            Cout() << "HTTPS header: " << http.GetMethod() << ' ' << http.GetURI() << '\n'; // shows header
            String html; // defines a response string in html format
            html << "<html>"
                 << "<b>Method:</b> " << http.GetMethod() << "<br>"
                 << "<b>URI:</b> " << http.GetURI() << "<br>"; // adds client info to the response
            for(int i = 0; i < http.fields.GetCount(); i++) // gets through the http fields
                html << "<b>" << http.fields.GetKey(i) << ":</b> " << http.fields[i] << "<br>"; // gets the http fields from the client request
            int len = (int)http.GetContentLength(); // gets the length ot the http request
            if(len > 0) // if the length is not zero
                socket.GetAll(len); // gets all characters from the stack
            html << "<b><i>Current time:</i></b> " << GetSysTime() << "</html>"; // adds the system time to the response
            HttpResponse(socket, http.scgi, 200, "OK", "text/html", html); // sends the http response to the client
            Cout() << "Request finished\n\n"; // ends the request
        }
    }
}