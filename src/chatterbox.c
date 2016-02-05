#include <stddef.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/reader.h"
#include "../include/chatterbox.h"
#include "../include/customerrno.h"

char (*AddCallback)(char* key, char* description);
char (*RemoveCallback)(char* key);
char* (*SearchCallback)(char* key);

/*long int getline(char** line, FILE* fd){
	defaultSize=128;
	*line=(char *)malloc(defaultSize);

	fgets(line, size, stdin);
}*/



char ListenerAddCallbacks(char (*addRequestCallback)(char* key, char* description), char (*removeRequestCallback)(char* key), char* (*searchRequestCallback)(char* key)){
	AddCallback=addRequestCallback;
	RemoveCallback=removeRequestCallback;
	SearchCallback=searchRequestCallback;	
	return 0;
}
char AddRecieved(){
	char* key=NULL;
	char* description=NULL;
	char ssize;
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
		perror("Unexpected EOF");
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
	return 0;
}

char removeRecieved(){
	char* key=NULL;
	char ssize;
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
	return 0;	
}

char searchRecieved(){
	char* key=NULL;
	char ssize;
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
	if(searchResult==NULL&&errno==0&&customerrno==0){
		//If no errors ocured and and still we got null - means not found
		printf("%s\n", "Not Found");
	}
	else if(searchResult==NULL){
		return -1;
	}
	else{
		printf("%s\n",searchResult);
	}
	fflush(stdout);
	free(key);
	key=NULL;
	return 0;
}

char helpRecieved(){
	printf("%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n", 
		"add - add a word with descpiption", 
		"search - search a word", 
		"remove - remove a word", 
		"help - help",
		"quit - quit properly");
	return 0;
}

char listen(){
	char* line = NULL;
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
		if (strcmp(line,"add")==0){
			if(AddRecieved()!=0)
				return -1;
		}
		else if (strcmp(line,"search")==0){
			if(searchRecieved()!=0)
				return -1;
		}
		else if (strcmp(line,"remove")==0){
			if(removeRecieved()!=0)
				return -1;
		}
		else if (strcmp(line, "help")==0){
			if(helpRecieved()!=0)
				return -1;
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
