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
	Add(key,description);		
	return 0;
}

char removeCallback(char* key){
	Remove(key);
	return 0;
}

char* searchCallback(char* key){
	return Search(key);
}
	
int main(int argc, char* argv[]){

	//more than one argument should be a user mistake

	if(argc>2){
		printf("%s","Too much arguments");
		exit(1);	
	}

	//exactly one argument, should be file to read and fill the dictionary
	else if(argc==2){
		//type read from file code here
	}
	//that actualy the main cycle
	Initialize(NULL);
	ListenerAddCallbacks(&addCallback, &removeCallback, &searchCallback);
	if(listen()==0){
		if(argc==2)
			DataWriteToFile(argv[1]);
	}

}
