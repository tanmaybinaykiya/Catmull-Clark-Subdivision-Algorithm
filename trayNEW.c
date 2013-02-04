#include <stdio.h>
#include "inputops.c"
//#include "computeAll.c"
#include<stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

int smooth=0;

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
}
void showOriginal(){
	int i;
	for (i=0;i<fIndex;i++)
	{
		glColor3f((float)i/5,(float)(5-i)/5,0);
		glBegin(GL_POLYGON);
			glVertex3f(vertices[faces[i].e1.v1].x,vertices[faces[i].e1.v1].y,vertices[faces[i].e1.v1].z);
			glVertex3f(vertices[faces[i].e2.v1].x,vertices[faces[i].e2.v1].y,vertices[faces[i].e2.v1].z);
			glVertex3f(vertices[faces[i].e3.v1].x,vertices[faces[i].e3.v1].y,vertices[faces[i].e3.v1].z);
			glVertex3f(vertices[faces[i].e4.v1].x,vertices[faces[i].e4.v1].y,vertices[faces[i].e4.v1].z);
		glEnd();
	}

}
void showSubdiv(){
	int i;
	for (i=0;i<fIndex;i++)
	{
		glColor3f((float)i/5,(float)(5-i)/5,0);
		glBegin(GL_POLYGON);
			glVertex3f(faces[i].facePt.x,faces[i].facePt.y,faces[i].facePt.z);
			glVertex3f(faces[i].e1.mid.x,faces[i].e1.mid.y,faces[i].e1.mid.z);
//			glVertex3f(vertices[faces[i].e1.v2].newVert.x,vertices[faces[i].e1.v2].newVert.y,vertices[faces[i].e1.v2].newVert.z);
			glVertex3f(faces[i].e2.mid.x,faces[i].e2.mid.y,faces[i].e2.mid.z);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(faces[i].facePt.x,faces[i].facePt.y,faces[i].facePt.z);
			glVertex3f(faces[i].e2.mid.x,faces[i].e2.mid.y,faces[i].e2.mid.z);
//			glVertex3f(vertices[faces[i].e2.v2].newVert.x,vertices[faces[i].e2.v2].newVert.y,vertices[faces[i].e2.v2].newVert.z);
			glVertex3f(faces[i].e3.mid.x,faces[i].e3.mid.y,faces[i].e3.mid.z);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(faces[i].facePt.x,faces[i].facePt.y,faces[i].facePt.z);
			glVertex3f(faces[i].e3.mid.x,faces[i].e3.mid.y,faces[i].e3.mid.z);
//			glVertex3f(vertices[faces[i].e3.v2].newVert.x,vertices[faces[i].e3.v2].newVert.y,vertices[faces[i].e3.v2].newVert.z);
			glVertex3f(faces[i].e4.mid.x,faces[i].e4.mid.y,faces[i].e4.mid.z);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(faces[i].facePt.x,faces[i].facePt.y,faces[i].facePt.z);
			glVertex3f(faces[i].e4.mid.x,faces[i].e4.mid.y,faces[i].e4.mid.z);
//			glVertex3f(vertices[faces[i].e4.v2].newVert.x,vertices[faces[i].e4.v2].newVert.y,vertices[faces[i].e4.v2].newVert.z);
			glVertex3f(faces[i].e1.mid.x,faces[i].e1.mid.y,faces[i].e1.mid.z);
		glEnd();
	}
}

void display(void){
	int i;
	glClear (GL_COLOR_BUFFER_BIT);
	//glLoadIdentity();
	glFrontFace(GL_CW);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	
	//glPolygonMode(GL_FRONT, GL_FILL);
	//glPolygonMode(GL_BACK, GL_POINTS);
	
	//glTranslatef(-0.5,0,0);
	//glRotatef(30,1,1,0.5);
	glRotatef(1,0.1,1,.1);
	if (!smooth)
	showOriginal();
	else 
	showSubdiv();
	
		glBegin(GL_LINES);
	
		glVertex3f(0,0,0);
		glVertex3f(10,0,0);

		glVertex3f(0,0,0);
		glVertex3f( 0,10,0);

		glVertex3f(0,0,0);
		glVertex3f(0,0,10);

	glEnd();		
	
	glutSwapBuffers();
	usleep(1000);
	glutPostRedisplay();
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			exit(0);
			break;
		case 'n':
			smooth=!smooth;
			glutPostRedisplay();
			break;
			
	}
}
void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 1000.0);
	gluLookAt(0,0,5,0,0,0,0,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//glScalef(0.2,.2,.2);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	input();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
