//  main.cpp
//  Flip-Flop-Game
//  Created by Ganesh Koripalli on 10/3/17.
//  Copyright © 2017 Ganesh Koripalli. All rights reserved.

//Headers for Visual Studio
/*#include <iostream>
 #include <GL/glew.h>
 #include <GL/glut.h>*/

//Headers for Xcode
#include "OpenGL/gl.h"
#include "OpenGL/glu.h"
#include <GLUT/glut.h>
#include <iostream>

void myReshape(int, int);
void display();
void spinCube();
void mouse(int, int, int, int);
void keyboard(unsigned char, int, int);
void face(int, int, int, int);
void colorcube();

//Functions:
GLsizei mouseX = 0, mouseY = 0;
GLsizei winWidth = 0, winHeight = 0;
GLfloat side = 50; //size of the square whenever mouse left button is clicked
GLfloat redColor[3] = { 1,0,0 };
GLfloat blueColor[3] = { 0,0,1 };
GLfloat delta = 0.02;
GLint axis = 2;
GLfloat theta[] = { 0.0, 0.0, 0.0 };

//Define the vertices
//Vertices of cube about the orgin

GLfloat vertices[8][3] =
    { { -1.0, -1.0, -1.0 },{ 1.0, -1.0, -1.0 },
    { 1.0, 1.0, -1.0 },{ -1.0, 1.0, -1.0 },{ -1.0, -1.0, 1.0 },
    { 1.0, -1.0, 1.0 },{ 1.0, 1.0, 1.0 },{ -1.0,1.0, 1.0 } };

//Colors to be assigned to vertices

GLfloat colors[8][3] =
    { { 0.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },
    { 1.0, 1.0, 0.0 },{ 0.0, 1.0, 0.0 },{ 0.0, 0.0, 1.0 },
    { 1.0, 0.0, 1.0 },{ 1.0, 1.0, 1.0 },{ 0.0, 1.0, 1.0 } };

int main(int argc, char** argv) {
    
    //mkgroup();
    //settime();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 850);
    glutCreateWindow("Flip-Flop-Game");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(spinCube);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
    
}

void myReshape(int w, int h) {
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800, 0, 850, 400.0, -400.0);
    glMatrixMode(GL_MODELVIEW);
    
}

//draw the grid
void drawLines() {
    
    //width of the grid lines
    glLineWidth(3.0);
    
    //The grid lines will be blue
    glColor3fv(blueColor);
    
    //For loop for drawing the lines
    for (int i = 0; i <= 800; i += 200) {
        glBegin(GL_LINES);
        glVertex3f(i, 0.0 , 0.0);
        glVertex3f(i, 800, 0.0);
        glEnd();
        glBegin(GL_LINES);
        glVertex3f(800, i , 0.0);
        glVertex3f(0, i, 0);
        glEnd();
    }
}

void drawSquare() {
    
 glColor3fv(blueColor);
 
for (int i = 0; i <= 800; i += 200) {
    
     glVertex3f(mouseX, mouseY, 0);
     glVertex3f(mouseX + side, mouseY, 0);
     glVertex3f(mouseX + side, mouseY + side, 0);
     glVertex3f(mouseX, mouseY + side, 0);
    
     glBegin(GL_POLYGON);
     glVertex3f(50 + i, 50, 0);
     glVertex3f(side, 50, 0);
     glVertex3f(side, side, 0);
     glVertex3f(50, side, 0);
     glEnd();
    
 }
    glFlush();
}

//display the cubes
void display(void) {
    
    int z = 0;
    glClearColor(1.0, 1.0, 1.0, 1.0); //change the color of the cubes inside to white
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    drawLines();
    glPopMatrix();
    
    glPushMatrix();
    //glTranslatef(0.0, 0.0, 0.0);
    glInitNames();
    glPushName(0);
    for (int i = 0; i <= 3; i++)
        for (int j = 0; j <= 3; j++)
        {
            glPushMatrix();
            glTranslatef(200 * j, 200.0 * i, 0.0);
            glLoadName((GLuint)(i + j + 1));
            glRotatef(theta[z], 1.0, 1.0, 0.0);
            colorcube();
            glPopMatrix();
            z++;
            
        }
    
    glutSwapBuffers();
    
}

//color the cube
void colorcube(void) {
    
    static int i = 0;
    int group[i][4];
    
    glColor3f(0, 0, 1.0);
    face(0, 3, 2, 1);
    glColor3f(0, 1.0, 0);
    face(2, 3, 7, 6);
    face(0, 4, 7, 3);
    face(1, 2, 6, 5);
    
    // group array is the array store the group information and the color of the same groups
    glColor3f(group[i][1]/10, group[i][2]/10, group[i][3]/10);
    if (i > 15) i = 0;
    i++;
    face(4, 5, 6, 7);
    glColor3f(0, 1.0, 0);
    face(0, 1, 5, 4);
    
}

//Drawing a face
void face(int a, int b, int c, int d) {
    
    glBegin(GL_POLYGON);
    glVertex3fv(vertices[a]);
    glVertex3fv(vertices[b]);
    glVertex3fv(vertices[c]);
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

//Mouse X position
void setX(int x) {
    
    mouseX = x;
    
}

//Mouse Y position
void setY(int y) {
    
    mouseY = y;
    
}

void mouse(int btn, int state, int x, int y) {
    
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        setX(x);
        setY(y);
        glutPostRedisplay();
    }
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        exit(1);
    }
    
}

//Keyboard function for exiting the program
void keyboard(unsigned char key, int x, int y) {
    
    if (key == 'q' || key == 'Q') {
        
        exit(0);
        
    }
}
