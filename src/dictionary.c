#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dictionary.h"
#include "../include/linkedlist.h"


char destructor(void* data){
	if (data==NULL){
		perror("Dictionary destructor: Somehow node exist in list, but not conain data");
		return -1;
	}
	free(((DictionaryNode*)data)->key);
	free(((DictionaryNode*)data)->description);
	return 0;
}
char comparer(void* data, void* key){
	if(data==NULL){
		perror("Dictionary comparer: Somehow node exist in list, but not conain data");
		return -1; //should define comparer error
	}
	int result = strcmp(((DictionaryNode*)data)->key,(char*)key);
	if(result==0){
		return 0;
	}
	return 1;
}

DictionaryNode* dictionaryNodeSearch(Dictionary* dictionary,char* key){
	return (DictionaryNode*)GetElement(dictionary->linkedList,(void*)key,&comparer);
}
Dictionary* DictionaryInitialize(){
	Dictionary* dictionary=(Dictionary*)malloc(sizeof(dictionary));
	dictionary->linkedList=LinkedListInitialize();
	return dictionary;
}

char DictionaryAdd(Dictionary* dictionary,const char* key, const char* description){
	DictionaryNode* addingNode = (DictionaryNode*)malloc(sizeof(DictionaryNode));
	if(addingNode==NULL){
		perror("Can't allocate memory for DictionaryNode");
		return -1;
	}
	char* cpKey=(char*)malloc(strlen(key)+1);
	if(cpKey==NULL){
		perror("Can't allocate memory for key in DictionaryNode");
		return -1;
	}
	addingNode->key = strcpy(cpKey,key);
	char* cpDescription=(char*)malloc(strlen(description)+1);
	if(cpDescription==NULL){
		perror("Can't allocate memory for description in DictionaryNode");
		return -1;
	}
	addingNode->description = strcpy(cpDescription,description);
	if(LinkedListAdd(dictionary->linkedList,addingNode)!=0)
		return -1;
	return 0;
}

char DictionaryRemove(Dictionary* dictionary, char* key){
	if(LinkedListRemove(dictionary->linkedList,key,&comparer, &destructor)!=0)
		return -1;
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

