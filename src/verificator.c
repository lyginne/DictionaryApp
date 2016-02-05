#include <string.h>
#include "../include/verificator.h"
char validateString(const char* key){
        if(strlen(key)==0){
                return STRING_UNVALID;
        }
        return STRING_VALID;
}

