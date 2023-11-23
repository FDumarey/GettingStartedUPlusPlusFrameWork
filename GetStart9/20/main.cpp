#include <CtrlLib/CtrlLib.h> // includes gui library
#include <GLDraw/GLDraw.h> // opengl draw wrapper library
#include <GLCtrl/GLCtrl.h> // opengl library

using namespace Upp;

struct OpenGLExample : GLCtrl { // inherits a opengl widget control
	Point point; // defines a point

	void GLPaint() override { // overrides painting the canvas
		StdView(); // standard viewport
		Size sz = GetSize(); // gets window size
				
		double ty = 10 * point.x; // calculates modifier y
		double tx = 10 * point.y; // calculates modifier x
				
		/* opengl example 1
		// remove comments to run
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0.1, 0.39, 0.88, 1.0);
  		glEnable(GL_CULL_FACE);
  		glCullFace(GL_BACK);
  		glMatrixMode(GL_PROJECTION);
  		glLoadIdentity();
  		glFrustum(-2, 2, -1.5, 1.5, 1, 40);
  		glMatrixMode(GL_MODELVIEW);
  		glLoadIdentity();
  		glTranslatef(0, 0, -3);
  		glRotatef(tx/50, 1, 0, 0);
  		glRotatef(ty/70, 0, 1, 0);
  		
  		glColor3f(1.0, 1.0, 1.0);
  		glBegin(GL_LINES);
  		for (GLfloat i = -2.5; i <= 2.5; i += 0.25) {
    		glVertex3f(i, 0, 2.5); glVertex3f(i, 0, -2.5);
    		glVertex3f(2.5, 0, i); glVertex3f(-2.5, 0, i);
  		}
  		glEnd();
		
		glBegin(GL_TRIANGLE_STRIP);
    	glColor3f(1, 1, 1); glVertex3f(0, 2, 0);
    	glColor3f(1, 0, 0); glVertex3f(-1, 0, 1);
    	glColor3f(0, 1, 0); glVertex3f(1, 0, 1);
    	glColor3f(0, 0, 1); glVertex3f(0, 0, -1.4);
    	glColor3f(1, 1, 1); glVertex3f(0, 2, 0);
    	glColor3f(1, 0, 0); glVertex3f(-1, 0, 1);
  		glEnd();
  		glFlush();
  		
  		*/
  		// opengl gldraw example
  		// remove comments to run
  		GLDraw drawdc; // defines a opengl draw object
		drawdc.Init(sz); // initializes the viewport
		for(int angle=0; angle<360; angle+=15) // draw rotated text
			drawdc.DrawTextA(sz.cx - sz.cx/3, sz.cy-sz.cy/3, angle*10, "OpenGL DrawText");
		drawdc.End(); // ends the drawing operations
	}
	
	virtual void GLResize(int w, int h) { // overrides resizing the window
		glViewport(0, 0, (GLsizei)w, (GLsizei)h); // adapts the viewport
	}
	
	void MouseMove(Point p, dword) override { // overrides the mouse move
		point = p; // sets the point for modifier
		Refresh(); // calls the paint function
	}
};

GUI_APP_MAIN // gui entry point
{
	Ctrl::GlobalBackPaint(); // sets the background black
	TopWindow win; // defines a top window form
	OpenGLExample gl; // instances a opengl custom widget
	gl.SetFrame(InsetFrame()); // draws an inset frame
	win.Add(gl.HSizePos(10, 10).VSizePos(10, 10)); // adds the gl widget to the form
	win.Sizeable().Zoomable(); // sets the window sizeable and zoomable
	win.Open(); // opens the window
	win.Run(); // runs the application
}