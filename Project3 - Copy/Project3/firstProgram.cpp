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
// Assignment Number: 02

// the window's width and height
int width, height;

//global parameters
int currentVert = 50;


void init(void)
{
	// initialize the size of the window
	width = 600;
	height = 600;
}

void drawFilledCircle(float red, float green, float blue, float center_x, float center_y, float radius) {
	// draw a circle as a filled ball
	glColor3f(red, green, blue);
	glBegin(GL_POLYGON);
	for (int i = 0; i < currentVert; ++i) {
		float t = (float)i / currentVert * 2.0f * 3.14f;
		glVertex2f(center_x + radius * cos(t), center_y + radius * sin(t));
	}
	glEnd();
}

void drawWireframeCircle(float red, float green, float blue, float center_x, float center_y, float radius, float lineWidth) {
	// draw a circle as a wireframe ball
	glColor3f(red, green, blue);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < currentVert; ++i) {
		float t = (float)i / currentVert * 2.0f * 3.14f;
		glVertex2f(center_x + radius * cos(t), center_y + radius * sin(t));
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
	glLoadIdentity();


	// draw the panda
	//draws the head
	drawFilledCircle(0.5, 0.0, 0.0, 0, 0, 3);
	drawWireframeCircle(0, 0, 0, 0, 0, 3, 1);
	
	//draws the ears
	drawFilledCircle(0.9, 0.9, 0.9, -3, 2.5, 1);
	drawWireframeCircle(0, 0, 0, -3, 2.5, 1, 1);
	drawFilledCircle(0.9, 0.9, 0.9, 3, 2.5, 1);
	drawWireframeCircle(0, 0, 0, 3, 2.5, 1, 1);
	drawFilledCircle(0.3, 0, 0, -2.6, 2.1, 0.45);
	drawWireframeCircle(0, 0, 0, -2.6, 2.1, 0.45, 1);
	drawFilledCircle(0.3, 0, 0, 2.6, 2.1, 0.45);
	drawWireframeCircle(0, 0, 0, 2.6, 2.1, 0.45, 1);
	
	//draws the eyes and eyebrows
	drawFilledCircle(0, 0, 0, -1.1, 0.9, 0.6);
	drawFilledCircle(0, 0, 0, 1.1, 0.9, 0.6);
	drawFilledCircle(1, 1, 1, -0.9, 1.1, 0.2);
	drawFilledCircle(1, 1, 1, 0.9, 1.1, 0.2);
	drawFilledCircle(1, 1, 1, -0.8, 1.9, 0.4);
	drawFilledCircle(1, 1, 1, 0.8, 1.9, 0.4);

	//draws the mouth and nose
	drawFilledCircle(1, 1, 1, 0, -1.3, 1.3);
	drawFilledCircle(0, 0, 0, 0, -0.5, 0.3);
	drawFilledCircle(0, 0, 0, -0.3, -1.8, 0.5);

	//draws the cheek patches
	drawFilledCircle(1, 1, 1, -2, -1.1, 0.5); 
	drawFilledCircle(1, 1, 1, 2, -1.1, 0.5);

	glutSwapBuffers(); // This example uses double framebuffers. This instructs the app that the current frame is finished and ready to display.
					   // The app then knows to swap it with the other buffer which was just displayed so that the display function can begin working on that buffer
}



// called when window is first created or when window is resized
void reshape(int w, int h)
{
	// update thescreen dimensions
	width = w;
	height = h;

	//do an orthographic parallel projection, limited by screen/window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5.0, 5.0, -5.0, 5.0); // Define the size of the canvas left =-5, right =-5, bottom =-5, top=5,
									  // so the orgin is at the center of the canvas.  

	/* tell OpenGL to use the whole window for drawing */
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
	if (key == '+') {
		if (currentVert != 100) {
			currentVert++;
			glutPostRedisplay();
			cout << "Vertices: " << currentVert << endl;
		}

	}
	if (key == '-') {
		if (currentVert != 3) {
			currentVert--;
			glutPostRedisplay();
			cout << "Vertices: " << currentVert << endl;
			cout << "yes";
		}

	}

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

	//register keyboard function
	glutKeyboardFunc(keyboard);

	//start the glut main loop
	glutMainLoop();

	return 0;
}