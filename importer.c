/*
 * importer.c
 * 
 * Copyright 2013 Tanmay <binaykiya.tanmay@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 * input filename hardcoded into code
 * input file line size should not exceed 128 characters
 * 		line starting with ' ' or '#'  is treated as a comment
 * 		line starting with v should contain 3 parameters (x, y, z)seperated by a ','character. 
 * 		line starting with f should contain 4 parameters (vertex1, vertex2, vertex3, vertex4) all in the clockwise order seperated by a ','character
 */



#include "structs.h"



void input(){
	static const char filename[] = "objects/input3.txt";
	FILE *file = fopen ( filename, "r" );
	

	if (file != NULL)
	{
		char line [ 128 ]; 
		int i;
			
		while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
			{
				if (line[0]=='#' || line[0]==' ' || line[0]=='\n'   ){
					continue;
				}
				else if(line[0]=='v'){
					float x,y,z;
					sscanf (line,"v %f,%f,%f ",&x, &y, &z);
					//~ printf("V[%d]: x= %4.2f, y= %4.2f, z= %4.2f \n",vIndex,x,y,z);
					createVertex(vIndex,x,y,z);
					vIndex++;
				}
				else if(line[0]=='f'){
					int v1,v2,v3,v4;
					sscanf (line,"f %d,%d,%d,%d ",&v1, &v2, &v3, &v4);
					//~ printf("Face found: v1= %d, v2= %d, v3=%d, v4=%d  \n",v1,v2,v3,v4);
					
					if (v1>vIndex || v2>vIndex || v3>vIndex || v4>vIndex )
					{
						//~ printf("Invalid Vertex Index \n");
					}
					else{
						//~ printf("BEFORE findex : %d, eIndex : %d\n",fIndex,eIndex);
						faces[fIndex].edge1=-1;
						faces[fIndex].edge2=-1;
						faces[fIndex].edge3=-1;
						faces[fIndex].edge4=-1;
						
						faces[fIndex].vert1=v1;
						faces[fIndex].vert2=v2;							//			Vertices set
						faces[fIndex].vert3=v3;
						faces[fIndex].vert4=v4;
						
						eIndex=createEdge(fIndex,1,eIndex,v1, v2);
						eIndex=createEdge(fIndex,2,eIndex,v2, v3);
						eIndex=createEdge(fIndex,3,eIndex,v3, v4);		//			Edges Set
						eIndex=createEdge(fIndex,4,eIndex,v4, v1);
						
						fIndex++;
#ifdef PRINTALL
						printf("AFter findex : %d, eIndex : %d \n",fIndex,eIndex);
#endif			
					}	
				}
				else {
#ifdef PRINTALL
					 printf("INVALID LINE :  \t");
#endif			
					 fputs ( line, stdout ); /* write the line */
				}
			}
#ifdef PRINTALL
			printf("INPUT COMPLETE \n \tVertices scanned:\t %d \n \t Faces Scanned: \t %d \n Edges Scanned:\t %d \n",vIndex,fIndex,eIndex);
			printReport();
			printf("Face1 > %d, %d \n",edges[faces[1].edge3].vert1,edges[faces[1].edge3].vert2);
#endif
			fclose ( file );
	}
	else
	{
		perror ( filename ); /* why didn't the file open? */
	}
}

void createVertex(int i,float x,float y,float z){
	//~ printf("Create Vertex: \n");
	
	
	vertices[i].x=x;
	vertices[i].y=y;
	vertices[i].z=z;
	
	vertices[i].edge1=-1;
	vertices[i].edge2=-1;
	vertices[i].edge3=-1;
	vertices[i].edge4=-1;

	vertices[i].face1=-1;
	vertices[i].face2=-1;
	vertices[i].face3=-1;
	vertices[i].face4=-1;
	//~ printf("All SET \n");
}

int createEdge(int fIndex,int edgeFace, int edgeIndex,int v1, int v2){
	int i;

	for (i=0;i<=edgeIndex; i++){
		//FIND A COMMON EDGE
		
		if((v1==edges[i].vert1 && v2==edges[i].vert2 )||(v2==edges[i].vert1 && v1==edges[i].vert2 )){
			//~ printf("Common Edge FOUND: \n\t");
			
			
			switch(edgeFace){
				case(1):
				faces[fIndex].edge1=i;
				addFacetoEdge(fIndex,i);
				addFacetoVertex(v1,fIndex);
				addFacetoVertex(v2,fIndex);
				//~ printf("EdgeIndex %d, FaceEdgeIndex %d, Vertex1 %d, Vertex2 %d \n",edgeIndex, faces[fIndex].edge1, edges[faces[1].edge1].vert1, edges[faces[1].edge1].vert2);
				break;

				case(2):
				faces[fIndex].edge2=i;
				addFacetoEdge(fIndex,i);
				addFacetoVertex(v1,fIndex);
				addFacetoVertex(v2,fIndex);
				//~ printf("EdgeIndex %d, FaceEdgeIndex %d, Vertex1 %d, Vertex2 %d \n",edgeIndex, faces[fIndex].edge2, edges[faces[1].edge2].vert1, edges[faces[1].edge2].vert2);
				break;

				case(3):
				faces[fIndex].edge3=i;
				addFacetoEdge(fIndex,i);
				addFacetoVertex(v1,fIndex);
				addFacetoVertex(v2,fIndex);
				//~ printf("EdgeIndex %d, FaceEdgeIndex %d, Vertex1 %d, Vertex2 %d \n",edgeIndex, faces[fIndex].edge3, edges[faces[1].edge3].vert1, edges[faces[1].edge3].vert2);
				break;

				case(4):
				faces[fIndex].edge4=i;
				addFacetoEdge(fIndex,i);
				addFacetoVertex(v1,fIndex);
				addFacetoVertex(v2,fIndex);
				//~ printf("EdgeIndex %d, FaceEdgeIndex %d, Vertex1 %d, Vertex2 %d \n",edgeIndex, faces[fIndex].edge4, edges[faces[1].edge4].vert1, edges[faces[1].edge4].vert2);
				break;
			}
		return edgeIndex;
		}
	}
	edgeIndex++;
	edges[edgeIndex].face1=-1;
	edges[edgeIndex].face2=-1;

	edges[edgeIndex].vert1=-1;
	edges[edgeIndex].vert2=-1;

	//~ printf("BEFORE Edge %d : face1: %d \n",edgeIndex,edges[edgeIndex].face1);
	//~ printf("BEFORE Edge %d : face2: %d \n",edgeIndex,edges[edgeIndex].face2);

	addEdgetoVertex(v1,edgeIndex);
	addEdgetoVertex(v2,edgeIndex);

	addFacetoVertex(v1,fIndex);
	addFacetoVertex(v2,fIndex);

	edges[edgeIndex].vert1=v1;
	edges[edgeIndex].vert2=v2;


	switch(edgeFace){
		case(1):
		faces[fIndex].edge1=edgeIndex;
		addFacetoEdge(fIndex,edgeIndex);
		//~ printf("NEW Edge\n  EdgeIndex %d, FaceEdgeIndex %d, Vertex1 %d, Vertex2 %d \n",edgeIndex, faces[fIndex].edge1, edges[faces[1].edge1].vert1, edges[faces[1].edge1].vert2);
		break;

		case(2):
		faces[fIndex].edge2=edgeIndex;
		addFacetoEdge(fIndex,edgeIndex);
		//~ printf("NEW Edge\n  EdgeIndex %d, FaceEdgeIndex %d, Vertex1 %d, Vertex2 %d \n",edgeIndex, faces[fIndex].edge2, edges[faces[1].edge2].vert1, edges[faces[1].edge2].vert2);
		break;

		case(3):
		faces[fIndex].edge3=edgeIndex;
		addFacetoEdge(fIndex,edgeIndex);
		//~ printf("NEW Edge\n  EdgeIndex %d, FaceEdgeIndex %d, Vertex1 %d, Vertex2 %d \n",edgeIndex, faces[fIndex].edge3, edges[faces[1].edge3].vert1, edges[faces[1].edge3].vert2);
		break;

		case(4):
		faces[fIndex].edge4=edgeIndex;
		addFacetoEdge(fIndex,edgeIndex);
		//~ printf("NEW Edge\n  EdgeIndex %d, FaceEdgeIndex %d, Vertex1 %d, Vertex2 %d \n",edgeIndex, faces[fIndex].edge4, edges[faces[1].edge4].vert1, edges[faces[1].edge4].vert2);
		break;
		
		}

	return edgeIndex;
}


void addEdgetoVertex(int v,int e){
	//~ printf("in add edge e:%d, v:%d, edge1=%d, edge2=%d, edge3=%d, edge4=%d",e,v,vertices[v].edge1,vertices[v].edge2,vertices[v].edge3,vertices[v].edge4);	
	
	if (vertices[v].edge1==-1){
		vertices[v].edge1=e;
		//~ printf("E1 added to v no. %d \n",v);
	}
	else if (vertices[v].edge2==-1){
		vertices[v].edge2=e;
		//~ printf("E2 added to v no. %d \n",v);
	}
	else if (vertices[v].edge3==-1){
		vertices[v].edge3=e;
		//~ printf("E3 added to v no. %d \n",v);
	}
	else if (vertices[v].edge4==-1){
		vertices[v].edge4=e;
		//~ printf("E4 added to v no. %d \n",v);
	}
	else {
		//~ printf("\t none added SOME ERROR\n");
	}
}

void addFacetoVertex(int v,int f){
#ifdef PRINTALL
	printf("in Add Face to vertex; v:%d f:%d \n \t",v,f);	
#endif
	if((vertices[v].face1!=f)&&(vertices[v].face2!=f)&&(vertices[v].face3!=f)&&(vertices[v].face4!=f)){
		if (vertices[v].face1==-1){
			vertices[v].face1=f;
#ifdef PRINTALL
			printf("F1 added \n");
#endif
		}
		else if (vertices[v].face2==-1){
			vertices[v].face2=f;
#ifdef PRINTALL
			printf("F2 added \n");
#endif
		}
		else if (vertices[v].face3==-1){
			vertices[v].face3=f;
#ifdef PRINTALL
			printf("F3 added \n");
#endif
		}
		else if (vertices[v].face4==-1){
			vertices[v].face4=f;
#ifdef PRINTALL
			printf("F4 added \n");
#endif
		}
	}
	else{
#ifdef PRINTALL
		printf("Duplicate Avoided \n");
#endif
	}
}

addFacetoEdge(int f, int e){
	//~ if (e==20 || e==21){
		//~ printf("-----------------------------\n Edge %d, face %d \n",e,f);
	//~ }
	
	if(edges[e].face1==-1){
		edges[e].face1=f;
	}
	else{
		edges[e].face2=f;
	}
	{
		//~ printf("Edge %d : face1: %d \n",e,edges[e].face1);
		//~ printf("Edge %d : face2: %d \n",e,edges[e].face2);
	}
}
void printReport(){
#ifdef PRINTALL
	int i=0;
	printf("VERTICES--------------------------------------------------");
	for (i=0;i<vIndex; i++){
		printf("\nVertex%d: (%4.2f,%4.2f,%4.2f)",i,vertices[i].x,vertices[i].y,vertices[i].z);
		printf("\n \t Faces: %d,%d,%d,%d ",vertices[i].face1, vertices[i].face2, vertices[i].face3, vertices[i].face4);
		printf("\n \t Edges: %d,%d,%d ",vertices[i].edge1,vertices[i].edge2,vertices[i].edge3,vertices[i].edge4);
		printf("\n \t New Value(%4.2f,%4.2f,%4.2f)",vertices[i].newVertX,vertices[i].newVertX,vertices[i].newVertZ);
		
	}
	printf("\nEDGES-----------------------------------------------------\n");
	for (i=0;i<eIndex; i++){
		printf("\nEdge %d",i);
		printf("\n \t Vertices : %d,%d",edges[i].vert1,edges[i].vert2);
		printf("\n \t Faces : %d,%d",edges[i].face1,edges[i].face2);
		printf("\n \t NewEdgePoint : (%4.2f,%4.2f,%4.2f)",edges[i].newEdgeX,edges[i].newEdgeY,edges[i].newEdgeZ);
		
	}		
	printf("\nFACES-----------------------------------------------------\n");
	for (i=0;i<fIndex;i++){
		printf("\nFace: %d",i);
		printf("\n \t Vertices : %d,%d,%d,%d",faces[i].vert1,faces[i].vert2,faces[i].vert3,faces[i].vert4);
		printf("\n \t Edges : %d,%d",faces[i].edge1,faces[i].edge2,faces[i].edge3,faces[i].edge4);
		printf("\n \t NewFacePoint : (%4.2f,%4.2f,%4.2f)",faces[i].newFaceX,faces[i].newFaceY,faces[i].newFaceZ);
	}
	printf("\n----------------------------------------------------------\n");
#endif
}
