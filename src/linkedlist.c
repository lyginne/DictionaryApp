#include <stdlib.h>
#include "../include/linkedlist.h"

void* GetElementByNumber(LinkedList* list,int position){
	int passed = 0;
	LinkedListNode* node=list->firstNode;
	while(1){
		if (passed==position){
			return node;
		}
		if(node->node==NULL){
			return NULL;
		}
		node=node->node;
		passed++;
	}
}

int LinkedListAdd(LinkedList* list,void* data,int position){
	//Add element to linked list
	LinkedListNode* prevNode;
	LinkedListNode* newNode;

	newNode = malloc(sizeof(LinkedListNode));
	if (newNode==NULL){
		return -1;
	}
	//if we add in first position we need to modify LinkedList structure
	if(position==0){
		newNode->node=list->firstNode;	
		list->firstNode=newNode;
	}
	else{
		prevNode = GetElementByNumber(list, position-1);
		if(prevNode==NULL){
			return -1;
		}
		newNode->node = prevNode->node;
		prevNode->node = newNode;
	}
	newNode->data = data;
	return 0;
}

int LinkedListRemove(LinkedList* list,int position){
	LinkedListNode* currentNode;
	LinkedListNode* prevNode;

	//Not yet implemented
	//prevNode=getNodeByNumber(position-1);
	if(prevNode==NULL){
		return -1;
	}
	currentNode=prevNode->node;
	prevNode->node=prevNode->node->node;
	free(currentNode);
}

