#include <iostream>
#include <sstream>
#include <string>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/GLUT.h"
#include <stdlib.h>
#include <stdio.h>
#include "TGA.h"

void render(GLfloat ambr, GLfloat ambg, GLfloat ambb, 
   GLfloat difr, GLfloat difg, GLfloat difb, 
   GLfloat specr, GLfloat specg, GLfloat specb, GLfloat shine) {
   GLfloat mat[4];

   glPushMatrix();
   mat[0] = ambr; mat[1] = ambg; mat[2] = ambb; mat[3] = 1.0;	
   glMaterialfv (GL_FRONT, GL_AMBIENT, mat);
   mat[0] = difr; mat[1] = difg; mat[2] = difb;	
   glMaterialfv (GL_FRONT, GL_DIFFUSE, mat);
   mat[0] = specr; mat[1] = specg; mat[2] = specb;
   glMaterialfv (GL_FRONT, GL_SPECULAR, mat);
   glMaterialf (GL_FRONT, GL_SHININESS, shine*128.0);

   if(solid==1) //teapot
		
   else{}  //cube
	   
	glPopMatrix();
}

void myReshape(int w, int h)
{
  // Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0) h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(60, ratio, 1, 100);
	glMatrixMode(GL_MODELVIEW);

}

int main(int argc, char **argv) {
   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Texture Mapping");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(NULL);
    glutMouseFunc(mouse);
    glEnable(GL_DEPTH_TEST);
	init();
	
	glGenTextures(2, TextureArray);

	TGA_Texture(TextureArray, "stone.tga", 0);
	TGA_Texture(TextureArray, "logo.tga", 1);
	
    glutKeyboardFunc(key);

    glClearColor(0.0,0.0,0.0,1.0);
	glewInit();
	
	setShaders();
	
	// Texture Units setup
	
    glutMainLoop();
}