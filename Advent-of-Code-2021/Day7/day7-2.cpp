#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>


int main(int argc, char** argv){

	std::string filename = argv[1];
	std::ifstream in;
	in.open(filename);
	if(!in.is_open()){
		std::cerr << "Can't open file\n";
		in.close();
		return 1;
	}


	std::string number;
	std::vector<int> trial;
	int total = 0;
	int newNum, count=0;
		
	while(!in.eof()){
		std::getline(in, number, ',');
		newNum = stoi(number);
		trial.push_back(newNum);
		total += newNum;
		count++;

	}

	float avg = total*1./count;

	int lowerResult = avg;
	int upperResult = lowerResult+1;

	// float diff = avg - trunc;
	// int lowerResult, upperResult;

	// result = (diff > 0.5) ? trunc + 1 : trunc;

	// std::cout << diff << std::endl;

	int lowerUnitTotal = 0;
	for(int a: trial){
		
		for(int i=1; i<= std::max(a-lowerResult, lowerResult-a); i++){
			lowerUnitTotal += i;
		}
	}


	int upperUnitTotal = 0;
	for(int a: trial){
		
		for(int i=1; i<= std::max(a-upperResult, upperResult-a); i++){
			upperUnitTotal += i;
		}
	}



	std::cout << "Minimal fuel found at location " << ((lowerUnitTotal < upperUnitTotal) ? lowerResult : upperResult) << " with a total of " << std::min(lowerUnitTotal, upperUnitTotal) << " units." << std::endl;


	in.close();

	return 0;
}