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

typedef enum {
	LINKEDLISTADDRESULT_SUCCEED,
	LINKEDLISTADDRESULT_FAILED
} LinkedListAddResult;

typedef enum {
	LINKEDLISTSEARCHRESULT_SUCCEED,
	LINKEDLISTSEARCHRESULT_FAILED,
	LINKEDLISTSEARCHRESULT_NOTFOUND
} LinkedListSearchResult;

typedef enum {
	LINKEDLISTREMOVERESULT_SUCCEED,
	LINKEDLISTREMOVERESULT_FAILED,
	LINKEDLISTREMOVERESULT_NOTFOUND
} LinkedListRemoveResult;
	

LinkedListSearchResult LinkedListSearch(LinkedList* list, void** data, void* key, char (*comparer)(void* data,void* key));
LinkedListAddResult LinkedListAdd(LinkedList* list, void* data);
LinkedListRemoveResult LinkedListRemove(LinkedList* list, void* key, char (*comparer)(void* data,void* key), char (*destructor)(void* data));
LinkedList* LinkedListInitialize();
void LinkedListForeachInit(LinkedList* list);
void* LinkedListNext(LinkedList* list);
#endif
