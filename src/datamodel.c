#include <stdlib.h>
#include "../include/datamodel.h"
#include "../include/dictionary.h"

static Dictionary* dictionary;

int Initialize(char* dataFile){
	dictionary = DictionaryInitialize();

	//TODO IMPLEmENT DIS
}

int Add(char* key, char* description){
	DictionaryAdd(dictionary,key, description);
}

int Remove(char* key){
	DictionaryRemove(dictionary, key);
}

char *Search(char* key){
	DictionaryDescriptionSearch(dictionary, key);
}
