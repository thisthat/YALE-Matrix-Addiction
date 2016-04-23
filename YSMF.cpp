#include <iostream>
#include "YSMF.hpp"

YSMF::YSMF(int nRows, int nCols, int fillPerc){
	_nRows = nRows;
	_nCols = nCols;
	_fill  = fillPerc;
    NNZ = _nRows * _nCols / _fill;
    A = std::vector<int>( NNZ);
    IA = std::vector<int>( _nRows + 1); //we have to think about a random accomulative function
    JA = std::vector<int>( NNZ ); //rand() * _nCols
}

YSMF::~YSMF() {

}

void YSMF::print() {
}

void YSMF::fillMatrix() {

}





