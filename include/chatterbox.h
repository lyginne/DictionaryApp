#ifndef H_CHATTERBOX
#define H_CHATTERBOX
char ListenerAddCallbacks(char (*addRequestCallback)(char* key, char* description), char (*removeRequestCallback)(char* key), char* (*searchRequestCallback)(char* key));
char listen();
#endif
