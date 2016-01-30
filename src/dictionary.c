#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dictionary.h"
#include "../include/linkedlist.h"


DictionaryNode* dictionaryNodeSearch(Dictionary* dictionary,char* key){
	int last = dictionary->count;
	int first = 0;

	int result;
	if(dictionary->count==0){
		return NULL;
	}
	while (first < last) {
		int mid = first + ((last - first) >> 1);

		DictionaryNode* candidat = GetElementByNumber(dictionary->linkedList,mid);
		result=strcmp(candidat->key,key);
		if (result==0){
			return candidat; 
		}
		else if(result<0){
			last = mid;
		}
		else{
			first = mid + 1;
		}
    	}
}

int dictionaryPositionSearch(Dictionary* dictionary,char* key){
	int result;
	int last = dictionary->count;
        int first = 0;

        if(dictionary->count==0){
                return -1;
        }
        while (first < last) {
		int mid = first + ((last - first) >> 1);

		DictionaryNode* candidat = GetElementByNumber(dictionary->linkedList,mid);
		result=strcmp(candidat->key,key);
		if (result==0){
			return mid;
                }
		else if(result<0){
			last = mid;
		}
		else{
			first = ++mid;
		}
	}
}

int dictionaryAddingPositionSearch(Dictionary* dictionary,char* key){
	int prevCompResult;
	int nextCompResult;
        int last = dictionary->count;
        int first = 0;

        if(dictionary->count==0){
                return -1;
        }
        while (first < last) {
                int mid = first + ((last - first) >> 1);
                
                DictionaryNode* potencialPrevCandidat = GetElementByNumber(dictionary->linkedList,mid);
		DictionaryNode* potencialNextCandidat = GetElementByNumber(dictionary->linkedList,mid+1);
                prevCompResult=strcmp(potencialPrevCandidat->key,key);
                nextCompResult=strcmp(potencialNextCandidat->key,key);
                if (prevCompResult<0&&nextCompResult>0){
                        return mid+1;
                }
                else if(prevCompResult<0&&nextCompResult<0){
                        last = mid;
                }
                else{
                        first = ++mid;
                }
        }

}

int DictionaryAdd(Dictionary* dictionary,char* key, char* description){
	DictionaryNode* addingNode = (DictionaryNode*)malloc(sizeof(DictionaryNode));
	addingNode->key = key;
	addingNode->description = description;
	int position = dictionaryAddingPositionSearch(dictionary,key);
	LinkedListAdd(dictionary->linkedList,addingNode,position);
}

DictionaryRemove(Dictionary* dictionary, char* key){
	int position = dictionaryPositionSearch(dictionary,key);
	LinkedListRemove(dictionary->linkedList,position);
}

char* DictionaryDescriptionSearch(Dictionary* dictionary, char* key){
	DictionaryNode* node = dictionaryNodeSearch(dictionary,key);	
}

