#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define BASIS 1
#define BUFFSIZE 2

void newLineTerminatedToNullTerminated(char* line){
	while (*line!='\0'){
		if(*line=='\n'){
			*line='\0';	
			return;
		}
		line++;
	}
	
}

char ReaderReadLine(FILE* file, char** linePtr){
	char buf[BUFFSIZE];
	char* line=NULL;
	char* memPointerToFreeIfLineReallocFails=NULL;
	size_t basicsize=BUFFSIZE;
	while (fgets(buf, BUFFSIZE, file)!=NULL){
		memPointerToFreeIfLineReallocFails=line;
		line=(char*) realloc(line,basicsize); //buffsize
		if (line==NULL){
			perror("Reader: line realloc failed\n");
			free(memPointerToFreeIfLineReallocFails);
			return -1;
		}
		if(basicsize==BUFFSIZE)
			line[0]='\0';
		basicsize+=BUFFSIZE;
		size_t ssize = strlen(buf);//figure out the actual length we read
		if (ssize==BUFFSIZE-1){
			strcat(line, buf);
			//if we read whole bytes we requested
			if(buf[ssize-1]=='\n'){
				//we got lion^W line, everybody get in a car
				newLineTerminatedToNullTerminated(line);
				*linePtr=line;
				return 0;
			}
			continue; //if we did not met '\n' keep reading that same file
		}
		// if we somehow read the other amount of chars
		strcat(line,buf);
		newLineTerminatedToNullTerminated(line);
		*linePtr=line;
		return 0;
	} 
	if(errno!=0){
		perror("Reader: Error while Reading file");
		if(line!=NULL)
			free(line);
		return -1;
	}
	if(line==NULL)
		return 0;
	newLineTerminatedToNullTerminated(line);
	*linePtr=line;
	return 0;
}

