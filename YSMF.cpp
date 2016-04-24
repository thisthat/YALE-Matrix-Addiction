#include "YSMF.hpp"

void getRowElement(int i);

YSMF::YSMF(int nRows, int nCols, double fillPerc){
	_nRows = nRows;
	_nCols = nCols;
	_fill  = fillPerc;
    NNZ = (int) ((double)_nRows * (double)_nCols * _fill);
    std::cout << "NZZ=" << NNZ << std::endl;
    A = std::vector<int>( NNZ);
    IA = std::vector<int>( _nRows + 1); //we have to think about a random accomulative function
    JA = std::vector<int>( NNZ ); //rand() * _nCols
    fillMatrix();
}

YSMF::~YSMF() {
	A.clear();
	std::vector<int>(A).swap(A);
	IA.clear();
	std::vector<int>(IA).swap(IA);
	JA.clear();
	std::vector<int>(JA).swap(JA);

}

void YSMF::print() {
    std::cout << "Vector A - " << NNZ << std::endl;
    for(int i = 0; i < NNZ; i++){
        std::cout << " " << A[i];
    }
    std::cout << std::endl;

    std::cout << "Vector JA - " << NNZ << std::endl;
    for(int i = 0; i < NNZ; i++){
        std::cout << " " << JA[i];
    }
    std::cout << std::endl;

    std::cout << "Vector IA - " << _nRows +1 << std::endl;
    for(int i = 0; i < (_nRows+1); i++){
        std::cout << " " << IA[i];
    }
    std::cout << std::endl;
	std::cout << "_____ MATRIX ____" << std::endl;
	//print matrix
	int indexA = 0;
	std::string elm;
	for(int i = 0; i < _nRows; i++){
		for(int j = 0; j < _nCols; j++){
			elm = std::to_string(getElement(i,j)) + " ";
			std::cout << elm;
		}
		std::cout << std::endl;
	}
}


int YSMF::getElement(int i, int j){
	int d = IA[i+1] - IA[i];
	if(d > 0){
		std::pair<std::vector<int>, std::vector<int>> row = getRow(i);
		for(int k = 0; k < row.first.size(); k++){
			if(j == row.second[k])
				return row.first[k];
		}
	}
	return 0;
}

std::vector<int> YSMF::getRowElement(int i){
	int d = IA[i+1] - IA[i];
	std::vector<int> ret;
	if(d > 0){
		int index = IA[i+1] - d;
		int j = 0;
		ret = std::vector<int>(d);
		for (int k = index; k < (index+d); k++) {
			ret[j++] = A[k];
		}
	}
	else ret = std::vector<int>(0);
	return ret;
}

std::vector<int> YSMF::getRowJA(int i){
	int d = IA[i+1] - IA[i];
	std::vector<int> ret;
	if(d > 0){
		int index = IA[i+1] - d;
		int j = 0;
		ret = std::vector<int>(d);
		for (int k = index; k < (index+d); k++) {
			ret[j++] = JA[k];
		}
	}
	return ret;
}

std::pair<std::vector<int>, std::vector<int>> YSMF::getRow(int i){
	return std::pair<std::vector<int>, std::vector<int>>( getRowElement(i), getRowJA(i));
}


void YSMF::fillMatrix() {
    std::mt19937_64 rng;
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);
    std::uniform_real_distribution<double> unif(0, 1);

    //Fill IA
    IA[0] = 0;
    int ndd = NNZ;
    int dist;
    double PP = (double)_nRows / (double)NNZ;
	if(PP < 1.0){
		//it works only if number of row are lower then the number of non zero elements
		for(int i = 1; i < _nRows; i++){
			double p = unif(rng);
			if(p > PP){
				int n = 1;
				dist = _nRows - i;
				n = (ndd / dist);
				ndd -= n;
				IA[i] = IA[i-1] + n;
			}
			else
				IA[i] = IA[i-1];
		}
		IA[_nRows] = NNZ;
	}
	else {
		//otherwise use 0.5 as threshold
		PP = 0.5;
		for(int i = 1; i < _nRows; i++){
			double p = unif(rng);
			if(p > PP){
				int n = 1;
				dist = _nRows - i;
				n = (ndd / dist);
				ndd -= n;
				IA[i] = IA[i-1] + n;
			}
			else
				IA[i] = IA[i-1];
		}
		IA[_nRows] = NNZ;
	}

	//Fill A
	for(int i = 0; i < NNZ; i++){
		A[i]  = (int) (unif(rng) * 9) + 1;
		if(i > 0){
			//check that element of the same row are in different cols and always in l2r order
			do{
				JA[i] = ( (int) (unif(rng) * _nCols) );
			} while(JA[i] == JA[i-1] );
		}

	}


	//fill JA
	int i = 0;
	//check that element of the same row are in different cols and always in l2r order
	for(int j = 0; j < _nRows; j++){ // i == NNZ at the end of the cicle -> nice property to show
		int howManyPerRow = getRowElement(j).size();
		std::vector<int> tmp(howManyPerRow);
		int k = 0;
		while(howManyPerRow > 0){
			int elm = (int) (unif(rng) * _nCols);
			//avoid two element on the same column
			if(std::find(tmp.begin(), tmp.end(), elm) == tmp.end())
			{
				tmp[k++] = elm;
				howManyPerRow--;
			}
		}
		//l2r fill
		std::sort(tmp.begin(), tmp.end());
		for(int ii = 0; ii < tmp.size(); ii++){
			JA[i++] = tmp[ii];
		}
	}
}








