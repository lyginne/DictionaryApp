#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "../include/linkedlist.h"

/*function 
 * returns the first element with key compared by comparer and NULL if error or not found
 * mem-O(1)
 * dif-O(n) - that's bad and u should feel bad, but since the other dificulty needs another structure - let it be*/
void* GetElement(LinkedList* list,char* key, char (*comparer)(void* data,void* key)){
        if(list->firstNode==NULL){
                return NULL;
        }
	LinkedListNode* node=list->firstNode;
        while (node!=NULL) {
		if(comparer(node->data,key)==0){
			return node->data;
		}
		node=node->node;
        }
	return NULL;
}

/*function adds the element on the list, to make it O(1) - in the first position
 * returns 0 if everyth going ok and -1 if not
 * mem-O(1)
 * dif-O(1)*/
int LinkedListAdd(LinkedList* list,void* data){
	//Add element to linked list
	LinkedListNode* newNode;
	LinkedListNode* prevFirstNode;

	newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	if (newNode==NULL){
		return -1;
	}
	prevFirstNode=list->firstNode;	
	newNode->node=prevFirstNode;	
	list->firstNode=newNode;
	newNode->data = data;
	return 0;
}

/*function deletes the first element with a key compared by comparer
 * returns 0 if found and deleted and -1 if not found or error TODO: define the results and make another error notification
 * mem-O(1)
 * dif-O(n) - and that's bad again, see method GetElement and it's comments for details*/
int LinkedListRemove(LinkedList* list,char* key, char (*comparer)(void* data, void* key), char (*destruct)(void* data)){
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
			destruct(node->data);
			free(node);
			prevNode=node;
			node=node->node;
			return 0;
		}
		prevNode=node;
		node=node->node;
        }
	return 0; //not found to remove is not actualy an ordinary stuff
}

LinkedList* LinkedListInitialize(){
	LinkedList* linkedList = (LinkedList*)malloc(sizeof(LinkedList));
	return linkedList;
}
void LinkedListForeachInit(LinkedList* list){
	list->foreachNode = list->firstNode;
}
void* LinkedListNext(LinkedList* list){
	if(list->foreachNode==NULL)
		return NULL;
	void* data = list->foreachNode->data;
	list->foreachNode=list->foreachNode->node;
	return data;		
}
