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
		char compresult = comparer(node->data,key);
		if(compresult==0)
			return node->data;
		else if(compresult==-1){
			//Comparer signals an error;
			return NULL;
		}
		node=node->node;
        }
	return NULL;
}

/*function adds the element on the list, to make it O(1) - in the first position
 * returns 0 if everyth going ok and -1 if not
 * mem-O(1)
 * dif-O(1)*/
char LinkedListAdd(LinkedList* list,void* data){
	//Add element to linked list
	LinkedListNode* newNode;
	LinkedListNode* prevFirstNode;

	newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	if (newNode==NULL){
		perror("Can't alloc mem for new linked list node");
		return -1;
	}
	prevFirstNode=list->firstNode;	
	newNode->node=prevFirstNode;	
	list->firstNode=newNode;
	newNode->data = data;
	return 0;
}

/*function deletes the first element with a key compared by comparer
 * returns 1 if found and deleted 
 * returns -1 if error
 * returns 0 if not found
 * mem-O(1)
 * dif-O(n) - and that's bad again, see method GetElement and it's comments for details*/
char LinkedListRemove(LinkedList* list,char* key, char (*comparer)(void* data, void* key), char (*destruct)(void* data)){
        if(list->firstNode==NULL){
                return 0;
        }
	LinkedListNode* node=list->firstNode;
	LinkedListNode* prevNode=NULL;
        while (node!=NULL) {
		char compresult = comparer(node->data,key);
		if(compresult==0){
			if(prevNode==NULL){
				//if we're removing firstNode we should change list structure
				list->firstNode=node->node;
			}	
			if(destruct(node->data)!=0)
				return -1;
			free(node);
			prevNode=node;
			node=node->node;
			return 1;
		}
		else if(compresult==-1){
			//Comparer signals an error;
			return -1;
		}
		prevNode=node;
		node=node->node;
        }
	return 0; 
}
/*function allocates memmory for LinkedList
 * returns NULL if failed*/
LinkedList* LinkedListInitialize(){
	LinkedList* linkedList = (LinkedList*)malloc(sizeof(LinkedList));
	if (linkedList==NULL){
		perror("LinkedListInitialize: Can't alloc mem for new linked list");
		return NULL;
	}
	return linkedList;
}
/* function prepares LinkedList struct to use LinkedListNext function ca't fail if list is ok*/
void LinkedListForeachInit(LinkedList* list){
	list->foreachNode = list->firstNode;
}
/* function returns void* data each time to the next node can't fail if list is ok*/
void* LinkedListNext(LinkedList* list){
	if(list->foreachNode==NULL)
		return NULL;
	void* data = list->foreachNode->data;
	list->foreachNode=list->foreachNode->node;
	return data;		
}

