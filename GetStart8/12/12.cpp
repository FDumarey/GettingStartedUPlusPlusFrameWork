#include <Core/Core.h> // includes core library
#include <Core/POP3/POP3.h> // includes pop3 protocol
#include <Core/SMTP/SMTP.h> // includes smtp protocol

using namespace Upp;

CONSOLE_APP_MAIN // console entry point
{
	// SMTP send a test mail
	
	String user = "user"; // sets user name
	String pwd = "password"; // sets password
	Smtp mailsmtp; // instances from smtp class
	Smtp::Trace(); // activates tracing
	mailsmtp.Host("smtp") // sets the host name
		    .Port(465) // sets the tcp port
		    .SSL() // sets use of TLS/SSL certificates
			.Auth(user, pwd) // authenticates the user
			.To(user) // sends mail to own user
			.Subject("Mail from U++ framework") // sets a subject
		    .Body("This is a test mail with some attachments.") // sets the mail body
		    .Attach("text.txt", "This is a test of a String attachment") // adds a text attachment
		    .AttachFile(GetDataFile("12.cpp")); // adds a file attachment
	if(mailsmtp.Send()) // sends the mail
		Cout() << "Mail succesfully sent\n"; // succesfully sent
	else
		Cout() << "Error sending mail, error code: " << mailsmtp.GetError() << '\n'; // error sending
		
	// POP3 receive the list of unread mails
	
	Cout() << "Press ENTER when you are ready to receive your mails [ENTER]";
	String ready = ReadStdIn(); // waits for enter
	Pop3 mailpop3; // instances a pop3 class
	mailpop3.Host("pop") // sets the pop3 host name
            .Port(995) // sets the tcp port
            .User(user, pwd) // sets the credentials
            .SSL() // enables TSL/SSL certificates
            .Trace(); // activates logging of pop3
	if(!mailpop3.Login()) { // tries to login
		Cout() << "Connection to mailbox failed, error code: " << mailpop3.GetLastError() << "\n"; // login failed
		return; // exits program
	}
	int msgcount = mailpop3.GetMessageCount(); // counts the number of mails
	if(msgcount < 0) { // error retrieving mails
		Cout() << "Get messages failed, error code: " << mailpop3.GetLastError() << "\n";
		return; // exits the program
	}
	Cout() << "There are " << msgcount << " new messages in your inbox.\n\n"; // returns number of messages
	for(int i=1; i<=msgcount; i++) // loops through all messages
	{
		Cout() << "Retrieving message: " << i << '\n';
		String message = mailpop3.GetMessage(i); // gets the mail message
		if(IsNull(message)) // error retrieving message
			Cout() << "Error retrieving message, error code: " << mailpop3.GetLastError() << "\n";
		else {
			InetMessage mail; // defines a mail object
			if(mail.Read(message)) { // reads a message in the mail object
				Cout() << "Subject: " << mail["subject"] << "\n" // returns the subject
					       << "From: " << mail["from"] << "\n" // returns the from field
					       << "Date: " << mail["date"] << "\n" // returns the date
					       << "Attachments: " << mail.GetCount() << '\n'; // returns the number of attachments
				for(int j = 0; j < mail.GetCount(); j++) // loops through the attachments
					Cout() << "Attachment " << j << ", type " << mail[j]["content-type"] // gets the content-type
						   << ", size: " << mail[j].Decode().GetLength() << '\n'; // gets the size
					Cout() << "\n";
				}
				else
					Cout() << "Error parsing the message\n"; // error reading the mail object
			}
	}	
}