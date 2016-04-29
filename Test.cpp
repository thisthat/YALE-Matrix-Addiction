//
// Created by giovanni on 29/04/16.
//
#include "Main.hpp"
int main(int argc, char** argv) {
	YSMF *a;
	a = new YSMF(10, 10, 0.1f);
	a->print();
	std::map<int, std::vector<std::pair<int, int>>> mapA;
	std::vector<std::pair<int, int>> coordinate = a->getElmCoordinate();
	std::vector<int> *aA = a->getA();
	for(int i = 0; i < coordinate.size(); i++){
		//store by row
		mapA[coordinate[i].first].push_back(std::pair<int,int>(coordinate[i].second, aA->at(i)));
	}
	int elm;
	for(int i = 0; i < a->getRows(); i++){
		for(int j = 0; j < a->getCols(); j++){
			std::cout << j << " : ";
			printVector(mapA[j]);
		}
		std::cout << "\n";
	}
}