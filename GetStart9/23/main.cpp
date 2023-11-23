#include <CtrlLib/CtrlLib.h> // includes gui library

using namespace Upp;

// the API key of your project and account
String apikey = "yourKEY"; 

// function to make a web api request to google static map
String GetGoogleMap(double center_x, double center_y, int zoom, int cx, 
					int cy, const char* format, String *error) { 
	String request; // defines a http request string
	request << "http://maps.google.com/maps/api/staticmap?center=" << AsString(center_y) 
			<< ',' << AsString(center_x) << // makes the correct string
			"&zoom=" << zoom << // using all the correct parameters in the api request
			"&size=" << cx << 'x' << cy <<
			"&format=" << format << // the file format of the request
			"&sensor=false&key=" << apikey; // our custom api key
	HttpRequest r(request); // defines a httprequest variable
	String h = r.Execute(); // executes the http request and get the answer
	if (r.IsFailure()) // if an error occured
		*error = r.GetErrorDesc(); // gets the error description
	return h; // returns the web server answer
}

// function to get the image of a google static map request
Image GetGoogleMapImage(double center_x, double center_y, int zoom, int cx, 
						int cy, const char* format, String *error) { 
	// get the request and put in an image streamraster
	return StreamRaster::LoadStringAny(GetGoogleMap(center_x, center_y, zoom, cx, 
						cy, format, error)); 
}

struct MyApp : TopWindow { // defines a topwindow inherited struct
	Image img; // defines our image
	
	virtual void Paint(Draw& w) { // overrides the paint event
		w.DrawRect(GetSize(), Gray()); // draws a background gray rectangle
		w.DrawImage(0,0,img); // draws the image on the ctrl
	}
	
	MyApp() { // defines the constructor
		String* error; // defines an error string pointer
		// get a google static map api image
		img = GetGoogleMapImage(-73.998672, 40.714728, 12, 600, 600, "png", error); 
		//LOG(*error); // for debugging reasons
	}
};

GUI_APP_MAIN // main gui entry point
{
	MyApp().Sizeable().Zoomable().Run(); // runs the application in resizable, zoomable window
}