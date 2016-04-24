#include "YSMF.hpp"
#include <thread>

class Mul {

public:
	Mul(YSMF *a, YSMF *b);
	~Mul();
	YSMF* calulate(int startLine, int endLine);
	struct threadData{
		int start;
		int end;
	};
private:
	YSMF *_a, *_b;
	void th_calulate(struct threadData);
};
