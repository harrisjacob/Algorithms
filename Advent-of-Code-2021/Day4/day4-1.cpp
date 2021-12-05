#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>



class Board{
	int total = 0;
	int rows[5] = {0};
	int cols[5] = {0};
	std::unordered_map<int, std::vector<int>> umap;
public:

	void addNumber(int r, int c, int val){
		std::vector<int> newVector;
		newVector.push_back(r);
		newVector.push_back(c);
		umap[val] = newVector;
		//std::cout << total << " adding " << val << " for new total " << total+val << std::endl;
		total+=val;

	}

	int markBoard(int r, int c){
		rows[r] += 1;
		cols[c] += 1;

		if(rows[r]>=5 || cols[c]>=5 ){
			return total;
		}

		return -1;
	}

	int check(int val){
		if(!umap.count(val)) return -1;
		//std::cout << total << " removing " << val << " leaves " << total-val << std::endl; 
		total -= val;
		return markBoard(umap[val][0], umap[val][1]);
	}



};

void freeBoards(std::vector<Board *>& boards){
	for(auto* b: boards) delete b;
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
	std::getline(in, line);
	std::stringstream ss(line);


	std::vector<int> bingoCalls;
	std::string number;
	while(ss.good()){
		std::getline(ss,number,',');
		bingoCalls.push_back(stoi(number));
	}

	std::vector<Board *> boards;
	Board* newBoard = NULL;
	
	int readNumber;

	while(!in.eof()){
		for(int row=0; row<6; row++){
			std::getline(in, line);
			if(row == 0){
				newBoard = new Board;
				continue;
			}

			std::stringstream ss(line);

			for(int col=0; col<5; col++){
				ss >> readNumber;
				newBoard->addNumber(row-1, col, readNumber);
			}

		}
		boards.push_back(newBoard);
	}

	int total, output;

	for(auto num: bingoCalls){

		for(auto* board: boards){
			total = board->check(num);
			if(total >= 0) break;
		}

		if(total >= 0){
			std::cout << total << " - " << num << std::endl;
			output = total*num;
			break;
		}
	}


	std::cout << output << std::endl;
	freeBoards(boards);

	in.close();

	return 0;
}