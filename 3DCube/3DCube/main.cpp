//  main.cpp
//  3DCube
//  Created by Ganesh Koripalli on 9/20/17.
//  Copyright © 2017 Ganesh Koripalli. All rights reserved.

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <iostream>
#include <stdlib.h>

//Part 1: Define the vertices
//Vertices of cube about the orgin

GLfloat vertices[8][3] =
    {{-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0},
    {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0}, {-1.0, -1.0, 1.0},
    {1.0, -1.0, 1.0}, {1.0, 1.0, 1.0}, {-1.0,1.0, 1.0}};

//colors to be assigned to vertices

GLfloat colors[8][3] =
    {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0},
    {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
    {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}};

//part 2: set up z-buffer and double buffering
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    //double buffering for smooth animation
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    
    /*Part 3: Window creation and callbacks here*/
//    glutInitWindowSize(500, 500);
//    glutCreateWindow("cube");
//    glutReshapeFunc(myReshape);
//    glutDisplayFunc(display);
//    glutIdleFunc(spinCube);
//    glutMouseFunc(mouse);
//    glutKeyboardFunc(keyboard);
//    glEnable(GL_DEPTH_TEST);
//    glutMainLoop();
//    return (0);
}

/*Part 3: Window creation and callbacks here*/
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

//Part 4: Reshape callback

void myReshape(int w, int h) {
    GLfloat aspect = (GLfloat) w / (GLfloat) h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if (w <= h) //aspect <= 1
        glOrtho(-2.0, 2.0, -2.0 / aspect, 2.0 / aspect, -10.0, 10.0);
    else //aspect > 1
        glOrtho(-2.0*aspect, 2.0*aspect, -2.0, 2.0, -10., 10.0);
    glMatrixMode(GL_MODELVIEW);
}

//Part 5: Display Callback

GLfloat theta[3] = { 0.0, 0.0, 0.0 };

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    colorcube();
    glutSwapBuffers();
}

//Part 6: Drawing faces

void colorcube(void) {
    
    face(0, 3, 2, 1);
    face(2, 3, 7, 6);
    face(0, 4, 7, 3);
    face(1, 2, 6, 5);
    face(4, 5, 6, 7);
    face(0, 1, 5, 4);
}

//Part 7: Drawing a face

void face(int a, int b, int c, int d){
    
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

//Part 8: Animation

Glfloat delta = 2.0;
GLint axi = 2;

//float height = 0;
//float weight = 0;

//spin the cube about the axis
void spinCube(){
    
    theta[axis] += delta;
    if(theta[axis] > 360.0)
        theta[axis] -= 360.0;

    //display result
    glutPostRedDisplay();
}

//Part 9: Change axis of rotation
//Mouse callback

void mouse(int btn, int state, int x, int y){
    //Scroll function
    float FoV = initialFoV - 5 * glfwGetMouseWheel();
    
    if((btn == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
        axis = 0;
    if((btn == GLUT_MIDDLE_BUTTON) && (state == GLUT_DOWN))
        axis = 1;
    if((btn == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
        axis = 2;
}

//PART 10: Toggle Rotation or Exit
//Keyboard functions

void keyboard(unsigned char key, int x, int y){
    
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);
    
    if(key == 'q' || key == 'Q'){
        exit(0);
    }
    if(key == ' '){
        stop = !stop;
    }
    if(stop){
        glutIdleFunc(NULL);
    }
    // Move forward
    if (glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS){
            position += direction * deltaTime * speed;
    }
    // Move backward
    if (glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS){
        position -= direction * deltaTime * speed;
    }
    // Move right
    if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){
        position += right * deltaTime * speed;
    }
    // Move left
    if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS){
        position -= right * deltaTime * speed;
    }
    else
        glutIdleFunc(spinCube);
}

//Functions:

void myReshape(int argc, char **argv){
    
    GLfloat aspect = (GLfloat) w / (GLfloat) h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(w <= h){
        glOrtho(-2.0, 2.0, -2 / aspet, 2.0 / aspect, -10.0, 10.0);
    else
        glOrtho(-2.0* aspect, 2.0 * aspect, -2.0, 2.0, -10.0, 10.0);
        glMatrixMode(GL_MODELVIEW);
    }
    
}

void display(void){
    
    glClear(GL_COLOR_BUFFER | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(height, weight, 0);
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    colorcube();
    glutSwapBuffers();
    
}

void spinCube(){
    
    theta[axis] += delta;
    if(theta[axis] > 360.0){
        theta[axis] -= 360.0;
        glutPostRedisplay();
    }
    
}



