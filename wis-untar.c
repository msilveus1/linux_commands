#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
/**
 * fp: original file pointer
 * nfp: new file pointer
 * BUFFER: where the filename gets loaded
 * The purpose of this function is to get the file name and
 * open it.
 */
FILE* getfileName(FILE *fp, FILE *nfp){
	char *BUFFER = malloc(sizeof(char)*100);
	fread(BUFFER,1,100,fp);
	nfp = fopen(BUFFER,"w");
	free(BUFFER);
	return nfp;
}
/**
* fp: file pointer from which to read
* size: pointer to a long in which we put size
* This function is meant to get file size.
*/
void getSize(FILE *fp,long *size){
	fread(size,sizeof(long),1,fp);
}
/**
 * Author: Matthew Silveus
 * Email: msilveus@wisc.edu
 * cs login: silveus-jr
 * This file is a simplified version of untar
 */
int main(int argc, char *argv[]) {
	//Arg count validation
	if(argc<2){
		printf("wis-untar: tar-file\n");
		exit(1);
	}
	FILE *fp = fopen(argv[1],"r");
	if(fp == NULL){
		printf("wis-untar: cannot open file\n");
		exit(1);
	}	
	//Condition to set for when to be done reading.
	int quit_condition = 0;
	while(quit_condition == 0){	
		FILE *nfp;
		nfp = getfileName(fp,nfp);
		if(nfp == NULL){
			printf("wis-untar: cannot open file\n");
			exit(1);
		}
		long *size = malloc(sizeof(long));
		getSize(fp,size);
		//We use heap because we get over reading of mem otherwise
		char * buffer_contents = malloc(sizeof(char)*(*size));
		fread(buffer_contents,1,*size,fp);
		fputs(buffer_contents,nfp);
		free(buffer_contents);
		//The position tracker for the file pointer
		fpos_t pos;
		fgetpos(fp,&pos);
		//Buffer for reading to the end
		char  buffer_end[3];
		fgets(buffer_end,3,fp);
		//Condition check to see if end-of-file flag is set
		if(feof(fp)==1){
			quit_condition = 1;
		}else{
			//Reset for position
			fsetpos(fp,&pos);
		}
	}
}