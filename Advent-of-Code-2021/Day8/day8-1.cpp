#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


struct Word{

	bool contains[7];
	Word* next;

};



int main(int argc, char** argv){

	std::string filename = argv[1];
	std::ifstream in;
	in.open(filename);
	if(!in.is_open()){
		std::cerr << "Can't open file\n";
		in.close();
		return 1;
	}


	std::string line, seg;
	char letters[10];


//	int segSz;

	while(!in.eof()){
		std::getline(in, line);
		std::stringstream ss(line.c_str());

		Word* words[10] = {0};

		for(int i=0; i<10; i++){
			ss >> seg;
			std::cout << seg << std::endl;
		}




		// for(int i=0; i<4; i++){
		// 	ss >> seg;
		// 	segSz = seg.size();

		// 	if(segSz == 2 || segSz == 4 || segSz == 3 || segSz == 7){
		// 		uniqCount++;
		// 	}
		// }

	}

//	std::cout << "1, 4, 7, and 8 were found " << uniqCount << " times" << std::endl;



	in.close();

	return 0;
}