#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "../include/linkedlist.h"

/*function 
 * returns the first element with key compared by comparer and NULL if error or not found
 * mem-O(1)
 * dif-O(n) - that's bad and u should feel bad, but since the other dificulty needs another structure - let it be*/
LinkedListSearchResult LinkedListSearch(LinkedList* list,void** data, void* key, char (*comparer)(void* data,void* key)){
        if(list->firstNode==NULL){
		*data=NULL;
                return LINKEDLISTSEARCHRESULT_NOTFOUND;
        }
	LinkedListNode* node=list->firstNode;
        while (node!=NULL) {
		char compresult = comparer(node->data,key);
		if(compresult==0){
			*data=node->data;
			return LINKEDLISTSEARCHRESULT_SUCCEED;
		}
		else if(compresult==-1){
			*data=NULL;
			//Comparer signals an error;
			return LINKEDLISTSEARCHRESULT_FAILED;
		}
		node=node->node;
        }
	return LINKEDLISTSEARCHRESULT_NOTFOUND;
}

/*function adds the element on the list, to make it O(1) - in the first position
 * returns 0 if everyth going ok and -1 if not
 * mem-O(1)
 * dif-O(1)*/
LinkedListAddResult LinkedListAdd(LinkedList* list,void* data){
	//Add element to linked list
	LinkedListNode* newNode;
	LinkedListNode* prevFirstNode;

	newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	if (newNode==NULL){
		perror("Can't alloc mem for new linked list node");
		return LINKEDLISTADDRESULT_FAILED;
	}
	prevFirstNode=list->firstNode;	
	newNode->node=prevFirstNode;	
	list->firstNode=newNode;
	newNode->data = data;
	return LINKEDLISTADDRESULT_SUCCEED;
}

/*function deletes the first element with a key compared by comparer
 * returns -1 if error
 * returns 0 if ok
 * mem-O(1)
 * dif-O(n) - and that's bad again, see method GetElement and it's comments for details*/
LinkedListRemoveResult LinkedListRemove(LinkedList* list, void* key, char (*comparer)(void* data, void* key), char (*destruct)(void* data)){
        if(list->firstNode==NULL){
                return LINKEDLISTREMOVERESULT_NOTFOUND;
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
			else{
				prevNode->node=node->node;
			}
			if(destruct(node->data)!=0){
				free(node);
				//if we can't destruct node data, return -1;
				return LINKEDLISTADDRESULT_FAILED;
			}
			free(node);
			return LINKEDLISTREMOVERESULT_SUCCEED;
		}
		else if(compresult==-1){
			//Comparer signals an error;
			return LINKEDLISTREMOVERESULT_FAILED;
		}
		prevNode=node;
		node=node->node;
        }
	return LINKEDLISTREMOVERESULT_NOTFOUND; 
}
/* function allocates memmory for LinkedList
 * returns NULL if failed*/
LinkedList* LinkedListInitialize(){
	LinkedList* linkedList = (LinkedList*)malloc(sizeof(LinkedList));
	if (linkedList==NULL){
		perror("LinkedListInitialize: Can't alloc mem for new linked list");
		return NULL;
	}
	linkedList->foreachNode=NULL;
	linkedList->firstNode=NULL;
	return linkedList;
}
/* function prepares LinkedList struct to use LinkedListNext function ca't fail if list is ok*/
void LinkedListForeachInit(LinkedList* list){
	list->foreachNode = list->firstNode;
}
/* function returns void* data each time to the next node 
 * can't fail except for sigfault*/
void* LinkedListNext(LinkedList* list){
	if(list->foreachNode==NULL)
		return NULL;
	void* data = list->foreachNode->data;
	list->foreachNode=list->foreachNode->node;
	return data;		
}

