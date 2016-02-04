#ifndef H_LINKEDLIST
#define H_LINKEDLIST
typedef struct LinkedListNode{
        struct LinkedListNode* node;
        void* data;
} LinkedListNode;

typedef struct LinkedList{
	LinkedListNode* firstNode;
	LinkedListNode* foreachNode;
} LinkedList;

void* GetElement(LinkedList* list,char* key, char (*comparer)(void* data,void* key));
int LinkedListAdd(LinkedList* list,void* data);
int LinkedListRemove(LinkedList* list,char* key, char (*comparer)(void* data, void* key), char (*destructor)(void* data));
LinkedList* LinkedListInitialize();
void LinkedListForeachInit(LinkedList* list);
void* LinkedListNext(LinkedList* list);
#endif
