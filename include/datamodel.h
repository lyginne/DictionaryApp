#ifndef H_DATAMODEL
#define H_DATAMODEL

int Initialize(char* dataFile);
int Add(char* key, char* description);
int Remove(char* key);
char *Search(char* key);
int Initialize(char* dataFile);

#endif
