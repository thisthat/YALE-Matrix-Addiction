#include "Mul.hpp"


Mul::Mul(YSMF *a, YSMF *b) {
	_a = a;
	_b = b;
}

Mul::~Mul() {

}

YSMF *Mul::calulate(int startLine, int endLine) {
	struct threadData data;
	int b1 = (int)(_b->getRows()/3);
	data.start = 0;
	data.end = b1;

	struct threadData data2;
	data.start = b1;
	data.end = b1+b1;

	struct threadData data3;
	data.start = b1+b1;
	data.end = _a->getRows();

	std::thread first (&Mul::th_calulate, this, data);
	std::thread second (&Mul::th_calulate, this, data2);
	std::thread third (&Mul::th_calulate, this, data2);
	first.join();
	second.join();
	third.join();
	return new YSMF(_a->getRows(), _b->getCols());
}

void Mul::th_calulate(struct threadData data) {
	int maxColB = _b->getCols();
	std::vector<int> *aA = _a->getA();
	std::vector<int> *aJA = _a->getJA();
	int sum ;
	int startLine = data.start;
	int endLine = data.end;
	YSMF *matrix = new YSMF(_a->getRows(), maxColB);
	for(int i = startLine; i < endLine; i++){
		for(int j = 0; j < maxColB; j++){
			sum = 0;
			for(int k = 0; k < maxColB; k++){
				sum += _a->getElement(i,k) * _b->getElement(k, j);
			}
			matrix->addElement(sum, i, j);
		}
	}
	//return matrix;
}





