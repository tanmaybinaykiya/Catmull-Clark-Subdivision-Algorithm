#include "structs.h"
void export(){
	#ifndef SubD
		#ifdef PRINT_ALL
			printf("Not Subdivided");
		#endif
	#else 
		FILE *fp;
		if((fp=fopen("out.obj","w+"))==NULL){
			printf("Error in output file");
			return 1;
		}
		
		
		
		
		
	#endif
}
