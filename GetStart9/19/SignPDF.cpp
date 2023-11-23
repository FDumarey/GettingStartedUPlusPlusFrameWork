#include <CtrlLib/CtrlLib.h> // includes gui library
#include <Core/SSL/SSL.h> // ssl library for digital signature
#include <PdfDraw/PdfDraw.h> // pdf export library

using namespace Upp;

CONSOLE_APP_MAIN // console application
{
	PdfDraw pdf; // defines pdf object
	PdfSignatureInfo pdfSSL; // defines pdf signature object

	pdfSSL.cert = LoadDataFile("cert.pem"); // loads certificate
	pdfSSL.pkey = LoadDataFile("pkey.pem"); // loads private key
	pdfSSL.name = "Frederik Dumarey"; // sets CN
	pdfSSL.location = "Belgium"; // sets location
	pdfSSL.reason = "Digital signature"; // sets signature reason code
	pdfSSL.contact_info = "frederik.dumarey@telenet.be"; // sets contact info

	pdf.DrawText(200, 200, "Hello world!", Serif(200), Magenta()); // draws text
	// draw an ellipse filled with light blue, width 5 pixels and contour color red
	pdf.DrawEllipse(310,500,80,60,LtBlue(),5,Red()); 
	DrawJPEG(pdf, 100, 1000, 2000, 940, LoadDataFile("1.jpg")); // adds a jpg bitmap

	String file = GetHomeDirFile("U++.pdf"); // filename in home folder
	SaveFile(file, pdf.Finish(&pdfSSL)); // saves the pdf file
	         
	LaunchWebBrowser(file); // shows pdf in web browser
}