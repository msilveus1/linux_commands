#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
/**
 * fp: Original File pointer
 * nfp: New file pointer for tar file
 * argv: The argument array being passed
 * The purpose of this function is to make placing
 * File contents into tar file more modular in nature
 */
void fileContents(FILE *fp, FILE *nfp,char** argv){
	char *BUFFER = malloc(sizeof(char)*32);
	size_t bufsize = 32;
	while(getline(&BUFFER,&bufsize,fp) > 0){		
		//Placement of contents into tar file
		fputs(BUFFER,nfp);		
	}
	free(BUFFER);
}
/**
 * fp: Original File pointer
 * nfp: New file pointer for tar file
 * count: the number of argument we are parsing
 * argv: The argument array being passed
 * The purpose of this is to create a function to 
 * get and write the file size to memory
 */
void fileSize(FILE *fp, FILE *nfp, int count,char** argv){
	//Stat is the struct that allows us to gather 
	//Details about the file size
	struct stat buf;
	stat(argv[count],&buf);
	long *size =malloc(sizeof(long));
	*size = buf.st_size;
	stat(argv[count],&buf);
	//Used fwrite to write non-asci value
	fwrite(size,sizeof(long),1,nfp);
	free(size);
}
/**
 * fp: Original File pointer
 * nfp: New file pointer for tar file
 * count: the number of argument we are parsing
 * argv: The argument array being passed
 * The purpose of this function is to get and write the 
 * file name to the new tar file and to follow preset 
 * 100 byte asci standard
 */
void fileName(FILE *fp, FILE *nfp, int count,char** argv){	
	int currentsize = strlen(argv[count]);
	//num_of_writes helps determine what we need
	//to do to conform to file format standards	
	int num_of_writes = 100 - currentsize;
	if(num_of_writes > 0){
		fputs(argv[count],nfp);
		for(int i=0;i<num_of_writes;i++){
			fwrite("\0",sizeof(char),1,nfp);
		}
	}
	else if(num_of_writes < 0){
		char *buffer = malloc(sizeof(char)*100);
		//A copy of the first 100 charecters of the title
		strncpy(buffer,argv[count],100);
		fputs(buffer,nfp);
		free(buffer);
	}
}
/**
 * Author: Matthew Silveus
 * Email: msilveus@wisc.edu
 * cs login: silveus-jr
 * This file is a simplified version of tar
 */
int main(int argc, char *argv[]) {
	//Validation check for argument count
	if(argc<3){
		printf("wis-tar: tar-file file […]\n");
		exit(1);
	}else{
		//Count for parsing arguments passed in
		int count = 2;
		//New file pointer for tar file
		FILE *nfp = fopen(argv[1],"w");
		while(count != argc){
			FILE *fp = fopen(argv[count],"r");
			if(fp == NULL){
				printf("wis-tar: cannot open file\n");
				exit(1);
			}
			fileName(fp,nfp,count,argv);
			fileSize(fp,nfp,count,argv);
			fileContents(fp,nfp,argv);
			count++;
			fclose(fp);
		}		
		fclose(nfp);
	}	
	return 0;
}