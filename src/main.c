#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/chatterbox.h"
#include "../include/datamodel.h"


#define STDOUT 1
#define STDERR 2
#define STDIN 0

char addCallback(char* key, char* description){
	printf("i wus here");
	fflush(stdout);
	Add(key,description);		
}

char removeCallback(char* key){
	Remove(key);
}

char* searchCallback(char* key){
	return Search(key);
}
	
int main(int argc, char* argv[]){

	char readbuffer[128];
	//more than one argument should be a user mistake

	if(argc>1){
		printf("%s","Too much arguments");
		exit(1);	
	}

	//exactly one argument, should be file to read and fill the dictionary
	else if(argc==1){
		//type read from file code here
	}
	//that actualy the main cycle
	Initialize(NULL);
	ListenerAddCallbacks(&addCallback, &removeCallback, &searchCallback);
	listen();
}
