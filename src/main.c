#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/chatterbox.h"
#include "../include/datamodel.h"

AddRequestCallbackResult addCallback( char* key,  char* description){
	DataModelAddResult result = Add(key,description);
	if(result==DATAMODELADDRESULT_SUCCEED)
		return ADDREQUESTCALLBACK_SUCCEED;
	if(result==DATAMODELADDRESULT_FAILED)
		return ADDREQUESTCALLBACK_FAILED;
	if(result==DATAMODELADDRESULT_ALREADYEXIST)
		return ADDREQUESTCALLBACK_ALREADYEXIST;
	return ADDREQUESTCALLBACK_FAILED;
}

RemoveRequestCallbackResult removeCallback( char* key){
	DataModelRemoveResult result = Remove(key);
	if(result == DATAMODELREMOVERESULT_SUCCEED)
		return REMOVEREQUESTCALLBACK_SUCCEED;
	if(result == DATAMODELREMOVERESULT_FAILED)
		return REMOVEREQUESTCALLBACK_FAILED;
	if(result == DATAMODELREMOVERESULT_NOTFOUND)
		return REMOVEREQUESTCALLBACK_NOTFOUND;
	return REMOVEREQUESTCALLBACK_FAILED;
}

SearchRequestCallbackResult searchCallback( char* key, char** description){
	DataModelSearchResult result = Search(key, description);
	if(result == DATAMODELSEARCHRESULT_SUCCEED)
		return SEARCHREQUESTCALLBACK_SUCCEED;
	if(result == DATAMODELSEARCHRESULT_FAILED)
		return SEARCHREQUESTCALLBACK_FAILED;
	if(result == DATAMODELSEARCHRESULT_NOTFOUND)
		return SEARCHREQUESTCALLBACK_NOTFOUND;
	return SEARCHREQUESTCALLBACK_FAILED;
}
	
int main(int argc, char* argv[]){
	char* path=NULL;
	if(argc>2){
		printf("%s\n","Too much arguments");
		exit(EXIT_FAILURE);	
	}

	if(Initialize()!=0)
		exit(EXIT_FAILURE);

	if(argc==2){
		path=argv[1];
		if(FillFromFile(path)!=0)
			exit(EXIT_FAILURE);
	}

	ListenerAddCallbacks(&addCallback, &removeCallback, &searchCallback);
	if(listen()==0){
		if(argc==2){
			if(DataWriteToFile(path)==0){
				exit(EXIT_SUCCESS);
			}
		}
		exit(EXIT_SUCCESS);
	}
	//Idk if that's a good idea to write data to file while listen() failed, but if you need this, uncomment the following
	/*if(argc==2)
		DataWriteToFile(path);
	*/
	exit(EXIT_FAILURE);

}
