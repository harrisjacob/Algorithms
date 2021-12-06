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

	std::string line, fishInput;
	std::getline(in, line);
	std::stringstream ss(line);

	int fishTimer = 8;

	int fish[fishTimer+1] = {0};


	//int total = 0;
	while(ss.good()){
		std::getline(ss, fishInput, ',');
		fish[stoi(fishInput)]++;

	}

	int maxDays = 80;

	for(int i=0; i<maxDays; i++){

		int reserve = fish[0];
		for(int j=1; j<=fishTimer; j++){
			fish[j-1] = fish[j];
		}

		fish[6] += reserve;
		fish[fishTimer] = reserve;


	}

	int total=0;
	for(int i=0; i<=fishTimer; i++){
		total+= fish[i];
	}


	std::cout << "Total fish after " << maxDays << " days: " << total << std::endl;


	in.close();

	return 0;
}