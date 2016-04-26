#include "Main.hpp"
#include "YSMF.hpp"

void helper(std::string file){
    std::cout << "Usage:: " << file << " -row <n_row> -col <n_col> [-fill <\%fill>] [-t <n_thread>]" << std::endl << std::endl;
    std::cout << "Default values:" << std::endl;
    std::cout << "\tn_row : 100" << std::endl;
    std::cout << "\tn_col : 100" << std::endl;
    std::cout << "\t\%fill : 10" << std::endl;
    std::cout << "\tn_thread : 1" << std::endl;
}

//visible also by the threads
YSMF *a;
YSMF *b;
YSMF *c;
pthread_mutex_t lock;

void *th_calculate(void *arg);

int main(int argc, char** argv)
{
	if (argc < 5) {
        helper(argv[0]);
        return 0;
    }
    //default value
    int n_col = 100;
    int n_row = 100;
    double fill  = 0.1;
    int n_thread = 1;
	//check other option
    int i = 1;
    while( i < argc){
        if(strcmp(argv[i],"-help") == 0 || strcmp(argv[i], "-h") == 0){
			helper(argv[0]);
			return 0;
        }
        if(strcmp(argv[i],"-row") == 0){
            if(i+1 < argc){
                n_row = atoi(argv[i+1]);
            }
            else{
                std::cerr << "Missing value for -row"<< std::endl;
                helper(argv[0]);
                return 1;
            }
        }
        else if(strcmp(argv[i],"-col") == 0){
            if(i+1 < argc){
                n_col = atoi(argv[i+1]);
            }
            else{
                std::cerr << "Missing value for -col"<< std::endl;
                helper(argv[0]);
                return 1;
            }
        }
        else if(strcmp(argv[i],"-fill") == 0){
            if(i+1 < argc){
                fill = (double)atoi(argv[i+1]) / 100.0f;
            }
            else{
                std::cerr << "Missing value for -fill"<< std::endl;
                helper(argv[0]);
                return 1;
            }
        }
        else if(strcmp(argv[i],"-t") == 0){
            if(i+1 < argc){
                n_thread = atoi(argv[i+1]);
            }
            else{
                std::cerr << "Missing value for -t"<< std::endl;
                helper(argv[0]);
                return 1;
            }
        }

        i++;
    }
    //Print options that will use
    std::cout << "Selected values:" << std::endl;
    std::cout << "\tn_row: " << n_row << std::endl;
    std::cout << "\tn_col: " << n_col << std::endl;
    std::cout << "\t\%fill: " << fill << std::endl;
    std::cout << "\tn_thread: " << n_thread << std::endl;

	int tmpDim = std::min(n_row, n_col);
	a = new YSMF(n_row, tmpDim, fill);
	b = new YSMF(tmpDim, n_col, fill);
    c = new YSMF(n_row, n_col);

	//preparating the threads
	struct threadData* _data = (struct threadData*) calloc(n_thread, sizeof(struct threadData));
	int batch_size = n_row / n_thread;
	for(int i = 0; i < n_thread; i++){
		_data[i].start = batch_size * i;
		_data[i].end = _data[i].start + batch_size;
	}
	_data[n_thread-1].end = n_row;
	pthread_attr_t attr;
	int s = pthread_attr_init(&attr);
	if (s != 0) {
		perror("Error pthread_attr_init");
	}

	if (pthread_mutex_init(&lock, NULL) != 0) {
		perror("Error pthread_mutex_init");
	}

	std::chrono::time_point<std::chrono::system_clock> init;
	std::chrono::time_point<std::chrono::system_clock> end;
	init = std::chrono::system_clock::now();

	//let's mul
	for(int i = 0; i < n_thread; i++){
		s = pthread_create(&_data[i].id, &attr,
					   &th_calculate, (void *)&_data[i]);
		if (s != 0)
			perror("Error in pthread_create");
	}
	void *res;
	for(int i = 0; i < n_thread; i++){
		if (pthread_join(_data[i].id, &res) != 0) {
			perror("Error in pthread_join");
		}
	}

	end = std::chrono::system_clock::now();
    std::cout << "END :D [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - init).count() << "]" << std::endl;

	//Store result
	a->export2CSV("a.csv");
	b->export2CSV("b.csv");
	c->export2CSV("c.csv");

	//a->print();
	//b->print();
	//c->print();
	delete a;
	delete b;
	delete c;
	return 0;
}


void *th_calculate(void *arg) {
	//pthread_mutex_lock(&lock);
	struct threadData *data = (struct threadData *)arg;
	int maxColB = b->getCols();
	std::vector<int> *aA = a->getA();
	std::vector<int> *aJA = a->getJA();
	int sum ;
	int startLine = data->start;
	int endLine = data->end;
	for(int i = startLine; i < endLine; i++){
		for(int j = 0; j < maxColB; j++){
			sum = 0;
			for(int k = 0; k < maxColB; k++){
				sum += a->getElement(i,k) * b->getElement(k, j);
			}
			pthread_mutex_lock(&lock);
			c->addElement(sum, i, j);
			pthread_mutex_unlock(&lock);
		}
	}
	//return matrix;
	//pthread_mutex_unlock(&lock);
	return NULL;
}