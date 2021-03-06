#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/chatterbox.h"
#include "../include/datamodel.h"
#include "../include/customerrno.h"


#define STDOUT 1
#define STDERR 2
#define STDIN 0

int customerrno=0;

char addCallback(char* key, char* description){
	return Add(key,description);		
}

char removeCallback(char* key){
	return Remove(key);
}

char* searchCallback(char* key){
	return Search(key);
}
	
int main(int argc, char* argv[]){
	char* path=NULL;

	//more than one argument should be a user mistake

	if(argc>2){
		printf("%s","Too much arguments");
		exit(1);	
	}

	//exactly one argument, should be file to read and fill the dictionary
	else if(argc==2){
		path=argv[1];
	}
	if(Initialize(path)!=0){
		exit(1);
	}
	ListenerAddCallbacks(&addCallback, &removeCallback, &searchCallback);
	if(listen()==0){
		if(DataWriteToFile(path)==0){
			exit(0);
		}
	}
	exit(1);

}
