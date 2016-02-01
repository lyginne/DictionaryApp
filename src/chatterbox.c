#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/chatterbox.h"

char (*AddCallback)(char* key, char* description);
char (*RemoveCallback)(char* key);
char* (*SearchCallback)(char* key);

int ListenerAddCallbacks(char (*addRequestCallback)(char* key, char* description), char (*removeRequestCallback)(char* key), char* (*searchRequestCallback)(char* key)){
	AddCallback=addRequestCallback;
	RemoveCallback=removeRequestCallback;
	SearchCallback=searchRequestCallback;	
}
int listen(){
	char** argv;
	char* line = NULL;
	char* key;
	char* description;
	size_t size;
	ssize_t ssize;
	while(1){
		printf("%s",">");
		fflush(stdout);
		ssize=getline(&line,&size,stdin);
		line[ssize-1]='\0';
		printf("%s",line);
		fflush(stdout);
		//argv=GetArgumentsFromString(line);
		if (strcmp(line,"add")==0){
			printf("%s","Type a word: ");
			fflush(stdout);
			ssize=getline(&key,&size,stdin);
			key[ssize-1]='\0';
			printf("%s", "Type a description: ");
			ssize=getline(&description,&size,stdin);
			description[ssize-1]='\0';
			printf("%s", "Type a description: ");
			AddCallback(key,description);
			free(key);
			key=NULL;
			free(description);
			key=NULL;
			continue;
		}
		else if (strcmp(line,"search")==0){
			printf("%s","Type a word: ");
			fflush(stdout);
			getline(&key,&size,stdin);
			key[ssize-1]='\0';
			RemoveCallback(key);
			free(key);
			key=NULL;
			free(line);
			line=NULL;
			continue;
		}
		else if (strcmp(line,"remove")==0){
			printf("%s","Type a word: ");
			fflush(stdout);
			getline(&key,&size,stdin);
			key[ssize-1]='\0';
			printf("%s",SearchCallback(key));
			free(key);
			key=NULL;
			free(line);
			continue;
		}
		else if (strcmp(line, "help")==0){
			printf("%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n", 
				"add WORD DESCRIPTION - add a word with descpiption", 
				"search WORD- search a word", 
				"remove WORD- remove a word", 
				"help - help",
				"quit - quit properly");
			continue;
		}
		else if(strcmp(line, "quit")==0){
			free(line);
			return 0;
		}
		printf("%s\r\n","Invalid command, type help for help");
	}
}
