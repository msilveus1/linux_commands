#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * Author: Matthew Silveus
 * Email: msilveus@wisc.edu
 * cs login: silveus-jr
 * This file is a simplified version of grep
 */
int main(int argc, char *argv[]) {
	if(argc < 2){
		printf("wis-grep: searchterm [file …]\n");
		exit(1);
	}else if(argc==2){
		size_t bufsize = 32;
		//The heap is used here because a normal char array was
		//Over reading memory.
		char *BUFFER = malloc(sizeof(char)*32);
		while(getline(&BUFFER,&bufsize,stdin) >0){			
			if(strstr(BUFFER,argv[1]) != NULL){
				printf("%s",BUFFER);
			}			
		}	
 		free(BUFFER);
  		return 0;  
	}else{
		//a count for parsing args
		int count = 2;
		while(count != argc){
			FILE *fp = fopen(argv[count],"r");
			size_t bufsize = 32;
			//The heap is used here because a normal char array was
			//Over reading memory.
			char *BUFFER = malloc(sizeof(char)*32);
			if (fp == NULL){
				printf("wis-grep: cannot open file\n");
				exit(1);
			}
			while(getline(&BUFFER,&bufsize,fp) > 0){
				//Check for the line containing search term
				if(strstr(BUFFER,argv[1]) != NULL){
					printf("%s",BUFFER);
				}
			}	
			free(BUFFER);
  			count++;
 			fclose(fp);
		}
	}
	return 0;
}