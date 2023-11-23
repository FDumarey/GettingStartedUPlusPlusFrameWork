#include <CtrlLib/CtrlLib.h> // includes gui library

#include <plugin/png/png.h> // includes png library
#include <plugin/bmp/bmp.h> // includes bmp library
#include <plugin/gif/gif.h> // includes gif library
#include <plugin/jpg/jpg.h> // includes jpeg library
#include <plugin/tif/tif.h> // includes tiff library

using namespace Upp;

GUI_APP_MAIN // gui entry point
{
	ImageDraw id(800, 600); // defines an image draw of 800*600 pixels
	id.DrawEllipse(0,0,800,600,LtGreen(),10,White()); // draws a full screen ellipse
	id.DrawText(80, 260, "Writing image to encoders.", Arial(50), Black()); // draws some text
	DrawFatFrame(id, 0, 0, 800, 600, White(), 2); // sets a outer frame
	Image im = id; // defines an image, and copy the drawing to it

	PNGEncoder png; // defines a png object
	png.Bpp(1); // sets color depth to 1 bit
	png.SaveFile(GetExeDirFile("image.png"), im); // saves the image to the executable directory
	
	BMPEncoder bmp; // defines a bmp object
	bmp.Bpp(32); // sets color depth to 32 bit
	bmp.SaveFile(GetExeDirFile("image.bmp"), im); // saves the image to the executable directory 

	GIFEncoder gif; // defines a gif object
	gif.SaveFile(GetExeDirFile("image.gif"), im); // saves the image to the executable directory

	JPGEncoder jpg; // defines a jpg object
	jpg.Quality(20); // sets the quality to 20%
	jpg.SaveFile(GetExeDirFile("image.jpg"), im); // saves the image to the executable directory
	 
	TIFEncoder tif; // defines a tif object
	tif.Bpp(8); // sets color depth to 8 bit
	tif.SaveFile(GetExeDirFile("image.tif"), im); // saves the image to the executable directory
}