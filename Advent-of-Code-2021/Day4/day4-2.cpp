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

		total+=val;

	}

	bool markBoard(int r, int c){
		rows[r] += 1;
		cols[c] += 1;

		if(rows[r]>=5 || cols[c]>=5 ){
			return true;
		}

		return false;
	}

	bool check(int val){
		if(!umap.count(val)) return false;
		total -= val;
		return markBoard(umap[val][0], umap[val][1]);
	}

	void clear(){
		umap.clear();
		total = 0;
	}

	int getTotal(){
		return total;
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
	int boardsRem = boards.size();
	int lastNumber;
	bool found = false;

	for(auto num: bingoCalls){


		for(auto& board: boards) {
			if(!board->getTotal()) continue;

			if(board->check(num)){
				
				if(boardsRem > 1){
					board->clear();
					boardsRem--;
				}else{
					std::cout << "Answer: " << board->getTotal()*num <<std::endl;
					found = true;
					break;
				}
			}

		}
		if(found) break;
	}


	freeBoards(boards);

	in.close();

	return 0;
}