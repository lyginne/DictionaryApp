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

typedef enum {
	DICTIONARYADDRESULT_SUCCED,
	DICTIONARYADDRESULT_FAILED,
	DICTIONARYADDRESULT_ALREADYEXIST
} DictionaryAddResult;

typedef enum {
	DICTIONARYREMOVERESULT_SUCCED,
	DICTIONARYREMOVERESULT_FAILED,
	DICTIONARYREMOVERESULT_NOTFOUND
} DictionaryRemoveResult;

typedef enum {
	DICTIONARYSEARCHRESULT_SUCCED,
	DICTIONARYSEARCHRESULT_FAILED,
	DICTIONARYSEARCHRESULT_NOTFOUND
} DictionarySearchResult;

DictionaryAddResult DictionaryAdd(Dictionary* dictionary,char* key,char* description);
DictionaryRemoveResult DictionaryRemove(Dictionary* dictionary, char* key);
DictionarySearchResult DictionaryDescriptionSearch(Dictionary* dictionary, char* key, char** description);
Dictionary* DictionaryInitialize();
void DictionaryForeachInit(Dictionary* dictionary);
DictionaryNode* DictionaryNext(Dictionary* dictionary);

#endif
