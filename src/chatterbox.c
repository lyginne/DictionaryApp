#include <stddef.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/reader.h"
#include "../include/chatterbox.h"
#include "../include/verificator.h"

AddRequestCallback AddCallback;
RemoveRequestCallback RemoveCallback;
SearchRequestCallback SearchCallback;

typedef enum{
	RECIEVERESULT_EOF,
	RECIEVERESULT_FAILED,
	RECIEVERESULT_SUCCED
} RecieveResult;

void ListenerAddCallbacks(AddRequestCallback addRequestCallback, RemoveRequestCallback removeRequestCallback, SearchRequestCallback searchRequestCallback){
	AddCallback=addRequestCallback;
	RemoveCallback=removeRequestCallback;
	SearchCallback=searchRequestCallback;	
}

RecieveResult AddRecieved(){
	char* key=NULL;
	char* description=NULL;
	char result;
	printf("%s\n","Type a word: ");
	fflush(stdout);
	result=ReaderReadLine(stdin,&key);
	if(result<0)
		return RECIEVERESULT_FAILED;
	if(key==NULL)
		return RECIEVERESULT_EOF;
	if(validateString(key,128)==STRING_UNVALID){
		perror("Key is invalid");		
		free(key);
		return RECIEVERESULT_SUCCED;
	}
	printf("%s\n", "Type a description: ");
	fflush(stdout);
	result=ReaderReadLine(stdin,&description);
	if(result<0){
		free(key);
		return RECIEVERESULT_FAILED;
	}
	if(description==NULL){
		free(key);
		return RECIEVERESULT_EOF;
	}
	if(validateString(description,0)==STRING_UNVALID){
		perror("description is invalid");		
		fflush(stdout);
		free(key);
		free(description);
		return RECIEVERESULT_SUCCED;
			
	}
	AddRequestCallbackResult addCallbackResult = AddCallback(key, description);
	free(key);
	free(description);
	if(addCallbackResult==ADDREQUESTCALLBACK_FAILED){
		return RECIEVERESULT_FAILED;
	}
	else if(addCallbackResult == ADDREQUESTCALLBACK_ALREADYEXIST){
		printf("%s\n", "Such word already exist");
		fflush(stdout);
		return RECIEVERESULT_SUCCED;
	}
	else if(addCallbackResult == ADDREQUESTCALLBACK_SUCCEED){
		return RECIEVERESULT_SUCCED;
	}
	return RECIEVERESULT_FAILED;
}

char removeRecieved(){
	char* key=NULL;
	char result;
	printf("%s\n","Type a word: ");
	fflush(stdout);
	result=ReaderReadLine(stdin,&key);
	if(result<0)
		return RECIEVERESULT_FAILED;
	if(key==NULL)
		return RECIEVERESULT_EOF;
	if(validateString(key,128)==STRING_UNVALID){
		perror("Key is invalid");		
		free(key);
		return RECIEVERESULT_SUCCED;
	}
	RemoveRequestCallbackResult removeCallbackResult = RemoveCallback(key);
	free(key);
	if(removeCallbackResult == REMOVEREQUESTCALLBACK_SUCCEED){
		return RECIEVERESULT_SUCCED;
	}
	else if (removeCallbackResult == REMOVEREQUESTCALLBACK_FAILED){
		return RECIEVERESULT_FAILED;
	}
	else if (removeCallbackResult == REMOVEREQUESTCALLBACK_NOTFOUND){
		printf("%s\n", "No such word exist");
		fflush(stdout);
		return RECIEVERESULT_SUCCED;
	}
	return RECIEVERESULT_FAILED;	
}

char searchRecieved(){
	char* key=NULL;
	char result;
	printf("%s\n","Type a word: ");
	fflush(stdout);
	result=ReaderReadLine(stdin,&key);
	if(result<0)
		return RECIEVERESULT_FAILED;
	if(key==NULL)
		return RECIEVERESULT_EOF;
	if(validateString(key,128)==STRING_UNVALID){
		perror("Key is invalid");		
		free(key);
		return RECIEVERESULT_SUCCED;
	}
	char* description=NULL;
	SearchRequestCallbackResult searchResult=SearchCallback(key,&description);
	free(key);
	if(searchResult==SEARCHREQUESTCALLBACK_SUCCEED){
		printf("%s\n",description);
		return RECIEVERESULT_SUCCED;
	}
	else if(searchResult==SEARCHREQUESTCALLBACK_FAILED){
		return RECIEVERESULT_FAILED;
	}
	else if(searchResult == SEARCHREQUESTCALLBACK_NOTFOUND){
		printf("%s\n", "Not Found");
		fflush(stdout);
		return RECIEVERESULT_SUCCED;
	}
	return RECIEVERESULT_FAILED;
}

char helpRecieved(){
	printf("%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n", 
		"add - add a word with descpiption", 
		"search - search a word", 
		"remove - remove a word", 
		"help - help",
		"quit - quit properly");
	fflush(stdout);
	return RECIEVERESULT_SUCCED;
}

char listen(){
	char* line = NULL;
	char result;
	RecieveResult recieveResult;
	while(1){
		recieveResult=RECIEVERESULT_SUCCED;
		printf("%s",">");
		fflush(stdout);
		result=ReaderReadLine(stdin,&line);
		if(result<0){
			return -1;
		}
		if (line==NULL){
			return 0;
		}
		else if (strcmp(line,"add")==0){
			recieveResult = AddRecieved();
		}
		else if (strcmp(line,"search")==0){
			recieveResult = searchRecieved();
		}
		else if (strcmp(line,"remove")==0){
			recieveResult = removeRecieved();
		}
		else if (strcmp(line, "help")==0){
			recieveResult = helpRecieved();
		}
		else if(strcmp(line, "quit")==0){
			free(line);
			return 0;
		}
		else{ 
			printf("%s\r\n","Invalid command, type help for help");
		}

		fflush(stdout);
		free(line);
		line=NULL;

		if(recieveResult==RECIEVERESULT_SUCCED)
			continue;
		else if(recieveResult==RECIEVERESULT_EOF)
			return 0;
		else if(recieveResult==RECIEVERESULT_FAILED)
			return -1;
	}
}
