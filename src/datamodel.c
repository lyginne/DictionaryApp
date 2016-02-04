#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/datamodel.h"
#include "../include/dictionary.h"

#define buffsize 128;

static Dictionary* dictionary;
int Initialize(char* dataFile){
	dictionary = DictionaryInitialize();
	/*FILE* file=fopen(dataFile,"r");
	char line[buffsize];	
	fgets(line, buffsize, file);
	ssize_t ssize = strlen(line);
	if (ssize=buffsize-1){
		if(line[ssize-1]=='\n'){
			//we got line, get in a car	
		}
		//domore

	}*/
	//FileOpen(dataFile);
	
	return 0;
}

int Add(char* key, char* description){
	DictionaryAdd(dictionary,key, description);
	return 0;
}

int Remove(char* key){
	DictionaryRemove(dictionary, key);
	return 0;
}

char *Search(char* key){
	return DictionaryDescriptionSearch(dictionary, key);
	
}
char DataWriteToFile(char* dataFile){
	FILE* file=fopen(dataFile,"w+");
	DictionaryForeachInit(dictionary);
	DictionaryNode* node=DictionaryNext(dictionary);
	while(node!=NULL){
		size_t strlen1 = strlen(node->key);
		size_t strlen2 = strlen(node->description);
		char* line=(char*)malloc(strlen1+strlen2+3);
		line[0]='\0';
		strcat(line,node->key);
		strcat(line, "\t");
		strcat(line,node->description);
		strcat(line,"\n");
		fputs(line, file);
		free(line);
		line=NULL;
		node=DictionaryNext(dictionary);
	}
	fclose(file);
	return 0;
	
}
