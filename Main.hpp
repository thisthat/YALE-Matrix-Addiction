#include <iostream> //Basic I/O
#include <pthread.h>
void helper();

struct threadData{
	int start;
	int end;
	pthread_t id;
};