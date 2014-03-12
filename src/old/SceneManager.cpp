void init(void) {
   GLfloat ambient[] = { 0.1, 0.1, 0.1, 1.0 };
   GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    
   GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
   GLfloat local_view[] = { 0.0 };

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

   
   glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,0.0);
   glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,0.025);
   glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION,0.002);  
    
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

   /* Setup cube vertex data */
	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -1;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = 1;
}

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