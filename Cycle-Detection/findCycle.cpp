#include "helperFunctions.h"

void usage(char* prog){
	std::cout << "Usage:" << std::endl;
	std::cout << "\t-h\t help"<<std::endl;
	std::cout << "\t-f\t specify data stream [mandatory]"<<std::endl;
	std::cout << "\t-l\t add loop to data [optional]"<<std::endl;
}

int main(int argc, char** argv){

	if(argc < 3){
		usage(argv[1]);
		return EXIT_FAILURE;
	}

	int opt;
	std::string userFile;
	bool addLoop = false;
	//if help flag
	while((opt = getopt(argc, argv, "hf:l")) != -1 ){
		switch(opt){
			case 'h':
				usage(argv[1]);
				return 0;
			case 'f':
				userFile = optarg;
				break;
			case 'l':
				addLoop = true;
				break;
			default:
				usage(argv[1]);
				return EXIT_FAILURE;
		}
	}

	Node<int>* head = readIn(userFile);
	printNodes(head);

	return EXIT_SUCCESS;
}