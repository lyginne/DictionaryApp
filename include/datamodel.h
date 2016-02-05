#ifndef H_DATAMODEL
#define H_DATAMODEL

char Initialize(char* dataFile);
char Add(char* key, char* description);
char Remove(char* key);
char *Search(char* key);
char Initialize(char* dataFile);
char DataWriteToFile(char* dataFile);


#endif
