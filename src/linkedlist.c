#include <stdlib.h>
#include <stddef.h>
#include "../include/linkedlist.h"

/*function returns the first element with key compared by comparer
* mem-O(1)
* dif-O(n) - that's bad and u should feel bad, but since the other dificulty needs another structure - let it be*/
void* GetElement(LinkedList* list,char* key, char (*comparer)(void* data,void* key)){
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

/*function adds the element on the list, to make it O(1) - in the first position
 * mem-O(1)
 * dif-O(1)*/
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

/*function deletes the first element with a key compared by comparer
 * mem-O(1)
 * dif-O(n) - and that's bad again, see method GetElement and it's comments for details*/
int LinkedListRemove(LinkedList* list,char* key, char (*comparer)(void* data, void* key)){
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

