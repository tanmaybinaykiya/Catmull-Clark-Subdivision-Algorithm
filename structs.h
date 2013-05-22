#ifndef STRUCTS_H
#define STRUCTS_H


	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include <string.h>
	#include <GL/glut.h>

	struct vertex {
		float x;
		float y;
		float z;
		
		int edge1;
		int edge2;
		int edge3;
		int edge4;
		
		int face1;
		int face2;
		int face3;
		int face4;

		float newVertX;
		float newVertY;
		float newVertZ;
	};

	struct edge{
		int vert1;
		int vert2;
		
		int face1;
		int face2;
		
		float newEdgeX;
		float newEdgeY;
		float newEdgeZ;
	};

	struct face{
		int edge1;
		int edge2;
		int edge3;
		int edge4;

		int vert1;
		int vert2;
		int vert3;
		int vert4;
		
		float newFaceX;
		float newFaceY;
		float newFaceZ;
	};
	
// #define PRINTALL
const int maxVertices=50;
const int maxEdges=50;
const int maxFaces=15;

int vIndex=0, eIndex=0, fIndex=0;

struct vertex typedef vertex;
struct edge typedef edge;
struct face typedef face;


void createVertex(int v,float x,float y,float z);
int createEdge(int fIndex,int edgeFace,int edgeIndex,int v1, int v2);
void addEdgetoVertex(int v1,int edgeIndex);
void addFacetoVertex(int v1,int faceIndex);
//void addFacetoEdge(int fIndex,int i);
void printReport();
void createFace();

vertex vertices[100];
edge edges[50];
face faces[50];


#endif
