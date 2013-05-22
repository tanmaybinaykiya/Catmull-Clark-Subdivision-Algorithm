#include "structs.h"
#include "importer.c"

void subdivide()
{ 
	int i;
	for(i=0;i<=fIndex;i++){
		
		faces[i].newFaceX=.25*(vertices[faces[i].vert1].x+vertices[faces[i].vert2].x+vertices[faces[i].vert3].x+vertices[faces[i].vert4].x);
		faces[i].newFaceY=.25*(vertices[faces[i].vert1].y+vertices[faces[i].vert2].y+vertices[faces[i].vert3].y+vertices[faces[i].vert4].y);
		faces[i].newFaceZ=.25*(vertices[faces[i].vert1].z+vertices[faces[i].vert2].z+vertices[faces[i].vert3].z+vertices[faces[i].vert4].z);
	}
	for (i=0;i<=eIndex;i++){
		if((edges[i].face2!=-1)&&(edges[i].face1!=-1)){
			//~ printf("Edge %d has 2 faces: %d and %d \n",i,edges[i].face1,edges[i].face2);
			edges[i].newEdgeX=0.25*(vertices[edges[i].vert1].x  + vertices[edges[i].vert2].x + faces[edges[i].face1].newFaceX + faces[edges[i].face2].newFaceX );
			edges[i].newEdgeY=0.25*(vertices[edges[i].vert1].y  + vertices[edges[i].vert2].y + faces[edges[i].face1].newFaceY + faces[edges[i].face2].newFaceY );
			edges[i].newEdgeZ=0.25*(vertices[edges[i].vert1].z  + vertices[edges[i].vert2].z + faces[edges[i].face1].newFaceZ + faces[edges[i].face2].newFaceZ );
		}
		else{
#ifdef PRINTALL		
			printf("Edge %d has 1 face: %d \n",i,edges[i].face1);
#endif			
			edges[i].newEdgeX=(0.5*vertices[edges[i].vert1].x  + 0.5*vertices[edges[i].vert2].x /*+ 0.5*faces[edges[i].face1].newFaceX */);
			edges[i].newEdgeY=(0.5*vertices[edges[i].vert1].y  + 0.5*vertices[edges[i].vert2].y /*+ 0.5*faces[edges[i].face1].newFaceY */);
			edges[i].newEdgeZ=(0.5*vertices[edges[i].vert1].z  + 0.5*vertices[edges[i].vert2].z /*+ 0.5*faces[edges[i].face1].newFaceZ */);
		}
	}	
	for (i=0;i<=vIndex;i++){
		int v1,v2,v3,v4,f1,f2,f3,f4;
		float qx,qy,qz,rx,ry,rz;
		// Q=.25*(q11+q13+q31+q33
		// R=0.25*((2*Porig)+.5*(p12+p21+p23p+p32))
		// Pnew= Q/4+ R/2 + Porig/4
			vertices[i].newVertX=vertices[i].x;
			vertices[i].newVertY=vertices[i].y;
			vertices[i].newVertZ=vertices[i].z;

		if(vertices[i].face3!=-1){
#ifdef PRINTALL		
			printf("Vertex %d has 3 faces: %d, %d, %d \n",i,vertices[i].face3,vertices[i].face2,vertices[i].face1);
#endif
			qx=0.25*(faces[vertices[i].face1].newFaceX+  faces[vertices[i].face2].newFaceX+  faces[vertices[i].face3].newFaceX+  faces[vertices[i].face4].newFaceX);
			qy=0.25*(faces[vertices[i].face1].newFaceY+  faces[vertices[i].face2].newFaceY+  faces[vertices[i].face3].newFaceY+  faces[vertices[i].face4].newFaceY);
			qz=0.25*(faces[vertices[i].face1].newFaceZ+  faces[vertices[i].face2].newFaceZ+  faces[vertices[i].face3].newFaceZ+  faces[vertices[i].face4].newFaceZ);
			
			int p1=-1,p2=-1,p3=-1,p4=-1;
			
			if(edges[vertices[i].edge1].vert1==i){
				p1=edges[vertices[i].edge1].vert2;
			}
			else{
				p1=edges[vertices[i].edge1].vert1;
			}

			if(edges[vertices[i].edge2].vert1==i){
				p2=edges[vertices[i].edge2].vert2;
			}
			else{
				p2=edges[vertices[i].edge2].vert1;
			}

			if(edges[vertices[i].edge3].vert1==i){
				p3=edges[vertices[i].edge3].vert2;
			}
			else{
				p3=edges[vertices[i].edge3].vert1;
			}

			if(edges[vertices[i].edge4].vert1==i){
				p4=edges[vertices[i].edge4].vert2;
			}
			else{
				p4=edges[vertices[i].edge4].vert1;
			}

			rx=0.25*(2*(vertices[i].x)+0.5*(vertices[p1].x+vertices[p2].x+vertices[p3].x+vertices[p4].x));
			ry=0.25*(2*(vertices[i].y)+0.5*(vertices[p1].y+vertices[p2].y+vertices[p3].y+vertices[p4].y));
			rz=0.25*(2*(vertices[i].z)+0.5*(vertices[p1].z+vertices[p2].z+vertices[p3].z+vertices[p4].z));
			
			vertices[i].newVertX=(0.25*vertices[i].x)+(qx/4)+(rx/2);
			vertices[i].newVertY=(0.25*vertices[i].y)+(qy/4)+(ry/2);
			vertices[i].newVertZ=(0.25*vertices[i].z)+(qz/4)+(rz/2);
		}
		else{
#ifdef PRINTALL				
						printf("Vertex %d has 3 faces: %d \n",i,vertices[i].face4);
#endif	
			}
	}
}
void showSubdiv(){
	int i=10;
	
	for(i=0;i<fIndex;i++)
	{
		//for every pair of edges, find the common vertex
		
		int v12,v23,v34,v41;
		if(edges[faces[i].edge1].vert1==edges[faces[i].edge2].vert1){
			v12=edges[faces[i].edge1].vert1;
		}
		else if (edges[faces[i].edge1].vert1==edges[faces[i].edge2].vert2){
			v12=edges[faces[i].edge1].vert1;
		}
		else if (edges[faces[i].edge1].vert2==edges[faces[i].edge2].vert2){
			v12=edges[faces[i].edge1].vert2;
		}
		else if(edges[faces[i].edge1].vert2==edges[faces[i].edge2].vert1){
			v12=edges[faces[i].edge1].vert2;
		}
		else{	
			v12=-1; 
#ifdef PRINTALL			
			printf("v12 errror \n");
#endif	
		}

		if(edges[faces[i].edge2].vert1==edges[faces[i].edge3].vert1){
			v23=edges[faces[i].edge2].vert1;
		}
		else if (edges[faces[i].edge2].vert1==edges[faces[i].edge3].vert2){
			v23=edges[faces[i].edge2].vert1;
		}
		else if (edges[faces[i].edge2].vert2==edges[faces[i].edge3].vert2){
			v23=edges[faces[i].edge2].vert2;
		}
		else if(edges[faces[i].edge2].vert2==edges[faces[i].edge3].vert1){
			v23=edges[faces[i].edge2].vert2;
		}
		else{	
		
			v23=-1; 
#ifdef PRINTALL
			printf("v23 errror \n");
#endif
		}


		if(edges[faces[i].edge3].vert1==edges[faces[i].edge4].vert1){
			v34=edges[faces[i].edge3].vert1;
		}
		else if (edges[faces[i].edge3].vert1==edges[faces[i].edge4].vert2){
			v34=edges[faces[i].edge3].vert1;
		}
		else if (edges[faces[i].edge3].vert2==edges[faces[i].edge4].vert2){
			v34=edges[faces[i].edge3].vert2;
		}
		else if(edges[faces[i].edge3].vert2==edges[faces[i].edge4].vert1){
			v34=edges[faces[i].edge3].vert2;
		}
		else{	
			v34=-1; 
#ifdef PRINTALL			
			printf("v34 errror \n");
#endif			
		}


		if(edges[faces[i].edge1].vert1==edges[faces[i].edge4].vert1){
			v41=edges[faces[i].edge1].vert1;
		}
		else if (edges[faces[i].edge1].vert1==edges[faces[i].edge4].vert2){
			v41=edges[faces[i].edge1].vert1;
		}
		else if (edges[faces[i].edge1].vert2==edges[faces[i].edge4].vert2){
			v41=edges[faces[i].edge1].vert2;
		}
		else if(edges[faces[i].edge1].vert2==edges[faces[i].edge4].vert1){
			v41=edges[faces[i].edge1].vert2;
		}
		else{	
			v41=-1; 
#ifdef PRINTALL			
			printf("v41 errror \n");
#endif
		}

/* FOR DEBUGGING: CHECK FOR FACEPOINTS
		glBegin(GL_POINTS);
			glVertex3f(faces[i].newFaceX,faces[i].newFaceY,faces[i].newFaceZ);
		glEnd();
*/

		glBegin(GL_LINE_LOOP);
			glVertex3f(faces[i].newFaceX,faces[i].newFaceY,faces[i].newFaceZ);
			glVertex3f(edges[faces[i].edge1].newEdgeX,edges[faces[i].edge1].newEdgeY,edges[faces[i].edge1].newEdgeZ);
			glVertex3f(vertices[v12].newVertX,vertices[v12].newVertY,vertices[v12].newVertZ );
			glVertex3f(edges[faces[i].edge2].newEdgeX,edges[faces[i].edge2].newEdgeY,edges[faces[i].edge2].newEdgeZ);
			
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(faces[i].newFaceX,faces[i].newFaceY,faces[i].newFaceZ);
			glVertex3f(edges[faces[i].edge2].newEdgeX,edges[faces[i].edge2].newEdgeY,edges[faces[i].edge2].newEdgeZ);
			glVertex3f(vertices[v23].newVertX,vertices[v23].newVertY,vertices[v23].newVertZ );
			glVertex3f(edges[faces[i].edge3].newEdgeX,edges[faces[i].edge3].newEdgeY,edges[faces[i].edge3].newEdgeZ);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(faces[i].newFaceX,faces[i].newFaceY,faces[i].newFaceZ);
			glVertex3f(edges[faces[i].edge3].newEdgeX,edges[faces[i].edge3].newEdgeY,edges[faces[i].edge3].newEdgeZ);
			glVertex3f(vertices[v34].newVertX,vertices[v34].newVertY,vertices[v34].newVertZ );
			glVertex3f(edges[faces[i].edge4].newEdgeX,edges[faces[i].edge4].newEdgeY,edges[faces[i].edge4].newEdgeZ);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(faces[i].newFaceX,faces[i].newFaceY,faces[i].newFaceZ);
			glVertex3f(edges[faces[i].edge4].newEdgeX,edges[faces[i].edge4].newEdgeY,edges[faces[i].edge4].newEdgeZ);
			glVertex3f(vertices[v41].newVertX,vertices[v41].newVertY,vertices[v41].newVertZ );
			glVertex3f(edges[faces[i].edge1].newEdgeX,edges[faces[i].edge1].newEdgeY,edges[faces[i].edge1].newEdgeZ);
		glEnd();
	
	}
 /*FOR DEBUGGING: CHECK FOR EDGEPOINTS	
	for (i=20;i<22;i++)
	{
		glBegin(GL_POINTS);
			glVertex3f(edges[i].newEdgeX,edges[i].newEdgeY,edges[i].newEdgeZ);
		glEnd();
	}
*/
}
