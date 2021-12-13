#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
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

int dfs(std::unordered_map<std::string, std::vector<std::string>>& adj, std::unordered_map<std::string, int>& visited, std::string& current, bool smallOverride){

	if(!current.compare("end")) return 1; //Path to the end was found
	
	visited[current] += 1; //Increment the visit of the cave

	int count = 0; //Collect successful paths from all neighbors
	for(auto& node: adj[current]){
		if(!node.compare("start"))continue; //Skip researching the start node
		

		if(!isBig(node) && visited[node]){ //If the cave is small has already been viisted
			if(!smallOverride){ //If the single use override hasn't been used on this path, use it

				count += dfs(adj, visited, node, true); //Run the search without the double checking small caves

			}
			continue;
		}

		count += dfs(adj, visited, node, smallOverride); //Visit the neighbor and collect the path result
	}

	visited[current] -= 1; //Decrement the visit of the cave

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
	std::unordered_map<std::string, int> visited;


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

		visited[firstNode] = 0;
		visited[secondNode] = 0;

	}


	std::string startLocation = "start";
	std::cout << "There were " << dfs(adj, visited, startLocation, false) << " paths through the cave system" << std::endl;


	in.close();

	return 0;
}