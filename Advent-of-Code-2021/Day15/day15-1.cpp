#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>

std::string getLine(std::ifstream& in){
	std::string s;
	std::getline(in, s);
	if(!in.good() || s.empty()) return s;
	std::stringstream ss(s);
	std::getline(ss, s, '\r');
	if(!in.good()) return s;
	return s;
}

void printRiskMap(std::vector<std::vector<int>>& riskMap){
	for(auto& row: riskMap){
		for(auto& col: row){
			std::cout << col;
		}
		std::cout << std::endl;
	}

}

void fillDP(std::vector<std::vector<int>>& dpMap, std::vector<std::vector<int>>& riskMap, int row, int col){

	// if(row >= dpMap.size() || col >= dpMap[0].size() ) return;

	if(row==0 && col==0){
		dpMap[row][col] = 0;
		return;
	}

	int above = (row > 0) ? dpMap[row-1][col] : INT_MAX; 
	int left = (col > 0) ? dpMap[row][col-1] : INT_MAX;

	dpMap[row][col] = std::min(above, left) + riskMap[row][col];

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

	std::vector<std::vector<int>> riskMap;

	std::string line;
	while(!(line=getLine(in)).empty()){

		std::vector<int> row;

		for(auto c: line){
			row.push_back(c-'0');
		}

		riskMap.push_back(row);

	}

	int cavernSize = riskMap.size();

	std::vector<std::vector<int>> dpMap;
	for(int i=0; i<cavernSize; i++){
		std::vector<int> newDP(cavernSize, INT_MAX);
		dpMap.push_back(newDP);
	}


	for(int row=0; row<cavernSize; row++){
		for(int col=0; col<cavernSize; col++){
			fillDP(dpMap, riskMap, row, col);
		}
	}
	

	int risk = dpMap[cavernSize-1][cavernSize-1];

	std::cout << "Minimum calculated risk level: " << risk << std::endl;

	in.close();

	return 0;
}