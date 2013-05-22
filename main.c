#include "structs.h"
#include "catmullclark.c"
#include "exporter.c"
int smooth=0;
GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; //set the light specular to white
GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0}; //set the light ambient to black
GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0}; //set the diffuse light to white
GLfloat light_position[] = { 4.0, 0.0, 0.0, 0.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 500.0 };


void init(void)
{
	glClearColor (0.2, 0.2, 0.2, 0.0);
	//glShadeModel (GL_FLAT);
	//glEnable (GL_DEPTH_TEST);
	//glEnable (GL_LIGHTING);
	//glEnable (GL_LIGHT0);

}
void light (void) {
	//glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//~ glLightfv(GL_LIGHT1, GL_SPECULAR, whiteSpecularLight);
	//~ glLightfv(GL_LIGHT1, GL_AMBIENT, blackAmbientLight);
	//~ glLightfv(GL_LIGHT1, GL_DIFFUSE, whiteDiffuseLight);
	//~ glLightfv(GL_LIGHT1, GL_POSITION, light_position);

	//~ glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//~ glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


}


void showOriginal(){
	int i=3;
	glColor3f(1.0,1.0,1.0);
	for (i=0;i<fIndex ;i++)
	{
		glBegin(GL_LINE_LOOP);
			glVertex3f(vertices[faces[i].vert1].x,vertices[faces[i].vert1].y,vertices[faces[i].vert1].z);
			glVertex3f(vertices[faces[i].vert2].x,vertices[faces[i].vert2].y,vertices[faces[i].vert2].z);
			glVertex3f(vertices[faces[i].vert3].x,vertices[faces[i].vert3].y,vertices[faces[i].vert3].z);
			glVertex3f(vertices[faces[i].vert4].x,vertices[faces[i].vert4].y,vertices[faces[i].vert4].z);
		glEnd();
	}
}

void showAxis(){
	glColor3f(1,0,0);
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(10,0,0);
	glEnd();
	glColor3f(0,1,0);
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f( 0,10,0);
	glEnd();
	glColor3f(0,0,1);
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(0,0,10);
	glEnd();
} 

void display(void){
	int i;
	glClear (GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glRotatef(1,0,1,0);
	showAxis();
	if (!smooth){
		showOriginal();
	}
	else {
		//showOriginal();
		glColor3f(1,1,1);
		showSubdiv();
	}

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
	glViewport (0,0,(GLsizei) w,(GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 1000.0);
	gluLookAt(0,5,10,0,0,0,0,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
	subdivide();
#define SubD	
	export();
	light();
#ifdef PRINTALL
	printf("\n-----------------AFtER SUBDIVIDING--------------------------------\n");
#endif
	printReport();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
