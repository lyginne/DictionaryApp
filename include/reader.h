#ifndef H_READER
#define H_READER

char ReaderGetWholeDamnString(int fd, char** lineptr);
char ReaderReadLine(FILE* file, char** linePtr);

#endif
