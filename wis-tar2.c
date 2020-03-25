#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
int main(int argc, char *argv[]) {
	if(argc<2){
		printf("wis-tar: tar-file file […]\n");
		exit(0);
	}
	FILE *fp = fopen(argv[1],"r");
	if(fp == NULL){
		printf("cannot open file \n");
		exit(0);
	}
	size_t bufsize = 32;
	char *BUFFER = malloc(sizeof(char)*32);
	// fclose(fp);
	getline(&BUFFER,&bufsize,fp);
	printf("%s\n",BUFFER );
}