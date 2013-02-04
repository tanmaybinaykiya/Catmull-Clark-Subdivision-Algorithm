#include<stdio.h>
#include<stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
float vertices[20][3]={
							{0,1,0},{0,1,-1},{1,0,0},{1,0,-1},{2,0,0},{2,0,-1},{3,0,0},{3,0,-1},{4,1,0},{4,1,-1},

							{0,1,-2},{0,1,-3},{1,0,-2},{1,0,-3},{2,0,-2},{2,0,-3},{3,0,-2},{3,0,-3},{4,1,-2},{4,1,-3}
						};
float facePoints[12][3];
float edgePoints[17][3];
float vertexPoints[6][3];
int before=1;

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
}
void subdivide(){
	int i=0,j=0,k=0;
	/****************FACE POINTS        */	
	while (j<4)
	{
		facePoints[j][0]=(vertices[i][0]+vertices[i+1][0]+vertices[i+2][0]+vertices[i+3][0])/4;
		facePoints[j][1]=(vertices[i][1]+vertices[i+1][1]+vertices[i+2][1]+vertices[i+3][1])/4;
		facePoints[j][2]=(vertices[i][2]+vertices[i+1][2]+vertices[i+2][2]+vertices[i+3][2])/4;
		//printf("%f, %f, %f \n",facePoints[j][0],facePoints[j][1],facePoints[j][2] );
		i=i+2;
		j++;
	}
	
	j=8;
	i=0;
	while (j<12)
	{
		facePoints[j][0]=(vertices[i+10][0]+vertices[i+11][0]+vertices[i+12][0]+vertices[i+13][0])/4;
		facePoints[j][1]=(vertices[i+10][1]+vertices[i+11][1]+vertices[i+12][1]+vertices[i+13][1])/4;
		facePoints[j][2]=(vertices[i+10][2]+vertices[i+11][2]+vertices[i+12][2]+vertices[i+13][2])/4;
		//printf("%f, %f, %f \n",facePoints[j][0],facePoints[j][1],facePoints[j][2] );
		i=i+2;
		j++;
	}
	j=4;
	i=1;
	while(j<8)
	{
		facePoints[j][0]=(vertices[i][0]+vertices[i+9][0]+vertices[i+2][0]+vertices[i+11][0])/4;
		facePoints[j][1]=(vertices[i][1]+vertices[i+9][1]+vertices[i+2][1]+vertices[i+11][1])/4;
		facePoints[j][2]=(vertices[i][2]+vertices[i+9][2]+vertices[i+2][2]+vertices[i+11][2])/4;
		//printf("%f, %f, %f \n",facePoints[j][0],facePoints[j][1],facePoints[j][2] );
		i=i+2;
		j++;
	}
	/****************EDGE POINTS        */
	i=0;
	int v=1;
	j=0;
	while(j<4){
	edgePoints[j][0]=(facePoints[i][0]+facePoints[i+4][0]+vertices[v][0]+vertices[v+2][0])/4;
	edgePoints[j][1]=(facePoints[i][1]+facePoints[i+4][1]+vertices[v][1]+vertices[v+2][1])/4;
	edgePoints[j][2]=(facePoints[i][2]+facePoints[i+4][2]+vertices[v][2]+vertices[v+2][2])/4;
	
	edgePoints[j+4][0]=(facePoints[i+4][0]+facePoints[i+8][0]+vertices[v+9][0]+vertices[v+11][0])/4;
	edgePoints[j+4][1]=(facePoints[i+4][1]+facePoints[i+8][1]+vertices[v+9][1]+vertices[v+11][1])/4;
	edgePoints[j+4][2]=(facePoints[i+4][2]+facePoints[i+8][2]+vertices[v+9][2]+vertices[v+11][2])/4;
	
	printf("j=%d And (%f, %f, %f) \n",j,edgePoints[j][0],edgePoints[j][1],edgePoints[j][2] );
	printf("j=%d And (%f, %f, %f) \n",j+4,edgePoints[j+4][0],edgePoints[j+4][1],edgePoints[j+4][2] );

	j++;
	i++;
	v+=2;
	}
	
	i=0,j=8,v=2;
	while(j<17){
		edgePoints[j][0]=(facePoints[i][0]+facePoints[i+1][0]+vertices[v][0]+vertices[v+1][0])/4;
		edgePoints[j][1]=(facePoints[i][1]+facePoints[i+1][1]+vertices[v][1]+vertices[v+1][1])/4;
		edgePoints[j][2]=(facePoints[i][2]+facePoints[i+1][2]+vertices[v][2]+vertices[v+1][2])/4;
		
		printf("j=%d And (%f, %f, %f) \n",j,edgePoints[j][0],edgePoints[j][1],edgePoints[j][2] );
		v+=2;
		i++;
		j++;
		}
		
		
		
	/*******************VERTEX POINTS          **************/
	i=1,j=0,k=0,v=3;
printf("asdf");
	while(j<3){
		
		vertexPoints[j][0]=(.5*vertices[v][0]) + ((vertices[i][0]+vertices[i+1][0]+vertices[i+4][0]+vertices[i+11][0])/16)  +  ((facePoints[k][0]+facePoints[k+1][0]+facePoints[k+4][0]+facePoints[k+5][0])/16);
		vertexPoints[j][1]=(.5*vertices[v][1]) + ((vertices[i][1]+vertices[i+1][1]+vertices[i+4][1]+vertices[i+11][1])/16)  +  ((facePoints[k][1]+facePoints[k+1][1]+facePoints[k+4][1]+facePoints[k+5][1])/16);
		vertexPoints[j][2]=(.5*vertices[v][2]) + ((vertices[i][2]+vertices[i+1][2]+vertices[i+4][2]+vertices[i+11][2])/16)  +  ((facePoints[k][2]+facePoints[k+1][2]+facePoints[k+4][2]+facePoints[k+5][2])/16);
		printf("Vertex Points assigned as  %f, %f, %f \n",vertexPoints[j][0],vertexPoints[j][1],vertexPoints[j][2] );

		j++;
		v+=2;
		i+=2;
		k++;	
	}
	i=0,v=12,k=4;
	j=3;
	
	while(j<6)
	{
		vertexPoints[j][0]=(.5*vertices[v][0]) + ((vertices[i][0]+vertices[i+10][0]+vertices[i+13][0]+vertices[i+14][0])/16)  +  ((facePoints[k][0]+facePoints[k+1][0]+facePoints[k+4][0]+facePoints[k+5][0])/16);
		vertexPoints[j][1]=(.5*vertices[v][1]) + ((vertices[i][1]+vertices[i+10][1]+vertices[i+13][1]+vertices[i+14][1])/16)  +  ((facePoints[k][1]+facePoints[k+1][1]+facePoints[k+4][1]+facePoints[k+5][1])/16);
		vertexPoints[j][2]=(.5*vertices[v][2]) + ((vertices[i][2]+vertices[i+10][2]+vertices[i+13][2]+vertices[i+14][2])/16)  +  ((facePoints[k][2]+facePoints[k+1][2]+facePoints[k+4][2]+facePoints[k+5][2])/16);
		printf("Vertex Points assigned as  %f, %f, %f \n",vertexPoints[j][0],vertexPoints[j][1],vertexPoints[j][2] );
		j++;
		v+=2;
		i+=2;
		k++;	
	}

}
void subdividedShow(){
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	int face=0,vert=0,edg=0;
	glBegin(GL_QUAD_STRIP);
		while(face<3){
			glVertex3fv(facePoints[face]);
			glVertex3fv(edgePoints[edg]);
			glVertex3fv(edgePoints[edg+8]);
			glVertex3fv(vertexPoints[vert]);
			
			printf("F %f, %f, %f \n",facePoints[face][0],facePoints[face][1],facePoints[face][2] );
			printf("E %f, %f, %f \n",edgePoints[edg][0],edgePoints[edg][1],edgePoints[edg][2] );			
			printf("E %f, %f, %f \n",edgePoints[edg+8][0],edgePoints[edg+8][1],edgePoints[edg+8][2] );			
			printf("V %f, %f, %f \n",vertexPoints[vert][0],vertexPoints[vert][1],vertexPoints[vert][2] );			
			face++;
			vert++;
			edg++;
		}
			glVertex3fv(facePoints[face]);
			glVertex3fv(edgePoints[edg]);
	glEnd();
	face=8;
	edg=4;
	vert=3;
	glBegin(GL_LINE_STRIP);
//		while(face<12){
			glVertex3fv(edgePoints[edg]);
			glVertex3fv(facePoints[face]);
			glVertex3fv(vertexPoints[vert]);
			glVertex3fv(edgePoints[edg+1]);

			printf("F %f, %f, %f \n",facePoints[face][0],facePoints[face][1],facePoints[face][2] );
			printf("E %f, %f, %f \n",edgePoints[edg][0],edgePoints[edg][1],edgePoints[edg][2] );			
			printf("E %f, %f, %f \n",edgePoints[edg+10][0],edgePoints[edg+10][1],edgePoints[edg+10][2] );			
			printf("V %f, %f, %f \n",vertexPoints[vert][0],vertexPoints[vert][1],vertexPoints[vert][2] );			
			face++;
			vert++;
			edg++;
//		}
//			glVertex3fv(facePoints[face]);
//			glVertex3fv(edgePoints[edg]);
	glEnd();

	
	glutSwapBuffers();
}
void display(void)
	{
		int i;
	//~ for (i=0;i<20;i++)
	//~ printf("%f, %f,%f \n",vertices[i][0],vertices[i][1],vertices[i][2]);
	
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,0);
	
	if (before){
		glBegin(GL_QUAD_STRIP);
			for (i=0;i<10;i++)
			glVertex3fv(vertices[i]);
		glEnd();

		glBegin(GL_QUAD_STRIP);
			for (i=10;i<20;i++)
			glVertex3fv(vertices[i]);
		glEnd();

		glBegin(GL_QUAD_STRIP);
			for (i=1;i<10;i++)
			{	
				glVertex3fv(vertices[i]);
				glVertex3fv(vertices[i+9]);
				i++;
			}	
		glEnd();
		glutSwapBuffers();
	
	}
	else{
		subdivide(vertices);
		subdividedShow();
		
	}
	
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			exit(0);
			break;
		case 'n':
			before=0;
			
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
	gluLookAt(0,5,5,0,0,0,0,1,0);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(-2,0,0);
	 //glScalef(2,2,2);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
