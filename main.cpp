//  main.cpp
//  3DCube
//  Created by Ganesh Koripalli on 9/28/17.
//  Copyright © 2017 Ganesh Koripalli. All rights reserved.

//Packages for Xcode:
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <iostream>

//Packages for Visual Studios:
//#include "GL/glew.h"
//#include "GL/freeglut.h"


void myReshape(int, int);
void display();
void spinCube();
void mouse(int, int, int, int);
void keyboard(unsigned char, int, int);
void face(int, int, int, int);
void colorcube();
void translate(char);
void changeColor(char);
void zoom(char);

float height = 0;
float weight = 0;

//Define the vertices
//Vertices of cube about the orgin

GLfloat vertices[8][3] =
    {{ -1.0, -1.0, -1.0 },{ 1.0, -1.0, -1.0 },
    { 1.0, 1.0, -1.0 },{ -1.0, 1.0, -1.0 },{ -1.0, -1.0, 1.0 },
    { 1.0, -1.0, 1.0 },{ 1.0, 1.0, 1.0 },{ -1.0,1.0, 1.0 }};

//Colors to be assigned to vertices

GLfloat colors[8][3] =
    {{ 0.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },
    { 1.0, 1.0, 0.0 },{ 0.0, 1.0, 0.0 },{ 0.0, 0.0, 1.0 },
    { 1.0, 0.0, 1.0 },{ 1.0, 1.0, 1.0 },{ 0.0, 1.0, 1.0 }};

//Set up z-buffer and double buffering
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    //double buffering for smooth animation
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    
    //Window creation and callbacks here
    glutInitWindowSize(500, 500);
    glutCreateWindow("cube");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(spinCube);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return (0);
}

//Reshape callback

void myReshape(int w, int h) {
    GLfloat aspect = (GLfloat)w / (GLfloat)h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if (w <= h) //aspect <= 1
        glOrtho(-2.0, 2.0, -2.0 / aspect, 2.0 / aspect, -10.0, 10.0);
    else //aspect > 1q
        glOrtho(-2.0*aspect, 2.0*aspect, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

GLfloat delta = 0.02;
GLint axis = 2;

//Functions:
GLfloat theta[] = { 0.0, 0.0, 0.0 };
void display(void) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(height, weight, 0);
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    colorcube();
    glutSwapBuffers();
    
}

//Drawing faces

void colorcube(void) {
    
    face(0, 3, 2, 1);
    face(2, 3, 7, 6);
    face(0, 4, 7, 3);
    face(1, 2, 6, 5);
    face(4, 5, 6, 7);
    face(0, 1, 5, 4);
}

//Drawing a face

void face(int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);
    glColor3fv(colors[a]);
    glVertex3fv(vertices[a]);
    glColor3fv(colors[b]);
    glVertex3fv(vertices[b]);
    glColor3fv(colors[c]);
    glVertex3fv(vertices[c]);
    glColor3fv(colors[d]);
    glVertex3fv(vertices[d]);
    glEnd();
}

//Spin the cube about the axi
void spinCube() {
    
    theta[axis] += delta;
    
    if (theta[axis] > 360.0)
        theta[axis] -= 360.0;
    //Display the result
    glutPostRedisplay();
}

void changeColor(char option) {
    
    //Remove color
    if (option == 'i') {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 3; j++) {
                colors[i][j] += 0.1;
            }
        }
    }
    //Add color
    else if (option == 'u') {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 3; j++) {
                colors[i][j] -= 0.1;
            }
        }
    }
}

// Zoom function
void zoom(char option) {
    
    // Zoom in
    if (option == 'z' || option == 'Z') {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 3; j++)
            {
                if (vertices[i][j] > 0)
                    vertices[i][j] += 0.1;
                else vertices[i][j] -= 0.1;
            }
        }
    }
    
    // Zoom out
    else if (option == 'x' || option == 'X') {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 3; j++) {
                if (vertices[i][j] < 0)
                    vertices[i][j] += 0.1;
                else vertices[i][j] -= 0.1;
            }
        }
    }
}

//Translate
void translate(char direction) {
    
    //Right
    if (direction == 'd') {
        for (int i = 0; i < 8; i++) {
            vertices[i][0] -= 0.1;
            height += 0.1;
        }
    }
    //Left
    else if (direction == 'a') {
        for (int i = 0; i < 8; i++) {
            vertices[i][1] += 0.1;
            height -= 0.1;
        }
    }
    //Up
    else if (direction == 'w') {
        for (int i = 0; i < 8; i++) {
            vertices[i][0] += 0.1;
            height += 0.1;
        }
    }
    //Down
    else if (direction == 's') {
        for (int i = 0; i < 8; i++) {
            vertices[i][0] -= 0.1;
            height -= 0.1;
        }
    }
}

//Change axis of rotation
//Mouse callback

void mouse(int btn, int state, int x, int y) {
    
    if ((btn == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
        axis = 0;
    if ((btn == GLUT_MIDDLE_BUTTON) && (state == GLUT_DOWN))
        axis = 1;
    if ((btn == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
        axis = 2;
    
    glutIdleFunc(spinCube);
}

//Keyboard functionality
void keyboard(unsigned char key, int x, int y) {
    
    bool stop = false;
    
    //quit
    if (key == 'q' || key == 'Q') {
        exit(0);
    }
    
    // Translate
    if (key == 'd' || key == 'D') {
        translate(key);
    }
    if (key == 'a' || key == 'A') {
        translate(key);
    }
    if (key == 'w' || key == 'W') {
        translate(key);
    }
    if (key == 's' || key == 'S') {
        translate(key);
    }
    
    // Zoom in/out
    if (key == 'z' || key == 'Z') {
        zoom(key);
    }
    if (key == 'x' || key == 'X') {
        zoom(key);
    }
    
    //Change color
    if (key == 'i') {
        changeColor(key);
    }
    if (key == 'u') {
        changeColor(key);
    }
    
    //animation
    if (key == ' ')
        stop = !stop;
    if (stop)
        glutIdleFunc(NULL);
    else
        glutIdleFunc(spinCube);
    
}
