#include <vector>

class YSMF {
	public:
		YSMF(int nRows, int nCols, int fillPerc);
		~YSMF();
		void print(); //Debug Purpose
	private:
		int _nRows, _nCols, _fill, NNZ;
        std::vector<int> A;
        std::vector<int> IA;
        std::vector<int> JA;
		void fillMatrix();
};

