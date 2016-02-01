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
			return node;
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
	printf("entered method");
	fflush(stdout);
	//Add element to linked list
	LinkedListNode* newNode;
	LinkedListNode* prevFirstNode;

	newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	printf("123");
	fflush(stdout);
	if (newNode==NULL){
		return -1;
	}
	printf("321");
	fflush(stdout);
	if(list==NULL){
		printf("linkedList is NULL");
		fflush(stdout);
	}
	if(list->firstNode==NULL){
		printf("firstNode is NULL");
		fflush(stdout);
	}
	prevFirstNode=list->firstNode;	
	printf("list is ok\n");

	fflush(stdout);
	
	newNode->node=prevFirstNode;	
	printf("ok");
	fflush(stdout);
	list->firstNode=newNode;
	printf("ok2");
	fflush(stdout);
	newNode->data = data;
	printf("ok3");
	fflush(stdout);
	return 0;
}

/*function deletes the first element with a key compared by comparer
 * returns 0 if found and deleted and -1 if not found or error TODO: define the results and make another error notification
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
			return 0;
		}
		prevNode=node;
		node=node->node;
        }
	return -1;
}

LinkedList* LinkedListInitialize(){
	printf("linkedList initialized");
	fflush(stdout);
	return (LinkedList*)malloc(sizeof(LinkedList));
}
