#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char** argv){

	std::string filename = argv[1];
	std::ifstream in;
	in.open(filename);
	if(!in.is_open()){
		std::cerr << "Can't open file\n";
		in.close();
		return 1;
	}

	int prevDepth;
	std::string line;
	int increasing = 0;
	std::getline(in, line);
	std::istringstream iss(line.c_str());
	iss >> prevDepth;



	int nextDepth;
	while(!in.eof()){
		std::getline(in, line);
		std::istringstream iss(line.c_str());
		iss >> nextDepth;

		increasing += (nextDepth > prevDepth) ? 1 : 0;
		prevDepth = nextDepth;


	}

	std::cout << increasing << std::endl;
	in.close();
	return 0;
}