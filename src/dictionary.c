#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dictionary.h"
#include "../include/linkedlist.h"


char destructor(void* data){
	if (data==NULL){
		return -1;
	}
	free(((DictionaryNode*)data)->key);
	free(((DictionaryNode*)data)->description);
	return 0;
}
char comparer(void* data, void* key){
	if(data==NULL){
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
	DictionaryNode* addingNode = (DictionaryNode*)malloc(sizeof(DictionaryNode));
	char* cpKey=(char*)malloc(strlen(key)+1);
	addingNode->key = strcpy(cpKey,key);
	char* cpDescription=(char*)malloc(strlen(description)+1);
	addingNode->description = strcpy(cpDescription,description);
	LinkedListAdd(dictionary->linkedList,addingNode);
	return 0;
}

int DictionaryRemove(Dictionary* dictionary, char* key){
	LinkedListRemove(dictionary->linkedList,key,&comparer, &destructor);
	return 0;
}

char* DictionaryDescriptionSearch(Dictionary* dictionary, char* key){
	DictionaryNode* node = dictionaryNodeSearch(dictionary,(void*)key);	
	if(node==NULL)
		return NULL;
	return node->description;
}

char DictionaryForeachInit(Dictionary* dictionary){
	LinkedListForeachInit(dictionary->linkedList);
	return 0;
}

DictionaryNode* DictionaryNext(Dictionary* dictionary){
	DictionaryNode* node = (DictionaryNode*)LinkedListNext(dictionary->linkedList);
	return node;
}

