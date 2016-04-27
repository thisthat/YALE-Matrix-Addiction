#include <iostream> //Basic I/O
#include <pthread.h>
#include "YSMF.hpp"

void helper();

struct threadData{
	int start;
	int end;
	int id;
	pthread_t tid;
	YSMF *c;
};
