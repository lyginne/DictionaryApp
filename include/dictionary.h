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
#endif
