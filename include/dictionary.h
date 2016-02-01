#include "linkedlist.h"
#ifndef H_DICTIONARY
#define H_DICTIONARY
typedef struct DictionaryNode{
	char* key;
	char* description;
}DictionaryNode;

typedef struct Dictionary{
	LinkedList* linkedList;
	int count;
}Dictionary;
int DictionaryAdd(Dictionary* dictionary,char* key, char* description);
int DictionaryRemove(Dictionary* dictionary, char* key);
char* DictionaryDescriptionSearch(Dictionary* dictionary, char* key);
Dictionary* DictionaryInitialize();
#endif
