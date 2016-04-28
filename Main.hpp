#include <iostream> //Basic I/O
#include <pthread.h>
#include <sys/stat.h>
#include <fstream>
#include "YSMF.hpp"

void helper();

struct threadData{
	int start;
	int end;
	int id;
	pthread_t tid;
	YSMF *c;
};

inline bool exists (const std::string& name) {
	struct stat buffer;
	return (stat (name.c_str(), &buffer) == 0);
}

void printVector(std::vector<int>* path){
	for (std::vector<int>::const_iterator i = path->begin(); i != path->end(); ++i)
		std::cout << *i << ' ';
}