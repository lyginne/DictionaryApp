#include <stdlib.h>
#include <stddef.h>
#include "../include/linkedlist.h"

void* GetElement(LinkedList* list,char* key, char (*comparer)(void* data,char* key)){
        if(list->firstNode==NULL){
                return NULL;
        }
	LinkedListNode* node=list->firstNode;
        while (node!=NULL) {
		if(comparer(node->data,key)==0){
			return node;
		}
		node=node->node;
        }
	return NULL;
}

int LinkedListAdd(LinkedList* list,void* data){
	//Add element to linked list
	LinkedListNode* newNode;

	newNode = malloc(sizeof(LinkedListNode));
	if (newNode==NULL){
		return -1;
	}
	newNode->node=list->firstNode;	
	list->firstNode=newNode;
	newNode->data = data;
	return 0;
}

int LinkedListRemove(LinkedList* list,char* key, char (*comparer)(void* data, char* key)){
        if(list->firstNode==NULL){
                return -1;
        }
	LinkedListNode* node=list->firstNode;
	LinkedListNode* prevNode;
        while (node!=NULL) {
		if(comparer(node->data,key)==0){
			if(prevNode!=NULL){
				list->firstNode=node->node;
			}	
			free(node);
		}
		prevNode=node;
		node=node->node;
        }
}

