#include <string.h>
#include "../include/verificator.h"
char validateString(const char* key, size_t ssize){
	if(strlen(key)==0)
		return STRING_UNVALID;
	else if(ssize!=0&&strlen(key)>ssize)
		return STRING_UNVALID;

	while (*key!='\0'){
		if(*key=='\n')
			return STRING_UNVALID;
		if(*key=='\t')
			return STRING_UNVALID;
		key++;
	}

	return STRING_VALID;
}

