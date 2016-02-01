#ifndef H_CHATTERBOX
#define H_CHATTERBOX
int ListenerAddCallbacks(char (*addRequestCallback)(char* key, char* description), char (*removeRequestCallback)(char* key), char* (*searchRequestCallback)(char* key));
int listen();
#endif
