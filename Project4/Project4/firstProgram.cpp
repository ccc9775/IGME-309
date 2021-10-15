#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#include <math.h>
#endif
#include <iostream>
using namespace std;
// Course: IGME 309-05
// Student Name: Chase Call


// the window's width and height
int width, height;

//global parameters
int currentVert = 50;


void init(void)
{
	// initialize the size of the window
	width = 1000;
	height = 500;
}

void drawLinesY(int numLines) {
	// draw a circle as a filled ball
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_LINE);
	for (int i = 0; i < numLines; ++i) {
		
	}
	glEnd();
}

// called when the GL context need to be rendered
void display(void)
{
	// clear the screen to white, which is the background color
	glClearColor(1.0, 1.0, 1.0, 0.0);

	// clear the buffer stored for drawing
	glClear(GL_COLOR_BUFFER_BIT);


	// this is to define in which transformed space / coordinate system (in a matrix form) the objects will be drawn. 
	// (we'll learn matrix-based transformation in later classes.) 
	glMatrixMode(GL_MODELVIEW);


	glBegin(GL_LINES);
	for (int i = 0; i <= 25; i++) {
		if (i == 12) { glColor3f(0.1, 0.1, 0.1); }
		else { glColor3f(.7, .7, .7); };
		glVertex3f(i-12, 0, 0);
		glVertex3f(i-12, 0, -12);
		if (i == 12) { glColor3f(0.1, 0.1, 0.1); }
		else { glColor3f(.7, .7, .7); };
		glVertex3f(0, 0, i-12);
		glVertex3f(-12, 0, i-12);


		if (i == 12) { glColor3f(0.1, 0.1, 0.1); }
		else { glColor3f(.7, .7, .7); };
		glVertex3f(-i + 12, 0, 0);
		glVertex3f(-i + 12, 0, 12);
		if (i == 12) { glColor3f(0.1, 0.1, 0.1); }
		else { glColor3f(.7, .7, .7); };
		glVertex3f(0, 0, -i + 12);
		glVertex3f(12, 0, -i + 12);
	};
	glEnd();
	

	glutSwapBuffers(); // This example uses double framebuffers. This instructs the app that the current frame is finished and ready to display.
					   // The app then knows to swap it with the other buffer which was just displayed so that the display function can begin working on that buffer
}



// called when window is first created or when window is resized
void reshape(int w, int h)
{


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(20, 20, -20, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, w / h, 0.1, 1000);
	glViewport(0, 0, w, h);


	glutPostRedisplay();

	// update thescreen dimensions
	/*width = w;
	height = h;

	//do an orthographic parallel projection, limited by screen/window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5.0, 5.0, -5.0, 5.0); // Define the size of the canvas left =-5, right =-5, bottom =-5, top=5,
									  // so the orgin is at the center of the canvas.  

	/* tell OpenGL to use the whole window for drawing */
	/*glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glutPostRedisplay();
	*/

}



int main(int argc, char* argv[])
{
	// before create a glut window,
	// initialize stuff not opengl/glut dependent
	init();

	//initialize GLUT, let it extract command-line GLUT options that you may provide
	//NOTE that the '&' before argc
	glutInit(&argc, argv);

	// specify as double bufferred can make the display faster
	// Color is speicfied to RGBA, four color channels with Red, Green, Blue and Alpha(depth)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	//set the initial window size */
	glutInitWindowSize((int)width, (int)height);

	// create the window with a title
	glutCreateWindow("First OpenGL Program");

	/* --- register callbacks with GLUT --- */

	//register function to handle window resizes
	glutReshapeFunc(reshape);

	//register function that draws in the window
	glutDisplayFunc(display);

	//start the glut main loop
	glutMainLoop();

	return 0;
}