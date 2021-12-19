#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
#include <unordered_map>
#include <unordered_set>
#include <queue>

std::string getLine(std::ifstream& in){
	std::string s;
	std::getline(in, s);
	if(!in.good() || s.empty()) return s;
	std::stringstream ss(s);
	std::getline(ss, s, '\r');
	if(!in.good()) return s;
	return s;
}

void printRiskMap(std::vector<std::vector<int>>& riskMap, int cellSz){
	
	for(int row=0; row<riskMap.size(); row++){
		if(row!=0 && !(row%cellSz)){
			for(int border=0; border<riskMap.size()+4; border++) std::cout<<"=";
			std::cout<< std::endl;
		}

		for(int col=0; col<riskMap[0].size(); col++){
			if(col!=0 && !(col%cellSz)) std::cout<< "|";
			std::cout << riskMap[row][col];
		}

		std::cout << std::endl;

	}

}


bool checkVisited(std::unordered_map<int, std::unordered_set<int>>& visited, int r, int c){

	return (visited.count(r) && visited[r].count(c));
}


void printVisited(std::unordered_map<int, std::unordered_set<int>>& visited, std::vector<std::vector<int>>& riskMap, int cellSz){
	
	for(int row=0; row<riskMap.size(); row++){
		if(row!=0 && !(row%cellSz)){
			for(int border=0; border<riskMap.size()+4; border++) std::cout<<"=";
			std::cout<< std::endl;
		}

		for(int col=0; col<riskMap[0].size(); col++){
			if(col!=0 && !(col%cellSz)) std::cout<< "|";

			std::cout << checkVisited(visited, row, col);
		}

		std::cout << std::endl;

	}

}




void expandCol(std::vector<int>& row, int origSz, int length){

	for(int expand=0; expand<length; expand++){

		for(int i=0; i<origSz; i++){

			int newNum = row[i] + expand + 1;
			newNum = (newNum > 9) ? newNum - 9 : newNum;

			row.push_back(newNum);

		}

	}

}


void expandRow(std::vector<std::vector<int>>& riskMap, int origSz, int length){

	for(int expand=0; expand<length; expand++){

		for(int row=0; row<origSz; row++){

			std::vector<int> newRow;

			for(int col=0; col<riskMap[row].size(); col++){
				int newNum = riskMap[row][col] + expand + 1;
				newNum = (newNum > 9) ? newNum - 9 : newNum;
				newRow.push_back(newNum);
			}

			riskMap.push_back(newRow);

		}

	}

}




struct Node{
	int row;
	int col;
	int value;		

	Node(int r, int c, int v): row(r), col(c), value(v){}
};

struct Comparator{
	bool operator()(Node const& left, Node const& right) const {
		return left.value > right.value;
	}
};


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
	int origSz;

	std::string line;
	while(!(line=getLine(in)).empty()){

		std::vector<int> row;

		for(auto c: line){
			row.push_back(c-'0');
		}

		origSz = row.size();
		expandCol(row, origSz, 4);
		riskMap.push_back(row);

	}


	expandRow(riskMap, riskMap.size(), 4);

	//Create table of cost to each location
	std::vector<std::vector<int>> values;
	for(auto& row: riskMap){
		std::vector<int> valueRow(row.size(), INT_MAX);
		values.push_back(valueRow);
	}	

	//Map of cells already visited
	std::unordered_map<int, std::unordered_set<int>> visited;
	
	Node n(0,0,0);
	values[0][0] = 0;

	std::priority_queue<Node, std::vector<Node>, Comparator> pq;
	pq.push(n);

	while(!pq.empty()){

		Node current = pq.top(); pq.pop();
		int row = current.row;
		int col = current.col;


		if(!checkVisited(visited, row, col)){

			values[row][col] = std::min(values[row][col], current.value);

			if(row > 0 && !checkVisited(visited, row-1, col)){
				pq.push({row-1, col, riskMap[row-1][col] + values[row][col]});
			}

			if(col > 0 && !checkVisited(visited, row, col-1)){
				pq.push({row, col-1, riskMap[row][col-1] + values[row][col]});
			}

			if(row < riskMap.size()-1 && !checkVisited(visited, row+1, col)){
				pq.push({row+1, col, riskMap[row+1][col] + values[row][col]});
			}

			if(col < riskMap[0].size()-1 && !checkVisited(visited, row, col+1)){
				pq.push({row,col+1, riskMap[row][col+1] + values[row][col]});
			}

			visited[row].insert(col);

		}
	}


	int risk = values[values.size()-1][values[0].size()-1];

	std::cout << "Minimum calculated risk level: " << risk << std::endl;

	in.close();

	return 0;
}