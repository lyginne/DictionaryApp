#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define STDOUT 1
#define STDERR 2
#define STDIN 0

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
	while(1){
		printf("%s",">");
		fflush(stdout);
		int charsread = read(0,readbuffer,128);
		readbuffer[charsread]='\0';
		if (strcmp(readbuffer,"add\n")==0){
			printf("%s","Type a word:\r\n");
			fflush(stdout);
			read(STDIN,readbuffer,128);
			//code for add
		}
		else if (strcmp(readbuffer,"search\n")==0){
			printf("%s","Type a word:\r\n");
			read(STDIN,readbuffer,128);
			//code for search
		}
		else if (strcmp(readbuffer,"remove\n")==0){
			printf("%s", "Type a word:\r\n");
			read(STDIN,readbuffer,128);
			//code for remove
		}
		else if (strcmp(readbuffer, "help\n")==0){
			printf("%s\r\n%s\r\n%s\r\n%s\r\n", "add - add a word", "search - search a word", "remove - remove a word", "help - help");
		}
		else {
			printf("%s\r\n","Invalid command, type help for help");
			//code for invalid command
		}
	}
}
