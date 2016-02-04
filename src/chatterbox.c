#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/reader.h"
#include "../include/chatterbox.h"

char (*AddCallback)(char* key, char* description);
char (*RemoveCallback)(char* key);
char* (*SearchCallback)(char* key);

/*long int getline(char** line, FILE* fd){
	defaultSize=128;
	*line=(char *)malloc(defaultSize);

	fgets(line, size, stdin);
}*/



int ListenerAddCallbacks(char (*addRequestCallback)(char* key, char* description), char (*removeRequestCallback)(char* key), char* (*searchRequestCallback)(char* key)){
	AddCallback=addRequestCallback;
	RemoveCallback=removeRequestCallback;
	SearchCallback=searchRequestCallback;	
	return 0;
}
int listen(){
	char* line = NULL;
	char* key=NULL;
	char* description=NULL;
	char ssize;
	while(1){
		printf("%s",">");
		fflush(stdout);
		ssize=ReaderGetWholeDamnString(0,&line);
		if(ssize==0){
			printf("%s\n", "Unexpected EOF");
			fflush(stdout);
			return -1;
		}
		printf(line);
		fflush(stdout);
		if (strcmp(line,"add")==0){
			printf("%s","Type a word: ");
			fflush(stdout);
			ssize=ReaderGetWholeDamnString(0,&key);
			if(ssize==0){
				printf("%s\n", "Unexpected EOF");
				fflush(stdout);
				return -1;
			}
			printf("%s", "Type a description: ");
			fflush(stdout);
			ssize=ReaderGetWholeDamnString(0,&description);
			if(ssize==0){
				printf("%s\n", "Unexpected EOF");
				fflush(stdout);
				free(key);
				key=NULL;
				free(description);
				description=NULL;
				return -1;
			}
			AddCallback(key,description);
			free(key);
			key=NULL;
			free(description);
			description=NULL;
		}
		else if (strcmp(line,"search")==0){
			printf("%s","Type a word: ");
			fflush(stdout);
			ssize=ReaderGetWholeDamnString(0,&key);
			if(ssize==0){
				printf("%s\n", "Unexpected EOF");
				fflush(stdout);
				free(key);
				key=NULL;
				return -1;
			}
			char* searchResult=SearchCallback(key);
			if(searchResult==NULL){
				printf("%s\n", "Not Found");
			}
			else{
				printf("%s\n",SearchCallback(key));
			}
			fflush(stdout);
			free(key);
			key=NULL;
		}
		else if (strcmp(line,"remove")==0){
			printf("%s","Type a word: ");
			fflush(stdout);
			ssize=ReaderGetWholeDamnString(0,&key);
			if(ssize==0){
				printf("%s\n", "Unexpected EOF");
				fflush(stdout);
				free(key);
				key=NULL;
				return -1;
			}
			RemoveCallback(key);
			free(key);
			key=NULL;
		}
		else if (strcmp(line, "help")==0){
			printf("%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n", 
				"add - add a word with descpiption", 
				"search- search a word", 
				"remove- remove a word", 
				"help - help",
				"quit - quit properly");
		}
		else if(strcmp(line, "quit")==0){
			free(line);
			line=NULL;
			return 0;
		}
		else{ 
			printf("%s\r\n","Invalid command, type help for help");
		}
		free(line);
		line=NULL;
	}
}
