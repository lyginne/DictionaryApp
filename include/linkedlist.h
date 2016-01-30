#ifndef H_LINKEDLIST
#define H_LINKEDLIST
typedef struct LinkedListNode{
        struct LinkedListNode* node;
        void* data;
} LinkedListNode;

typedef struct LinkedList{
	LinkedListNode* firstNode;
	int count;
} LinkedList;

void* GetElementByNumber(LinkedList* list,int position);
int LinkedListAdd(LinkedList* list,void* data,int position);
int LinkedListRemove(LinkedList* list,int position);
#endif
