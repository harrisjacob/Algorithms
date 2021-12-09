#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>


int dfs(std::vector<std::vector<int>>& numbers, int r, int c){

	if(		r < 0 || r >= numbers.size() ||
			c < 0 || c >= numbers[0].size() ||
			numbers[r][c] == 9
	) return 0;

	numbers[r][c] = 9;
	int left = dfs(numbers, r, c-1);
	int right = dfs(numbers, r, c+1);
	int up = dfs(numbers, r-1, c);
	int down = dfs(numbers, r+1, c);

	return left+right+up+down+1;

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

	int result;

	std::priority_queue<int> pq;

	for(int row=0; row<numbers.size(); row++){
		for(int col=0; col<numbers[0].size(); col++){
			if(numbers[row][col] == 9) continue;
			pq.push(dfs(numbers, row, col));
		}
	}

	int threeBig=1;


	for(int i=0; i<3; i++){
		if(pq.empty()) break;
		threeBig *= pq.top();
		pq.pop();
	}

	 std::cout << "Three Largest Basins: " << threeBig << std::endl;


	in.close();

	return 0;
}