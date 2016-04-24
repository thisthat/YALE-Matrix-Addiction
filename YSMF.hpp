#include <vector>
#include <iostream>
#include <random>

class YSMF {
	public:
		YSMF(int nRows, int nCols, double fillPerc);
		~YSMF();
		void print(); //Debug Purpose
		int getElement(int i, int j);
		std::vector<int> getRowElement(int i);
		std::pair<std::vector<int>, std::vector<int>> getRow(int i);
		std::vector<int> getRowJA(int i);
	private:
		int _nRows, _nCols, NNZ;
		double _fill;
		std::vector<int> A;
        std::vector<int> IA;
        std::vector<int> JA;
		void fillMatrix();


};

