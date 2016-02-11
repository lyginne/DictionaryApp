#ifndef H_CHATTERBOX
#define H_CHATTERBOX

typedef enum {
	ADDREQUESTCALLBACK_SUCCEED,
	ADDREQUESTCALLBACK_FAILED,
	ADDREQUESTCALLBACK_ALREADYEXIST
} AddRequestCallbackResult;

typedef enum {
	REMOVEREQUESTCALLBACK_SUCCEED,
	REMOVEREQUESTCALLBACK_FAILED,
	REMOVEREQUESTCALLBACK_NOTFOUND
} RemoveRequestCallbackResult;

typedef enum {
	SEARCHREQUESTCALLBACK_SUCCEED,
	SEARCHREQUESTCALLBACK_FAILED,
	SEARCHREQUESTCALLBACK_NOTFOUND
} SearchRequestCallbackResult;

typedef AddRequestCallbackResult (*AddRequestCallback)(char* key, char* description);
typedef RemoveRequestCallbackResult (*RemoveRequestCallback)(char* key);
typedef SearchRequestCallbackResult (*SearchRequestCallback)(char* key, char** description);

void ListenerAddCallbacks(AddRequestCallback addRequestCallback, RemoveRequestCallback removeRequestCallback, SearchRequestCallback searchRequestCallback);
char listen();

#endif
