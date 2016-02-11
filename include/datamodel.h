#ifndef H_DATAMODEL
#define H_DATAMODEL

typedef enum{
	DATAMODELSEARCHRESULT_SUCCEED,
	DATAMODELSEARCHRESULT_FAILED,
	DATAMODELSEARCHRESULT_NOTFOUND
} DataModelSearchResult;

typedef enum{
	DATAMODELADDRESULT_SUCCEED,
	DATAMODELADDRESULT_FAILED,
	DATAMODELADDRESULT_ALREADYEXIST
} DataModelAddResult;

typedef enum{
	DATAMODELREMOVERESULT_SUCCEED,
	DATAMODELREMOVERESULT_FAILED,
	DATAMODELREMOVERESULT_NOTFOUND
} DataModelRemoveResult;

char FillFromFile(char* path);
char Initialize(void);
char DataWriteToFile(char* dataFile);

DataModelAddResult Add(char* key, char* description);
DataModelRemoveResult Remove(char* key);
DataModelSearchResult Search(char* key, char** description);


#endif
