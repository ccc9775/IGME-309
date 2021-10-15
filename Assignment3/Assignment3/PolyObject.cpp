// Course: IGME 309-05
// Student Name: Chase Call
// Assignment Number: 03
#include "PolyObject.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
using namespace std;

//initializes the empty object
PolyObject::PolyObject() {
	vertices.empty();
}

//deletes the vertices of the current object
PolyObject::~PolyObject() {
	vertices.clear();
}


// add vertex at the end of the vertex list
void PolyObject::addVertex(vec2 p_vert) {
	vertices.push_back(p_vert);
}


// set the color of this polygon
void PolyObject::setColor(vec3 p_color) {
	color = p_color;
}


// return the number of vertices
unsigned int PolyObject::getVertNum() {
	return vertices.size();
}


// draw the polygon if it’s completed
void PolyObject::draw() {
    glColor3f(color.r, color.g, color.b);

    //if the polygon only has one point, draw a point
    if (vertices.size() > 0 && vertices.size() < 2) {
        glPointSize(5);
        glBegin(GL_POINTS);

        for (int i = 0; i < vertices.size(); i++)
            glVertex2f(vertices[i].x, vertices[i].y);
        glEnd();
    }

    //if the polygon has 2 points, draw a line
    else if (vertices.size() > 1 && vertices.size() < 3) {

        glBegin(GL_LINES);
        for (int i = 0; i < vertices.size(); i++)
            glVertex2f(vertices[i].x, vertices[i].y);
        glEnd();
    }

    //if the polygon has more than 2 points, draw a polygon
    else if (vertices.size() >= 3) {
        glBegin(GL_POLYGON);
        for (int i = 0; i < vertices.size(); i++)
            glVertex2f(vertices[i].x, vertices[i].y);
        glEnd();
    }
}


// draw the polygon if it’s being created
void PolyObject::draw(vec2 p_mousePos) {
    glColor3f(color.r, color.g, color.b);
    if (vertices.size() > 0 && vertices.size() < 3) {

        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < vertices.size(); i++)
            glVertex2f(vertices[i].x, vertices[i].y);
        glVertex2f(p_mousePos.x, p_mousePos.y);
        glEnd();
    }
    else if (vertices.size() >= 3) {
        glBegin(GL_POLYGON);
        for (int i = 0; i < vertices.size(); i++)
            glVertex2f(vertices[i].x, vertices[i].y);
        glVertex2f(p_mousePos.x, p_mousePos.y);
        glEnd();
    }

}
