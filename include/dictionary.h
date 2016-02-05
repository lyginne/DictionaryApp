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
char DictionaryAdd(Dictionary* dictionary,const char* key,const char* description);
char DictionaryRemove(Dictionary* dictionary, char* key);
char* DictionaryDescriptionSearch(Dictionary* dictionary, char* key);
Dictionary* DictionaryInitialize();
char DictionaryForeachInit(Dictionary* dictionary);
DictionaryNode* DictionaryNext(Dictionary* dictionary);

#endif
