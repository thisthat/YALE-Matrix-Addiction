#include <vector>
#include <iostream>
#include <random>

#ifndef __YSMF__
#define __YSMF__ 1

class YSMF {
	public:
		YSMF(int nRows, int nCols, double fillPerc);
		YSMF(int nRows, int nCols);
		~YSMF();
		void print(); //Debug Purpose


		std::vector<std::vector<int>> to_naiveMatrix();

		void addElement(int elm, int row, int col);
		void addElementThread(int elm, int row, int col, int nElmSkip);
		int getElement(int i, int j);
		std::vector<int> getRowElement(int i);
		std::vector<int> getColElement(int j);
		std::vector<int> *getA();
		std::vector<int> *getIA();
		std::vector<int> *getJA();
		std::pair<std::vector<int>, std::vector<int>> getRow(int i);
		std::vector<int> getRowJA(int i);
		int getCols();
		int getRows();
		void export2CSV(char *);
	private:
		int _nRows, _nCols, NNZ;
		double _fill;
		std::vector<int> A;
        std::vector<int> IA;
        std::vector<int> JA;
		void fillMatrix();



};

#endif
