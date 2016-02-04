#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BASIS 1
#define BUF_SIZE 1024

static int flags;
char nonblockfd(int fd){
	flags = fcntl(fd, F_GETFL, 0);
	if(fcntl(fd, F_SETFL, flags | O_NONBLOCK)){
		perror("Can't set stream nonblocking");
		return -1;
	}
	return 0;
}

char restoreflagsfd(int fd){
	if(fcntl(fd,F_SETFL, flags)){
		perror("Can't restore stream flags");
		flags = fcntl(fd, F_GETFL, 0);
		return -1;
	}
	return 0;
}

// *line should be NULL cause we gonna allocate the real size for it
ssize_t ReaderGetWholeDamnString(int fd, char** lineptr){
	char blockingAllowed=1;
	size_t buffsize = 0;
	size_t oldbuffsize;
	char* line = *lineptr;
	if(line!=NULL){
		perror("This finction works with NULL pointers only");
		return -1;
	}
	do{
		oldbuffsize=buffsize;
		buffsize+=BASIS; //more size to buffer
		char* newline=(char*)realloc(line,buffsize+1);//add more memory (+1 to store '\0');
		if(newline==NULL){
			perror("realloc error");
			restoreflagsfd(fd);
			blockingAllowed=1;
			return -1;
		}
		//if realloc done it's job
		line=newline;
		ssize_t ssize = read(fd,line + oldbuffsize, BASIS);//read to buffer where the last one read stoped
		//we should block once only. Any other read should just read.
		if(blockingAllowed){
			if(nonblockfd(fd)!=0){
				free(line);
				return -1;
			}
			blockingAllowed=0;
		}		
		//If read are goona block the stream second time
		if(ssize<0&&errno==EAGAIN){
			if(line[oldbuffsize+ssize-1]=='\n'){
				line[oldbuffsize+ssize-1]='\0';
			}
			line[oldbuffsize+ssize]='\0';
			*lineptr=line;
			if(restoreflagsfd(fd)!=0){
				free(line);
				return -1;
			}
			blockingAllowed=1;
			return strlen(line);//return the count of symbols read	
		}
		if(ssize == 0||ssize != BASIS){
			//This is the end, my only friend, the end.
			//I mean we met <EOF>
			if(oldbuffsize==0i&&ssize==0){
				//if we read nothing and newer allocaded anyth
				restoreflagsfd(fd);
				if(restoreflagsfd(fd)!=0){
					free(line);
					return -1;
				}
				return 0;
			}
			if(line[oldbuffsize+ssize-1]=='\n'){
				line[oldbuffsize+ssize-1]='\0';
			}
			line[oldbuffsize+ssize]='\0';
			*lineptr=line;
			if(restoreflagsfd(fd)!=0){
				free(line);
				return -1;
			}
			blockingAllowed=1;
			return strlen(line);	
		}
	} 
	//look, i know while(1) is not the best, but we need to read untill it's something to read
	while(1);
}

/*ssize_t ReaderGetWholeDamnString(int fd, char** lineptr){
	
}*/
