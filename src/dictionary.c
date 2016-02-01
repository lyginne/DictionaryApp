#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dictionary.h"
#include "../include/linkedlist.h"


char comparer(void* data, void* key){
	if(data=NULL){
		return 0x80; //should define comparer error
	}
	return strcmp(((DictionaryNode*)data)->key,(char*)key);
}

DictionaryNode* dictionaryNodeSearch(Dictionary* dictionary,char* key){
	return (DictionaryNode*)GetElement(dictionary->linkedList,(void*)key,&comparer);
}
Dictionary* DictionaryInitialize(){
	Dictionary* dictionary=(Dictionary*)malloc(sizeof(dictionary));
	dictionary->linkedList=LinkedListInitialize();
	return dictionary;
}

int DictionaryAdd(Dictionary* dictionary,char* key, char* description){
	printf("I wus here");
	fflush(stdout);
	DictionaryNode* addingNode = (DictionaryNode*)malloc(sizeof(DictionaryNode));
	addingNode->key = key;
	addingNode->description = description;
	printf("dohodit");
	fflush(stdout);
	if(dictionary->linkedList==NULL){
		printf("NULL");
		fflush(stdout);
	}
	LinkedListAdd(dictionary->linkedList,addingNode);
}

int DictionaryRemove(Dictionary* dictionary, char* key){
	LinkedListRemove(dictionary->linkedList,key,&comparer);
}

char* DictionaryDescriptionSearch(Dictionary* dictionary, char* key){
	DictionaryNode* node = dictionaryNodeSearch(dictionary,(void*)key);	
}

