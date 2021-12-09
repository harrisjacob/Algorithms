#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


int main(int argc, char** argv){

	std::string filename = argv[1];
	std::ifstream in;
	in.open(filename);
	if(!in.is_open()){
		std::cerr << "Can't open file\n";
		in.close();
		return 1;
	}

	std::string line;
	std::vector<std::vector<int>> numbers;
	char readNumber;

	while(!in.eof()){
		std::getline(in, line);
		if(line.empty()) continue;
		std::vector<int> row;

		//Get rid of carriage return character
		std::string trim_line;
		std::stringstream ss(line);
		ss >> trim_line;

		for(char c : trim_line){
			row.push_back(c-'0');
		}

		numbers.push_back(row);
	}

	int total = 0;

	for(int row=0; row<numbers.size(); row++){
		for(int col=0; col<numbers[0].size(); col++){
			if(row>0 && numbers[row-1][col] <= numbers[row][col]) continue;
			if(row+1<numbers.size() && numbers[row+1][col] <= numbers[row][col])continue;
			if(col>0 && numbers[row][col-1] <= numbers[row][col]) continue;
			if(col+1<numbers[0].size() && numbers[row][col+1] <= numbers[row][col]) continue;

			total += numbers[row][col] + 1;
		}
	}

	std::cout << "Total: " << total << std::endl;


	in.close();

	return 0;
}