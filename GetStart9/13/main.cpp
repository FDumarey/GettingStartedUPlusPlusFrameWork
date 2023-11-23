#include <CtrlLib/CtrlLib.h> // uses gui library
#include <chrono> // high precision timers library

using namespace Upp;

class CachedImage : public ImageMaker // inherits cached image base class
{
	public:
		Color color; // a color member variable
		int x; // a size member variable
		virtual String Key() const; // overrides unique identifier
		virtual Image Make() const; // overrides cached image maker
};

String CachedImage::Key() const // function to define unique identifier
{
	// return a key based upon size and color
	return Format("%03d%03d%03d%03d", x, color.GetR(), color.GetB(), color.GetG()); 
}

Image CachedImage::Make() const // function to define cached image
{
	ImageBuffer b(x,x); // defines a image buffer x * x pixels size
	for(int yy=0;yy<x;yy++) // loops through vertical size
		for(int xx=0;xx<x;xx++) // loops through horizontal size
		{
			RGBA& a = b[yy][xx]; // makes a reference to a pixel in the buffer variable
			a.r = color.GetR(); // sets the red value
			a.g = color.GetG(); // sets the green value
			a.b = color.GetB(); // sets the blue value
			int q = x*xx - x*yy; // calculates an alpha value to have a triangle form
			a.a = q <= 255 ? q : 0; // if q < 255 use color otherwise make transparent
		}
		Premultiply(b); // pre multiplies the alpha value
		return b; // returns the buffered image
}

Image CreateImage(int x, Color color) // function to create a single image
{
	CachedImage m; // instances a cached image
	m.x = x; // sets the size parameter
	m.color = color; // sets the color parameter
	return MakeImage(m); // returns the cached image
}

class MyApp : public TopWindow // makes an gui application class
{
	public:
		virtual void Paint(Draw& w) // overrides the paint event
		{
			// take a snapshot of current time
			auto start = std::chrono::high_resolution_clock::now(); 
			w.DrawRect(GetSize(), Black()); // makes the background black
			for (int y=0; y<500; y+=50) // loops through vertical values
				for (int x=0;x<500;x+=25) // loops through horizontal values
				{
					Color c = Color((x)&255, (2*x)&255, (3*x)&255); // defines a color value
					w.DrawImage(x, y, CreateImage(x, c)); // calls the cached image function
				}
			// calculate time duration
			auto duration = std::chrono::high_resolution_clock::now() - start; 
			// convert duration to milliseconds
			auto result=std::chrono::duration_cast<std::chrono::milliseconds>(duration).count(); 
			// set the title of the application to the duration
			Title(AsString(result) + " milliseconds elapsed for drawing operation."); 
		}
};

GUI_APP_MAIN // gui entry point
{
	MyApp().Sizeable().Zoomable().Run(); // runs the application with a sizeable window
}