#include "helperFunctions.h"
void usage(char* prog){
	std::cout << "Usage:" << std::endl;
	std::cout << "\t-h\t help"<<std::endl;
	std::cout << "\t-f\t specify data stream [mandatory]"<<std::endl;
	std::cout << "\t-l\t add loop to data [optional]"<<std::endl;
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

	std::cout << "Loop found starting at element index " << startLoop <<" with loop length "<<loopLength<<std::endl;

}


int main(int argc, char** argv){

	if(argc < 3){
		usage(argv[1]);
		return EXIT_FAILURE;
	}

	int opt;
	int loopDest = 0;
	std::string userFile;
	bool addLoop = false;
	//if help flag
	while((opt = getopt(argc, argv, "hf:l::")) != -1 ){
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
			default:
				usage(argv[1]);
				return EXIT_FAILURE;
		}
	}

	Node<int>* head = readIn(userFile);
	//printNodes(head);
	//if(addLoop) addTailLoop(head, loopDest);
	floyd(head);
	

	return EXIT_SUCCESS;
}