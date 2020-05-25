#include <algorithm>
#include "helperFunctions.h"


void usage(char* prog){
	std::cout << "Usage:" << std::endl;
	std::cout << "\t-h\t help"<<std::endl;
	std::cout << "\t-f [file]\t specify data stream [mandatory]"<<std::endl;
	std::cout << "\t-l[loop index]\t add loop to data [optional] (note: no space)"<<std::endl;
	std::cout << "\t-a [algorithm]\t specify algorithm (Floyd/Brent) [optional]"<<std::endl;
}

void floyd(Node<int>* head){

	Node<int> *tortise, *hare;
	int startLoop=0, loopLength = 1;

	tortise = head->getNext();
	hare = head->getNext()->getNext();

	while(tortise->getData() != hare->getData()){
		tortise = tortise->getNext();
		hare = hare->getNext()->getNext();
	}

	tortise = head;
	while(tortise->getData() != hare->getData()){
		tortise = tortise->getNext();
		hare = hare->getNext();
		startLoop++;
	}

	hare = tortise->getNext();
	while(tortise->getData() != hare->getData()){
		hare=hare->getNext();
		loopLength++;
	}

	std::cout << "Floyd's algorithm found a loop starting at element index " << startLoop <<" with loop length "<<loopLength<<"."<<std::endl;

}

void brent(Node<int>* head){
	int power = 0, loopLength = 0, startLoop = 0;
	Node<int> *tortise, *hare;

	tortise = head;
	hare = head->getNext();

	while(tortise->getData() != hare->getData()){
		if(power == loopLength){
			tortise = hare;
			power *=2;
			loopLength = 0;
		}
		hare = hare->getNext();
		loopLength++;
	}

	tortise = hare = head;
	for(int i = 0; i < loopLength; i++){
		hare = hare->getNext();
	}

	while(tortise->getData() != hare->getData()){
		tortise = tortise->getNext();
		hare = hare->getNext();
		startLoop++;
	}

	std::cout << "Brent's algorithm found a loop starting at element index " << startLoop <<" with loop length "<<loopLength<<"."<<std::endl;

}


int main(int argc, char** argv){

	if(argc < 3){
		usage(argv[1]);
		return EXIT_FAILURE;
	}

	int opt;
	int loopDest = 0;
	std::string userFile, algorithm = "floyd";
	bool addLoop = false;
	//if help flag
	while((opt = getopt(argc, argv, "hf:l::a:")) != -1 ){
		switch(opt){
			case 'h':
				usage(argv[1]);
				return 0;
			case 'f':
				userFile = optarg;
				break;
			case 'l':
				addLoop = true;
				if(optarg){
					loopDest = std::stoi(optarg);
				}
				break;
			case 'a':
				algorithm = optarg;
				break;
			default:
				usage(argv[1]);
				return EXIT_FAILURE;
		}
	}

	Node<int>* head = readIn(userFile);
	
	std::for_each(algorithm.begin(), algorithm.end(), [](char &c){
		c = tolower(c);
	});

	//printNodes(head);
	if(addLoop) addTailLoop(head, loopDest);
	if(algorithm.compare("floyd") == 0){
		floyd(head);
	}else if(algorithm.compare("brent") == 0){
		brent(head);
	}else{
		std::cout<<"Error: Unknown algorithm specified"<<std::endl;
		usage(argv[1]);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}