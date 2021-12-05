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

	int increasing = 0;

	int aDepth, bDepth, cDepth;
	std::string line;
	
	std::getline(in, line);
	std::istringstream iss;
	iss.str(line.c_str());
	iss >> aDepth;
	iss.clear();

	std::getline(in, line);
	iss.str(line.c_str());
	iss >> bDepth;
	iss.clear();

	std::getline(in, line);
	iss.str(line.c_str());
	iss >> cDepth;
	iss.clear();

	long prevDepth = aDepth + bDepth + cDepth;
	// std::cout << prevDepth << " original" << std::endl;

	long nextDepth;
	int dDepth;
	while(!in.eof()){
		std::getline(in, line);
		std::istringstream iss(line.c_str());
		iss >> dDepth;

		nextDepth = prevDepth - aDepth + dDepth;
		// std::cout << nextDepth;

		if(nextDepth > prevDepth){
		//	std::cout << " increasing" << std::endl;
			increasing++;
		}
		// }else if(nextDepth < prevDepth) {
		// 	std::cout << " drecreasing" << std::endl;
		// }else{
		// 	std::cout << " same" << std::endl;
		// }

		prevDepth = nextDepth;

		aDepth = bDepth;
		bDepth = cDepth;
		cDepth = dDepth;


	}

	std::cout << increasing << std::endl;
	in.close();
	return 0;
}