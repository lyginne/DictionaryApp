#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "../include/dictionary.h"
#include "../include/linkedlist.h"


char comparer(void* data, char* key){
	if(data=NULL){
		return 0x80; //should define comparer error
	}
	return strcmp(((DictionaryNode*)data)->key,key);
}

DictionaryNode* dictionaryNodeSearch(Dictionary* dictionary,char* key){
	return (DictionaryNode*)GetElement(dictionary->linkedList,key,&comparer);
}

int DictionaryAdd(Dictionary* dictionary,char* key, char* description){
	DictionaryNode* addingNode = (DictionaryNode*)malloc(sizeof(DictionaryNode));
	addingNode->key = key;
	addingNode->description = description;
	LinkedListAdd(dictionary->linkedList,addingNode);
}

DictionaryRemove(Dictionary* dictionary, char* key){
	LinkedListRemove(dictionary->linkedList,key,&comparer);
}

char* DictionaryDescriptionSearch(Dictionary* dictionary, char* key){
	DictionaryNode* node = dictionaryNodeSearch(dictionary,key);	
}

