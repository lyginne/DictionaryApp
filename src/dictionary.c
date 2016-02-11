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
	free(data);
	return 0;
}
char comparer(void* data, void* key){
	if(data==NULL){
		perror("Dictionary comparer: Somehow node exist in list, but not conain data");
		return -1;
	}
	int result = strcmp(((DictionaryNode*)data)->key,(char*)key);
	if(result==0){
		return 0;
	}
	return 1;
}

/* returns DictionarySearchResult
 * writes the found DictionaryNode* to the *node*/
DictionarySearchResult dictionaryNodeSearch(Dictionary* dictionary, char* key, DictionaryNode** returnNode){
	*returnNode = NULL;
	DictionaryNode* node = NULL;
	DictionarySearchResult result = LinkedListSearch(dictionary->linkedList, (void**) &node, (void*)key, &comparer);
	if ( result==LINKEDLISTSEARCHRESULT_FAILED)
		return DICTIONARYSEARCHRESULT_FAILED;
	if ( result==LINKEDLISTSEARCHRESULT_NOTFOUND)
		return DICTIONARYSEARCHRESULT_NOTFOUND;
	if ( result==LINKEDLISTSEARCHRESULT_SUCCEED){
		*returnNode=node;
		return DICTIONARYSEARCHRESULT_SUCCED;
	}
	return DICTIONARYSEARCHRESULT_FAILED; 
}

/* returns NULL if failed
 * returns Dictionary* if SUCCEED*/
Dictionary* DictionaryInitialize(){
	Dictionary* dictionary=(Dictionary*)malloc(sizeof(dictionary));
	if(dictionary==NULL){
		perror("Can't allocate dictionary");
		return NULL;
	}
	dictionary->linkedList=LinkedListInitialize();
	if(dictionary->linkedList==NULL){
		free(dictionary);
		return NULL;
	}
	return dictionary;
}

/* return 0 if ok
 * return -1 on error */
DictionaryAddResult DictionaryAdd(Dictionary* dictionary,char* key, char* description){
	DictionaryNode* node=NULL;
	DictionarySearchResult result = dictionaryNodeSearch(dictionary,(void*)key, &node);
	if(result==DICTIONARYSEARCHRESULT_SUCCED)
		return DICTIONARYADDRESULT_ALREADYEXIST;
	DictionaryNode* addingNode = (DictionaryNode*)malloc(sizeof(DictionaryNode));
	if(addingNode==NULL){
		perror("Can't allocate memory for DictionaryNode");
		return DICTIONARYADDRESULT_FAILED;
	}
	char* cpKey=(char*)malloc(strlen(key)+1);
	if(cpKey==NULL){
		free(addingNode);
		perror("Can't allocate memory for key in DictionaryNode");
		return DICTIONARYADDRESULT_FAILED;
	}
	addingNode->key = strcpy(cpKey,key);
	char* cpDescription=(char*)malloc(strlen(description)+1);
	if(cpDescription==NULL){
		free(addingNode);
		free(cpKey);
		perror("Can't allocate memory for description in DictionaryNode");
		return DICTIONARYADDRESULT_FAILED;
	}
	addingNode->description = strcpy(cpDescription,description);
	if(LinkedListAdd(dictionary->linkedList,addingNode)==LINKEDLISTADDRESULT_FAILED){
		free(addingNode);
		free(cpKey);
		free(cpDescription);
		return DICTIONARYADDRESULT_FAILED;
	}
	return DICTIONARYADDRESULT_SUCCED;
}

DictionaryRemoveResult DictionaryRemove(Dictionary* dictionary, char* key){
	LinkedListRemoveResult result = LinkedListRemove(dictionary->linkedList, key, &comparer, &destructor);
	if(result==LINKEDLISTREMOVERESULT_SUCCEED)
		return DICTIONARYREMOVERESULT_SUCCED;
	if(result==LINKEDLISTREMOVERESULT_NOTFOUND)
		return DICTIONARYREMOVERESULT_NOTFOUND;
	return DICTIONARYREMOVERESULT_FAILED;
}

DictionarySearchResult DictionaryDescriptionSearch(Dictionary* dictionary, char* key, char** description){
	DictionaryNode* node=NULL;
	*description=NULL;
	DictionarySearchResult result = dictionaryNodeSearch(dictionary,(void*)key, &node);
	if(result==DICTIONARYSEARCHRESULT_SUCCED)
		*description=node->description;
	return result;
}

/* function prepares Dictionary to use DictionaryNext function
 * function can't fail */
void DictionaryForeachInit(Dictionary* dictionary){
	LinkedListForeachInit(dictionary->linkedList);
}

/* returns next DictionaryNode each time it's called
 * can't fail */
DictionaryNode* DictionaryNext(Dictionary* dictionary){
	DictionaryNode* node = (DictionaryNode*)LinkedListNext(dictionary->linkedList);
	return node;
}

