#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void addBits(std::vector<int>& bitVal, std::string input){

	for(int i=0; i<input.length(); i++){
		bitVal[i] += (input[i]=='1') ? 1 : -1;
	}

}


int main(int argc, char** argv){

	std::string filename = argv[1];
	std::ifstream in;
	in.open(filename);
	if(!in.is_open()){
		std::cerr << "Can't open file\n";
		in.close();
		return 1;
	}

	std::string line, input;
	std::getline(in, line);
	std::istringstream iss(line.c_str());
	iss >> input;

	
	std::vector<int> bitVal(input.length(), 0);
	addBits(bitVal, input);

	while(!in.eof()){
		std::getline(in, line);
		if(line.empty()) continue;

		std::istringstream iss(line.c_str());
		iss >> input;
		addBits(bitVal, input);
	}

	int gam, eps;
	gam = eps = 0;


	for(int i=0; i<bitVal.size(); i++){
		gam = gam << 1;
		eps = eps << 1;
		
		gam |= (bitVal[i] > 0) ? 1 : 0;
		eps |= (bitVal[i] > 0) ? 0 : 1;

	}

	std::cout << "Gamma " << gam << std::endl;
	std::cout << "Epsilon " << eps << std::endl;

	std::cout << gam*eps << std::endl;
	in.close();

	return 0;
}