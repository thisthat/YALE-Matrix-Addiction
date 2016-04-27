#include "Main.hpp"
#include "YSMF.hpp"

void helper(std::string file){
    std::cout << "Usage:: " << file << " -row <n_row> -col <n_col> [-fill <\%fill>] [-t <n_thread>] [-d] [-s <ID>]" << std::endl << std::endl;
    std::cout << "Default values:" << std::endl;
    std::cout << "\tn_row : 100" << std::endl;
    std::cout << "\tn_col : 100" << std::endl;
    std::cout << "\t\%fill : 10" << std::endl;
    std::cout << "\tn_thread : 1" << std::endl;
    std::cout << "\t-d Debug disabled" << std::endl;
    std::cout << "\t-s Strategy" << std::endl;
    std::cout << "\t\t0 : Single C Matrix among thread" << std::endl;
    std::cout << "\t\t1 : Multiple C Matrix merged after" << std::endl;
}

//visible also by the threads
YSMF *a;
YSMF *b;
YSMF *c;
pthread_mutex_t lock;
pthread_mutex_t lockInfo;
int* nElmWrite;

//prototypes of the different strategies
void *th_calculate_single_c(void *arg);
void *th_calculate_multiple_c(void *arg);

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
	bool debug = false;
	int strategy = 0;
	//check other option
    int i = 1;
    while( i < argc){
		if(strcmp(argv[i],"-help") == 0 || strcmp(argv[i], "-h") == 0){
			helper(argv[0]);
			return 0;
		}
		if(strcmp(argv[i],"-d") == 0){
			debug = true;
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
		else if(strcmp(argv[i],"-s") == 0){
			if(i+1 < argc){
				strategy = atoi(argv[i+1]);
			}
			else{
				std::cerr << "Missing value for -s"<< std::endl;
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
    std::cout << "\tdebug: " << debug << std::endl;
    std::cout << "\tstrategy: " << strategy << std::endl;

	int tmpDim = std::min(n_row, n_col);
	a = new YSMF(n_row, tmpDim, fill);
	b = new YSMF(tmpDim, n_col, fill);
    c = new YSMF(n_row, n_col);

	//preparating the threads data
	struct threadData* _data = (struct threadData*) calloc(n_thread, sizeof(struct threadData));
	int batch_size = n_row / n_thread;
	for(int i = 0; i < n_thread; i++){
		_data[i].id = i;
		_data[i].start = batch_size * i;
		_data[i].end = _data[i].start + batch_size;
		_data[i].c = new YSMF(0, _data[i].end-_data[i].start);
	}
	_data[n_thread-1].end = n_row;

	nElmWrite = (int *) calloc(n_thread, sizeof(int));

	pthread_attr_t attr;
	int s = pthread_attr_init(&attr);
	if (s != 0) {
		perror("Error pthread_attr_init");
	}

	if (pthread_mutex_init(&lock, NULL) != 0) {
		perror("Error pthread_mutex_init lock");
	}
	if (pthread_mutex_init(&lockInfo, NULL) != 0) {
		perror("Error pthread_mutex_init lockInfo");
	}

	std::chrono::time_point<std::chrono::system_clock> init;
	std::chrono::time_point<std::chrono::system_clock> end;
	init = std::chrono::system_clock::now();

	//let's mul with the select strategy
	for(int i = 0; i < n_thread; i++){
		if(strategy == 0)
			s = pthread_create(&_data[i].tid, &attr, &th_calculate_single_c, (void *)&_data[i]);
		else
			s = pthread_create(&_data[i].tid, &attr, &th_calculate_multiple_c, (void *)&_data[i]);
		if (s != 0)
			perror("Error in pthread_create");
	}

	//debug info about data passed to threads
	if(debug){
		for(int i = 0; i < n_thread; i++){
			std::cout << "[Thread " << i << "]";
			std::cout << " " << _data[i].start << " ,";
			std::cout << " " << _data[i].end << " ,";
			std::cout << " " << _data[i].id << " ,";
			std::cout << " " << _data[i].tid << "";
			std::cout << std::endl;
		}
	}


	void *res;
	for(int i = 0; i < n_thread; i++){
		if (pthread_join(_data[i].tid, &res) != 0) {
			perror("Error in pthread_join");
		}
		if(strategy == 1){
			//merge results
			//TODO
		}
	}

	end = std::chrono::system_clock::now();
    std::cout << "END [" << std::chrono::duration_cast<std::chrono::milliseconds>(end - init).count() << "]" << std::endl;

	//Store result in csv file to check if the mul is correct with R
	if(debug){
		for(int i = 0; i < n_thread; i++){
			std::cout << "[Thread " << i << "] " << nElmWrite[i] << std::endl;
		}
		a->export2CSV("a.csv");
		b->export2CSV("b.csv");
		c->export2CSV("c.csv");
	}

	//free the big objects ;)
	delete a;
	delete b;
	delete c;
	return 0;
}


void *th_calculate_single_c(void *arg) {
	//preparing the data to use
	struct threadData *data = (struct threadData *)arg;
	int maxColB = b->getCols();
	std::vector<int> *aA = a->getA();
	std::vector<int> *aJA = a->getJA();
	int sum ;
	int startLine = data->start;
	int endLine = data->end;
	int NNZ = 0;
	//work only on out batch size
	for(int i = startLine; i < endLine; i++){
		for(int j = 0; j < maxColB; j++){
			sum = 0;
			for(int k = 0; k < maxColB; k++){
				sum += a->getElement(i,k) * b->getElement(k, j);
			}
			if(sum > 0) {
				// we have to store something, check where store the data
				int z = 0;
				NNZ = 0;
				pthread_mutex_lock(&lockInfo);
				nElmWrite[data->id]++;
				for(; z <= data->id; z++){
					NNZ += nElmWrite[z];
				}
				pthread_mutex_unlock(&lockInfo);
				pthread_mutex_lock(&lock);
				//write down the result
				c->addElementThread(sum, i, j, NNZ-1);
				pthread_mutex_unlock(&lock);
			}

		}
	}
	return NULL;
}

void *th_calculate_multiple_c(void *arg) {
	return NULL;
}