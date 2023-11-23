#include <CtrlLib/CtrlLib.h> // includes gui library

using namespace Upp;

#define IMAGECLASS ImagesImg // defines the class of the icons
#define IMAGEFILE <GuiImages/images.iml> // defines the icon file
#include <Draw/iml.h> // imports images library

class MyApp : public TopWindow { // defines a new window form from topwindow
	public:
		Image img, img2; // defines two bitmaps
		FileSel fs; // defines a file selector
		virtual void Paint(Draw& w); // overrides the ctrl paint function
		void Open(); // function to open a file
		// override the left mouse click and connect to the open function
		virtual void LeftDown(Point, dword) { Open(); } 
		typedef MyApp CLASSNAME; // used for callback functions
		MyApp(); // default constructor
};

MyApp::MyApp() { // default constructor
	// choose extensions for file selector
	fs.Type("Image file", "*.bmp;*.png;*.tif;*.tiff;*.jpg;*.jpeg;*.gif"); 
	ImageBuffer ib(50,50); // defines a bitmap buffer 50*50 pixels
	for (int y=0; y<50; y++) { // loops through all lines of the buffer
		RGBA *line = ib[y]; // sets a pointer to each beginning of the line
		for (int x=0; x<50; x++) { // loops through all columns (x-coordinates) of the bitmap
			if (y==0 || y==49 || x==0 || x==49) // if we have a border coordinate
				*line++ = Black(); // sets the pixel black and move to the next pixel
			else { // if no border pixel
				line->a=2*(x+y); // sets the alpha value to 2 * (x+y)
				line->r=4*x; // sets the red value to 4 * x
				line->g=4*y; // sets the green value to 4 * y
				line->b=2*(x+y); // sets the blue value to 2 * (x+y)
				line++; // moves to the next pixel
			}
		}
	}
	Premultiply(ib); // already multiply the alpha value
	img = ib; // sets the image to the image memory buffer
}

void MyApp::Open() { // the open file function
	// display the standard file open dialog
	if (fs.ExecuteOpen("Choose the image file to open")) { 
		img2 = StreamRaster::LoadFileAny(~fs); // loads a bitmap file in a bitmap image
		Refresh(); // refreshes the ctrl, calling the paint function
	}
}

void MyApp::Paint(Draw& w) { // paints the ctrl area
	w.DrawRect(GetSize(), White()); // sets a white background
	w.DrawImage(10,5, img); // draws our created bitmap
	w.DrawImage(40,25,img); // draws an overlapped bitmap to see the alpha channel working
	w.DrawImage(0,300,img2); // draws the file selected bitmap
	for (int i=0; i < ImagesImg::GetCount(); i++) { // loops through the icons in the iml file
		w.DrawImage(50, 100+50*i, ImagesImg::Get(i)); // shows the icons
		w.DrawText(100,100+50*i, ImagesImg::GetId(i)); // shows the name of the icons
	}
}

GUI_APP_MAIN // main gui entry point
{
	MyApp().Sizeable().Run(); // runs the application in a resizable form
}