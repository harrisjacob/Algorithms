#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>


std::string getLine(std::ifstream& in){
	std::string s;
	std::getline(in, s);
	if(!in.good() || s.empty()) return s;
	std::stringstream ss(s);
	std::getline(ss, s, '\r');
	if(!in.good()) return s;
	return s;
}

bool inRange(int first, int second, int current){
	return (std::min(first, second) <= current && std::max(first, second) >= current);
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

	std::string line = getLine(in);

	if(line.empty()){
		std::cerr << "Error reading the target area" << std::endl;
		in.close();
		return 1;
	}

	std::stringstream ss(line);
	std::string input;
	std::getline(ss, input, ' '); //target
	std::getline(ss, input, ' '); //area

	int split;
	int x1, x2, y1, y2;


	std::getline(ss, input, ','); //xGroup
	split = input.find('.');
	x1 = stoi(input.substr(2, split-2));
	x2 = stoi(input.substr(split+2));


	std::getline(ss, input); //yGroup
	split = input.find('.');
	y1 = stoi(input.substr(3, split-3));
	y2 = stoi(input.substr(split+2));


	

	in.close();

	return 0;
}