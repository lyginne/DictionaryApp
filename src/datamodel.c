#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "../include/reader.h"
#include "../include/datamodel.h"
#include "../include/dictionary.h"
#include "../include/verificator.h"

#define BUFFSIZE 2

static Dictionary* dictionary;

char parseAndSave(char* line){
	char* strPointer=NULL;
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
			if(validateString(key, 128)==STRING_UNVALID){
				perror("Invalid file structure");
				return -1;
			}
			description=strPointer+1;
			if(validateString(description, 0)==STRING_UNVALID){
				perror("Invalid file structure");
				return -1;
			}
			break;
		}
		strPointer++;
	}
	if (key==NULL||description==NULL){
		perror("Invalid file structure");
		return -1;
	}
	DictionaryAddResult result = DictionaryAdd(dictionary, key, description);	
	if(result==DICTIONARYADDRESULT_FAILED){
		return -1;
	}
	else if(result==DICTIONARYADDRESULT_ALREADYEXIST){
		perror("Already existing dictionary node, skiping");
		return 0;
	}
	else if(result==DICTIONARYADDRESULT_SUCCED){
		return 0;
	}
	return -1;
}
char FillFromFile(char* path){
	char* line=NULL;
	FILE* file=fopen(path,"r");
	if(file==NULL){
		//if file does not exist don't try to read, write only
		errno=0;
		return 0;
	}
	while(ReaderReadLine(file,&line)==0){
		if (line==NULL)
			break;
		if(parseAndSave(line)!=0){
			free(line);
			fclose(file);
			return -1;
		}
		free(line);
		line=NULL;
	}
	fclose(file);
	return 0;
	
}

char Initialize(void){
	dictionary = DictionaryInitialize();
	if(dictionary==NULL)
		return -1;
	return 0;
}

DataModelAddResult Add( char* key,  char* description){
	DictionaryAddResult result = DictionaryAdd(dictionary, key, description);
	if(result==DICTIONARYADDRESULT_SUCCED)
		return DATAMODELADDRESULT_SUCCEED;
	if(result==DICTIONARYADDRESULT_FAILED)
		return DATAMODELADDRESULT_FAILED;
	if(result==DICTIONARYADDRESULT_ALREADYEXIST)
		return DATAMODELADDRESULT_ALREADYEXIST;
	return DATAMODELREMOVERESULT_FAILED;
}

DataModelRemoveResult Remove( char* key){
	DictionaryRemoveResult result = DictionaryRemove(dictionary, key);
	if(result==DICTIONARYREMOVERESULT_SUCCED)
		return DATAMODELREMOVERESULT_SUCCEED;
	if(result==DICTIONARYREMOVERESULT_FAILED)
		return DATAMODELREMOVERESULT_FAILED;
	if(result==DICTIONARYREMOVERESULT_NOTFOUND)
		return DATAMODELREMOVERESULT_NOTFOUND;
	return DATAMODELREMOVERESULT_FAILED;
}

DataModelSearchResult Search( char* key, char** description){
	*description=NULL;
	DataModelSearchResult result = DictionaryDescriptionSearch(dictionary, key, description);
	if(result==DICTIONARYSEARCHRESULT_SUCCED)
		return DATAMODELSEARCHRESULT_SUCCEED;
	if(result==DICTIONARYSEARCHRESULT_FAILED)
		return DATAMODELSEARCHRESULT_FAILED;
	if(result==DICTIONARYSEARCHRESULT_NOTFOUND)
		return DATAMODELSEARCHRESULT_NOTFOUND;
	return DATAMODELSEARCHRESULT_FAILED;
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
