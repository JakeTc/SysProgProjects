#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

//gets the next command from file
//assumes that file is already open
char* getCommand(FILE* fp) {
	
}

//gets the timestring for the locat time, and returns char* to it
char* getTime() {
	time_t rawtime;
	struct tm* ltime;
	//struct tm* currTime = (struct tm*)malloc(sizeof(struct tm));
	
	time(&rawtime);
	ltime = localtime(&rawtime);
	
	char* timeStr = (char*)malloc(64);
	snprintf(timeStr, 64,"%d%d %d %s\n", ltime->tm_hour, ltime->tm_min, ltime->tm_mday, months[ltime->tm_mon]); 
	//memcpy(currTime, time, sizeof(struct tm));
	return timeStr;
	
}
//checks if an argument was given
//opens a file descriptor
int init(int argc, char* argv[]) {
	//checks if there is an argument in argv
	//if not, returns
	if(argc == 1) {
		char* time = getTime();
		printf("Error: NO arguments given @ %s\n", time);
		return -2;
	}
	
	return open("fileIn.txt", O_RDONLY | O_CREAT, 00700);
}



int main(int argc, char* argv[]) {
	//making file descriptor, doing checks
	//if -1. means there was an error
	int retval = init(argc, argv);
	if(retval == -2) {
		return 0;
	} else if(retval == -1) {
		printf("Error: File was not found\n");
	}
	
	
	
	
	return 0;
}
