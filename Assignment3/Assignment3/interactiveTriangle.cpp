// Course: IGME 309-05
// Student Name: Chase Call
// Assignment Number: 03
#include "Assignment3/PolyObject.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>

using namespace std;

float canvasSize[] = {10.0f, 10.0f};
int rasterSize[] = {800, 600};

vector<PolyObject> polygons;
PolyObject tempPoly;
int polyNum;

// structure for storing 2D vertices
int numOfVertices = 0;
float v[2*100];
float color[3];
vec3 polygonColor;

float mousePosFloat[2];
vec2 mousePos;

void init(void)
{
    for(int i=0; i<6; i++)
        v[i] = 0.0f;
    mousePosFloat[0] = mousePosFloat[1] = 0.0f;
    mousePos.x = mousePosFloat[0];
    mousePos.y = mousePosFloat[1];
    color[0] =1.0f;
    polygonColor.r = color[0];
    color[1] = color[2] = 0.0f;
    polygonColor.g = color[1];
    polygonColor.b = color[2];
    polyNum = 0;
    polygons.push_back(tempPoly);
}

void drawCursor()
{
    glColor3f(1.0f, 0.0f, 1.0f);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex2fv(mousePosFloat);
    glEnd();
    glPointSize(1.0f);
}

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    for (int i = 0; i < polyNum; i++) {
        polygons[i].draw();
    }
    polygons[polyNum].draw(mousePos);
    
    drawCursor();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    rasterSize[0] = w;
    rasterSize[1] = h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, canvasSize[0], 0.0, canvasSize[1]);
    glViewport(0, 0, rasterSize[0], rasterSize[1]);
    
    glutPostRedisplay();
}

void mouse (int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        mousePos.x = mousePosFloat[0] = (float)x / rasterSize[0] * canvasSize[0];
        mousePos.y = mousePosFloat[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];
        v[numOfVertices*2+0] = mousePosFloat[0];
        v[numOfVertices*2+1] = mousePosFloat[1];
        

        polygons[polyNum].addVertex(mousePos);

        numOfVertices++;
        glutPostRedisplay();
    }
}

void motion(int x, int y)
{
    // mouse events are handled by OS, eventually. When using mouse in the raster window, it assumes top-left is the origin.
    // Note: the raster window created by GLUT assumes bottom-left is the origin.
    mousePos.x = mousePosFloat[0] = (float)x / rasterSize[0] * canvasSize[0];
    mousePos.y = mousePosFloat[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];
    
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key){
        case 27:
            exit(0);
            break;

        case 32:
            polygons[polyNum].draw();
            polygons.push_back(tempPoly);
            tempPoly.~PolyObject();
            polyNum++;
            break;
    }
}

void menu(int value)
{
    switch (value) {
        case 0: // clear
            numOfVertices = 0;
            for (int i = 0; i <= polyNum; i++) {
                polygons[i].~PolyObject();
            }
            glutPostRedisplay();
            break;
        case 1: //exit
            exit(0);
        case 2: // red
            polygons[polyNum].setColor(vec3(1.0, 0.0, 0.0));
            glutPostRedisplay();
            break;
        case 3: // green
            polygons[polyNum].setColor(vec3(0.0, 1.0, 0.0));
            glutPostRedisplay();
            break;
        case 4: // blue
            polygons[polyNum].setColor(vec3(0.0, 0.0, 1.0));
            glutPostRedisplay();
            break;
        case 5: // black
            polygons[polyNum].setColor(vec3(0.0, 0.0, 0.0));
            glutPostRedisplay();
        default:
            break;
    }
}
void createMenu()
{
    int colorMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Red", 2);
    glutAddMenuEntry("Green", 3);
    glutAddMenuEntry("Blue", 4);
    glutAddMenuEntry("Black", 5);
    
    glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 0);
    glutAddSubMenu("Colors", colorMenu);
    glutAddMenuEntry("Exit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char *argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(rasterSize[0], rasterSize[1]);
    glutCreateWindow("Assignment 3 - 2D Polygon Tool");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
    createMenu();
    glutMainLoop();
    return 0;
    
    
}