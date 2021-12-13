#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


void printAdjList(std::unordered_map<std::string, std::vector<std::string>>& adj){
	for(auto it=adj.begin(); it!=adj.end(); it++){

		std::cout << it->first << ":";
		for(auto& neighbor: it->second){
			std::cout << " " << neighbor;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}



bool isBig(std::string& s) { return (s[0] <= 'Z'); }

int dfs(std::unordered_map<std::string, std::vector<std::string>>& adj, std::unordered_set<std::string>& visited, std::string& current){

	if(!current.compare("end")) return 1; //Path to the end was found
	visited.insert(current);

	int count = 0; //Collect successful paths from all neighbors
	for(auto& node: adj[current]){
		if(!node.compare("start"))continue; //Skip researching the start node
		if(!isBig(node) && visited.count(node)) continue; //If the node is small and already visited, don't revisit
		count += dfs(adj, visited, node); //Visit the neighbor and collect the path result
	}

	visited.erase(current);
	return count;

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
	std::string firstNode, secondNode;

	std::unordered_map<std::string, std::vector<std::string>> adj;
	std::unordered_set<std::string> visited;


	std::stringstream ss;


	while(std::getline(in, line)){

		std::stringstream ss(line);
		ss >> input;
		std::stringstream sp(input);

		//Read nodes
		std::getline(sp, firstNode, '-');
		std::getline(sp, secondNode, '-');


		adj[firstNode].push_back(secondNode);
		adj[secondNode].push_back(firstNode);

	}

	std::string startLocation = "start";
	std::cout << "There were " << dfs(adj, visited, startLocation) << " paths through the cave system" << std::endl;


	in.close();

	return 0;
}