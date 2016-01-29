#include <stdlib.h>
#include "../include/linkedlist.h"

void* GetElementByNumber(LinkedList list,int position){
	int passed = 0;
	LinkedListNode* node=LikedList->firstNode;
	while(1){
		if (passed==position){
			return node;
		}
		if(node->node==null){
			return null;
		}
		node=node->node;
		passed++;
	}
}

int LinkedListAdd(LinkedList list,void* data,int position){
	//Add element to linked list
	node* prevNode;
	node* newNode;

	node* newNode = malloc(sizeof(linkedListNode));
	if (newNode==null){
		return -1;
	}
	//if we add in first position we need to modify LinkedList structure
	if(position==0){
		newNode->node=list->fistNode;	
		list->firstNode=newNode;
	}
	else{
		node* prevNode = getNodeByNumber(position-1);
		if(prevNode==null){
			return -1;
		}
		newNode->node = prevNode->node;
		prevNode->node = newNode;
	}
	newNode->data = data;
	return 0;
}

int LinkedListRemove(LinkedList list,int position){
	node* currentNode;
	node* prevNode;

	prevNode=getNodeByNumber(position-1);
	if(prevNode==null){
		return -1;
	}
	currentNode=prevNode->node;
	prevNode->node=prevNode->node->node;
	free(currentNode);
}

