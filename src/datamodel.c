#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "../include/datamodel.h"
#include "../include/dictionary.h"
#include "../include/verificator.h"
#include "../include/customerrno.h"

#define BUFFSIZE 2

static Dictionary* dictionary;

char parseAndSave(char* line){
	char* strPointer;
	char* descriptionStartPointer;
	char* key=NULL;
	char* description=NULL;
	strPointer=line;
	while(*strPointer!='\0'){
		if(*strPointer=='\t'){
			if(key!=NULL){
				//tabulation is ok only once, so key should not be setted
				perror("Invalid file structure");
				return -1;
			}
			*strPointer='\0';	
			key=line;
			if(validateString(key)==STRING_UNVALID){
				perror("Invalid file structure");
				return -1;
			}
			descriptionStartPointer=strPointer+1;
		}
		if(*strPointer=='\n'){
			*strPointer='\0';
			description=descriptionStartPointer;
			if(validateString(description)==STRING_UNVALID){
				perror("Invalid file structure");
				return -1;
			}
		}
		strPointer++;
	}
	if (key==NULL||description==NULL){
		perror("Invalid file structure");
		return -1;
	}
	
	if(DictionaryAdd(dictionary,key, description)!=0)
		return -1;
	return 0;
}
char Initialize(char* path){
	char buf[BUFFSIZE];
	char* line=NULL;
	size_t basicsize=BUFFSIZE;
	dictionary = DictionaryInitialize();
	if(path==NULL){
		//if d
		return 0;
	}
	FILE* file=fopen(path,"r");
	if(file==NULL){
		//if file does not exist don't try to read, write only
		errno=0;
		return 0;
	}
	while (!feof(file)){
		if(fgets(buf, BUFFSIZE, file)==NULL){
			//Noth more to read, but we can have line saved before, can we?
			if(line==NULL)
				break;
			parseAndSave(line);
			free(line);
			line=NULL;
			break;
		}
		line=(char*) realloc(line,basicsize); //buffsize
		if (line==NULL){
			perror("Dictionary Initialize realloc line failed");
			free(line);
			fclose(file);
			return 0;
		}
		if(basicsize==BUFFSIZE){
			line[0]='\0';
		}
		basicsize+=BUFFSIZE;
		size_t ssize = strlen(buf);//figure out the actual length we read
		if (ssize==BUFFSIZE-1){
			strcat(line, buf);
			//if we read whole bytes we requested
			if(buf[ssize-1]=='\n'){
				//we got lion^W line, everybody get in a car
				if(parseAndSave(line)!=0){
					free(line);
					fclose(file);
					return -1;
				}
				free(line);
				basicsize=BUFFSIZE;
				line=NULL;
			}
			continue; //if we did not met EOF or '\n' keep reading that same file
		}
		strcat(line,buf);
		if(parseAndSave(line)!=0){
			free(line);
			fclose(file);
			return -1;
		}
		parseAndSave(line);
		free(line);
		line=NULL;
		basicsize=BUFFSIZE;
		// if we somehow read the other amount of chars
		 
	} 
	if(errno!=0){
		perror("Error while Reading file");
		fclose(file);
		return -1;
	}
	fclose(file);
	return 0;
}

char Add(char* key, char* description){
	return DictionaryAdd(dictionary,key, description);
}

char Remove(char* key){
	return DictionaryRemove(dictionary, key);
}

char *Search(char* key){
	return DictionaryDescriptionSearch(dictionary, key);
	
}
char DataWriteToFile(char* path){
	if(path==NULL){
		return 0;
	}
	FILE* file=fopen(path,"w+");
	if(file==NULL){
		perror("Can't open file.");
		return -1;
	}
	DictionaryForeachInit(dictionary);
	DictionaryNode* node=DictionaryNext(dictionary);
	while(node!=NULL){
		size_t strlen1 = strlen(node->key);
		size_t strlen2 = strlen(node->description);
		char* line=(char*)malloc(strlen1+strlen2+3); //strlen1+'\t'+strlen2+'\n'+'\0'
		if(line==NULL){
			perror("can't allocate mem for file");
			fclose(file);
			return -1;
		}
		line[0]='\0';
		strcat(line,node->key);
		strcat(line, "\t");
		strcat(line,node->description);
		strcat(line,"\n");
		if(fputs(line, file)==EOF){
			perror("Can't write wo a file");
			free(line);
			fclose(file);
			return -1;
		}
		free(line);
		line=NULL;
		node=DictionaryNext(dictionary);
	}
	fclose(file);
	return 0;
}
