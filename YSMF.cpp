#include "YSMF.hpp"

void getRowElement(int i);

YSMF::YSMF(int nRows, int nCols, double fillPerc){
	_nRows = nRows;
	_nCols = nCols;
	_fill  = fillPerc;
    NNZ = (int) ((double)_nRows * (double)_nCols * _fill);
    //std::cout << "Fill matrix [" << _nRows << "x"<< _nCols <<"] with NZZ=" << NNZ << std::endl;
    A = std::vector<int>( NNZ);
    IA = std::vector<int>( _nRows + 1);
    JA = std::vector<int>( NNZ );
    fillMatrix();
}

YSMF::YSMF(int nRows, int nCols){
	_nRows = nRows;
	_nCols = nCols;
	A = std::vector<int>( );
	IA = std::vector<int>( _nRows + 1);
	IA.push_back(0);
	JA = std::vector<int>( );
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
	std::cout << "_____ MATRIX " << NNZ << " ____" << std::endl;
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

std::vector<std::vector<int>> YSMF::to_naiveMatrix(){
	//init output variable
	std::vector<std::vector<int>> ret = std::vector<std::vector<int>>(_nRows);
	for(int i = 0; i < _nRows; i++){
		ret[i] = std::vector<int>(_nCols);
	}
	//populate the array
	for(int i = 0; i < _nRows; i++){
		for(int j = 0; j < _nCols; j++){
			ret[i][j] = getElement(i,j);
		}
	}
	return ret;
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

std::vector<int> YSMF::getColElement(int j) {
	std::vector<int> ret;
	for(int i = 0; i < NNZ; i++){
		if(JA[i] == j){
			ret.push_back(A[i]);
		}
	}
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
	//it works only if number of row are lower then the number of non zero elements
	if(PP > 0.99){
		PP = 0.5;
	}
	for(int i = 1; i < _nRows; i++){
		double p = unif(rng);
		if(p > PP){
			int n = 1;
			dist = _nRows - i;
			n = (ndd / dist);
			//not too many for each row
			if( (double)n/(double)_nCols > 0.75f ){
				n -= (int)((double)_nCols * 0.1f);
			}
			ndd -= n;
			IA[i] = IA[i-1] + n;
		}
		else
			IA[i] = IA[i-1];
	}
	IA[_nRows] = NNZ;

	//Fill A
	for(int i = 0; i < NNZ; i++){
		A[i]  = (int) (unif(rng) * 9) + 1; //value in [1,9]
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
		for(int h = 0; h < tmp.size(); h++){
			JA[i++] = tmp[h];
		}
	}
}

void YSMF::addElement(int elm, int row, int col) {
	if(elm == 0) return;
	A.push_back(elm);
	JA.push_back(col);
	for(int i = row+1; i <= _nRows; i++){
		IA[i] += 1;
	}
	NNZ++;
}


void YSMF::addElementThread(int elm, int row, int col, int nElmSkip){
	if(elm == 0) return;
	//create memory for new elements
	if (nElmSkip >= A.size()) {
		A.resize(nElmSkip+1);
	}
	if (nElmSkip >= JA.size()) {
		JA.resize(nElmSkip+1);
	}
	A.insert(A.begin() + nElmSkip, elm);
	JA.insert(JA.begin() + nElmSkip, col);
	for(int i = row+1; i <= _nRows; i++){
		IA[i] += 1;
	}
	NNZ++;
}

int YSMF::getCols() {
	return _nCols;
}

int YSMF::getRows() {
	return _nRows;
}

std::vector<int> *YSMF::getA() {
	return &A;
}

std::vector<int> *YSMF::getIA() {
	return &IA;
}

std::vector<int> *YSMF::getJA() {
	return &JA;
}

void YSMF::export2CSV(char *name){
	FILE *f;
	f = fopen(name, "w+");
	std::string elm;
	for(int i = 0; i < _nRows; i++){
		for(int j = 0; j < _nCols; j++){
			elm = std::to_string(getElement(i,j)) + ((j == _nCols-1) ? "" : ",");
			fprintf(f, "%s", elm.c_str());
		}
		fprintf(f, "\n");
	}

}

int YSMF::getNNZ() {
	return NNZ;
}

std::vector<std::pair<int, int>> YSMF::getElmCoordinate() {
	return getElmCoordinate(0, NNZ);
}

std::vector<std::pair<int, int>> YSMF::getElmCoordinate(int begin, int end) {
	std::vector<std::pair<int,int>> ret;
	int eXr = 0;
	for(int i = begin; i < end; i++){
		while(IA[eXr] < (i+1)){
			eXr++;
		}
		ret.push_back(std::pair<int,int>(eXr-1, JA[i]));
	}
	return ret;
}

std::vector<std::pair<int, int>> YSMF::getElmCoordinateWithMaxLine(int begin, int end, int line) {
	std::vector<std::pair<int,int>> ret;
	int eXr = 0;
	for(int i = begin; i < end && eXr < line; i++){
		while(IA[eXr] < (i+1)){
			eXr++;
		}
		if(eXr < line) ret.push_back(std::pair<int,int>(eXr-1, JA[i]));
	}
	return ret;
}





















