#include <CtrlLib/CtrlLib.h> // includes gui library
#include <plugin/jpg/jpg.h> // using the jpeg library

using namespace Upp;

GUI_APP_MAIN // gui entry point
{
	FileSel fs; // defines file selector dialog
	// define raster types
	fs.Type("Image file", "*.bmp; *.png; *.tif; *.tiff; *.jpg; *.jped; *.gif"); 
	if(!fs.ExecuteOpen("Choose the image file to convert")) // opens file select dialog
		return; // if error stop program
	String fn = ~fs; // gets the filename
	JPGEncoder jpg(20); // defines a jpeg encoding stream with quality 20
	FileIn in(fn); // opens a file stream
	// define and open a streamraster stream
	One<StreamRaster> raster = StreamRaster::OpenAny(in); 
	if(!raster) { // if an error occurs on the streamraster
		Exclamation("Invalid file format"); // shows exclamation dialog
		return; // exits the program
	}
	FileOut out (fn + ".out.jpg"); // defines a file write stream
	jpg.SetStream(out); // sets a write jpeg stream using filename
	jpg.Create(raster->GetSize()); // creates needs the size of the jpeg bitmap
	for(int i=0; i<raster->GetHeight(); i++) { // loops through all lines of the bitmap
		RasterLine l = raster->GetLine(i); // defines a raster line and get it from the stream
		Buffer<RGBA> out(raster->GetWidth()); // defines a rgba buffer with size getwidth pixels
		for (int j=0; j<raster->GetWidth(); j++) { // loops through a line for all pixels
			// set monotone color to initial green value
			out[j].g = out[j].b = out[j].r = l[j].g; 
			out[j].a = 255; // no transparency
		}
		jpg.WriteLine(out); // writes and closes the jpeg output stream
	}
}