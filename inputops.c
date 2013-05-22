// This code implements the Catmull CLark Algorithm to subdivide a polygonal mesh into a smoother subdivisional mesh.
// Limitations : 	The max number of vertices, faces has to be harcoded. 
// 					The edge points are duplicated.
//					The faces are defined using vertex indices in the C/AC direction of the vertex face
// Input File Format
//		LINE SIZE should be less than 128
//		All Indices (face and vertices) start from 0
//		Vertex format: v x,y,z 
//		quad format: f v1,v2,v3,v4 
//	EDGE POINT CALCULATION IS WRONG:  facePt Computation remaining
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct vertex typedef vertex;
struct quad typedef quad;
struct edge typedef edge;

struct simpleVert{
	float x;
	float y;
	float z;
	
}typedef sVertex;

struct vertex{
	float x;
	float y;
	float z;
	
	int quad1;
	int quad2;
	int quad3;
	int quad4;
	
	edge *edge1;
	edge *edge2;
	edge *edge3;
	edge *edge4;
	
	sVertex newVert;
};


struct edge{
	int v1;
	int v2;
	
	vertex mid;
};
	

struct quad{
	edge e1;
	edge e2;
	edge e3;
	edge e4;

	sVertex facePt;
};

int vIndex=0,fIndex=0;
//const int maxVertices=50;
vertex vertices[50];
quad faces[10];


addVertex(int index,float X,float Y,float Z){
	vertices[index].x=X;
	vertices[index].y=Y;
	vertices[index].z=Z;
	
	vertices[index].quad1=-1;
	vertices[index].quad2=-1;
	vertices[index].quad3=-1;
	vertices[index].quad4=-1;
	
	vertices[index].edge1=NULL;
	vertices[index].edge2=NULL;
	vertices[index].edge3=NULL;
	vertices[index].edge4=NULL;
}
void addFace(int F, int V){

	if(vertices[V].quad1==-1){
		vertices[V].quad1=F;
	}
	else if	(vertices[V].quad2==-1){
		vertices[V].quad2=F;
	}
	else if	(vertices[V].quad3==-1){
		vertices[V].quad3=F;
	}
	else if	(vertices[V].quad4==-1){
		vertices[V].quad4=F;
	}
}
void addEdge(int v,edge *e){
#ifdef PRINTALL	
	printf("in add edge \n");	
#endif	
	if (vertices[v].edge1==NULL){
		vertices[v].edge1=e;
#ifdef PRINTALL	
		printf("E1 added to v no. %d \n",v);
		printf("E1.x1 E1.y1 = %f %f  ; E.x2, E1.y2 =  %f %f \n",(double)vertices[vertices[v].edge1->v1].x,(double)vertices[vertices[v].edge1->v1].y,(double)vertices[vertices[v].edge1->v2].x,(double)vertices[vertices[v].edge1->v2].y);
#endif	
	}
	else if (vertices[v].edge2==NULL){
		vertices[v].edge2=e;
#ifdef PRINTALL	
		printf("E2 added to v no. %d \n",v);
#endif	
	}
	else if (vertices[v].edge3==NULL){
		vertices[v].edge3=e;
#ifdef PRINTALL	
		printf("E3 added to v no. %d \n",v);
#endif	
	}
	else if (vertices[v].edge4==NULL){
		vertices[v].edge4=e;
#ifdef PRINTALL	
		printf("E4 added to v no. %d \n",v);
#endif	
	}
	
	
	
}
addQuad(int index, int V1,int V2,int V3,int V4){
	faces[index].e1.v1=V1;
	faces[index].e1.v2=V2;
	
	addEdge(V1,&(faces[index].e1));
	addEdge(V2,&(faces[index].e1));
	
	faces[index].e1.mid.x=0.5*(vertices[V1].x+vertices[V2].x);
	faces[index].e1.mid.y=0.5*(vertices[V1].y+vertices[V2].y);
	faces[index].e1.mid.z=0.5*(vertices[V1].z+vertices[V2].z);
	
	faces[index].e2.v1=V2;
	faces[index].e2.v2=V3;

	addEdge(V3,&(faces[index].e2));
	addEdge(V2,&(faces[index].e2));


	faces[index].e2.mid.x=0.5*(vertices[V3].x+vertices[V2].x);
	faces[index].e2.mid.y=0.5*(vertices[V3].y+vertices[V2].y);
	faces[index].e2.mid.z=0.5*(vertices[V3].z+vertices[V2].z);


	faces[index].e3.v1=V3;
	faces[index].e3.v2=V4;

	addEdge(V3,&(faces[index].e3));
	addEdge(V4,&(faces[index].e3));


	faces[index].e3.mid.x=0.5*(vertices[V3].x+vertices[V4].x);
	faces[index].e3.mid.y=0.5*(vertices[V3].y+vertices[V4].y);
	faces[index].e3.mid.z=0.5*(vertices[V3].z+vertices[V4].z);
	

	faces[index].e4.v1=V4;
	faces[index].e4.v2=V1;

	addEdge(V1,&(faces[index].e4));
	addEdge(V4,&(faces[index].e4));

	faces[index].e4.mid.x=0.5*(vertices[V1].x+vertices[V4].x);
	faces[index].e4.mid.y=0.5*(vertices[V1].y+vertices[V4].y);
	faces[index].e4.mid.z=0.5*(vertices[V1].z+vertices[V4].z);
	
	faces[index].facePt.x=0.25*(vertices[V1].x+vertices[V2].x+vertices[V3].x+vertices[V4].x);
	faces[index].facePt.y=0.25*(vertices[V1].y+vertices[V2].y+vertices[V3].y+vertices[V4].y);
	faces[index].facePt.z=0.25*(vertices[V1].z+vertices[V2].z+vertices[V3].z+vertices[V4].z);

	addFace(fIndex,V1);
	addFace(fIndex,V2);
	addFace(fIndex,V3);
	addFace(fIndex,V4);
}

vertPtCompute(int i){
	float newX,newY,newZ;
	

if(vertices[i].edge4){				//only if vertex has 4 edges incident
	float qX=0;
	
	if (vertices[i].quad3)
		qX=(0.25*(faces[vertices[i].quad1].facePt.x + faces[vertices[i].quad2].facePt.x + faces[vertices[i].quad3].facePt.x + faces[vertices[i].quad4].facePt.x));
	
	float rX=0.5*vertices[i].x;

	if ((vertices[i].edge1->v1)==i)
		rX+=vertices[vertices[i].edge1->v2].x;
	else	
		rX+=vertices[vertices[i].edge1->v1].x;

	if (vertices[i].edge2->v1==i)
		rX+=vertices[vertices[i].edge2->v2].x;
	else	
		rX+=vertices[vertices[i].edge2->v1].x;
	
	if (vertices[i].edge3->v1==i)
		rX+=vertices[vertices[i].edge3->v2].x;
	else	
		rX+=vertices[vertices[i].edge3->v1].x;
	
	if (vertices[i].edge4->v1==i)
		rX+=vertices[vertices[i].edge4->v2].x;
	else	
		rX+=vertices[vertices[i].edge4->v1].x;
	
	
	
	float pX=0;
	
	pX=.25*vertices[i].x;
	
	vertices[i].newVert.x=rX/2+qX/4+pX/4;




	float qY=0;

	if (vertices[i].quad3)
		qY=(0.25*(faces[vertices[i].quad1].facePt.y + faces[vertices[i].quad2].facePt.y + faces[vertices[i].quad3].facePt.y + faces[vertices[i].quad4].facePt.y));
	
	float rY=0.5*vertices[i].y;

	if (vertices[i].edge1->v1==i)
		rY+=vertices[vertices[i].edge1->v2].y;
	else	
		rY+=vertices[vertices[i].edge1->v1].y;

	if (vertices[i].edge2->v1==i)
		rY+=vertices[vertices[i].edge2->v2].y;
	else	
		rY+=vertices[vertices[i].edge2->v1].y;
	
	if (vertices[i].edge3->v1==i)
		rY+=vertices[vertices[i].edge3->v2].y;
	else	
		rY+=vertices[vertices[i].edge3->v1].y;
	
	if (vertices[i].edge4->v1==i)
		rY+=vertices[vertices[i].edge4->v2].y;
	else	
		rY+=vertices[vertices[i].edge4->v1].y;
	
	
	
	float pY=0;
	
	pY=.25*vertices[i].y;
	
	vertices[i].newVert.y=rY/2+qY/4+pY/4;









	float qZ=0;

	if (vertices[i].quad3)
		qZ=(0.25*(faces[vertices[i].quad1].facePt.z + faces[vertices[i].quad2].facePt.z + faces[vertices[i].quad3].facePt.z + faces[vertices[i].quad4].facePt.z));
	
	float rZ=0.5*vertices[i].z;

	if (vertices[i].edge1->v1==i)
		rZ+=vertices[vertices[i].edge1->v2].z;
	else	
		rZ+=vertices[vertices[i].edge1->v1].z;

	if (vertices[i].edge2->v1==i)
		rZ+=vertices[vertices[i].edge2->v2].z;
	else	
		rZ+=vertices[vertices[i].edge2->v1].z;
	
	if (vertices[i].edge3->v1==i)
		rZ+=vertices[vertices[i].edge3->v2].z;
	else	
		rZ+=vertices[vertices[i].edge3->v1].z;
	
	if (vertices[i].edge4->v1==i)
		rZ+=vertices[vertices[i].edge4->v2].z;
	else	
		rZ+=vertices[vertices[i].edge4->v1].z;
	
	
	
	float pZ=0;
	
	pZ=.25*vertices[i].z;
	
	vertices[i].newVert.z=rZ/2+qZ/4+pZ/4;
	}

};

void printAll(){
}
quad CCsubdivide(/*quad *a*/){
	
	int i=0;
	
	quad *qq;
	qq=faces;
	printf("%d \n",(int)(sizeof(qq)/sizeof(qq[0])));
	printf("%d \n",(int)(sizeof(faces)/sizeof(faces[0])));
	printf("%d \n",fIndex);
	
	/**********NEW VERteX POINT ROUTINE************/
	for (i=0;i<vIndex;i++){
		vertPtCompute(i);
	}
}

void input( void )
{
	static const char filename[] = "input3.txt";
	FILE *file = fopen ( filename, "r" );

	if (file != NULL)
	{
		char line [ 128 ]; /* or other suitable maximum line size */
		while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
			{
				if (line[0]=='#' || line[0]==' ' || line[0]=='\n'   ){
					continue;
				}
				else if(line[0]=='v'){
					float x,y,z;
					sscanf (line,"v %f,%f,%f ",&x, &y, &z);
					//printf("Vertex found: x= %4.2f, y= %4.2f, z= %4.2f \n",x,y,z);
					addVertex(vIndex,x,y,z);
					vIndex++;
				}
				else if(line[0]=='f'){
					int v1,v2,v3,v4;
					sscanf (line,"f %d,%d,%d,%d ",&v1, &v2, &v3, &v4);
#ifdef PRINTALL
					printf("Face found: v1= %d, v2= %d, v3=%d, v4=%d  \n",v1,v2,v3,v4);
#endif	
					if (v1>vIndex || v2>vIndex || v3>vIndex || v4>vIndex )
#ifdef PRINTALL
						printf("Invalid Vertex Index \n");
#endif	
					else{
						addQuad(fIndex,v1,v2,v3,v4);
						fIndex++;
#ifdef PRINTALL
						printf("findex : %d \n",fIndex);
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
			printf("INPUT COMPLETE \n\tVertices scanned:\t%d \n\tFaces Scanned:\t%d \n",vIndex,fIndex);
#endif	
			fclose ( file );
	}
	else
	{
		perror ( filename ); /* why didn't the file open? */
	}
	//printAll();
	CCsubdivide();
}
