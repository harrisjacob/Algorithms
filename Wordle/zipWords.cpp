#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_set>

int main(int argc, char* argv[]){

	if(argc!=3){
		std::cerr << "Two few arguments\n";
		return 1;
	}

	std::string filename = argv[1];
	std::ifstream in;
	in.open(filename);
	if(!in.is_open()){
		std::cerr << "Can't open dictionary file\n";
		in.close();
		return 1;
	}

	std::unordered_set<std::string> uset;

	int firstCount = 0;
	int secondCount = 0;

	std::string line, input;
	while(!in.eof()){
		std::getline(in, line);
		std::stringstream ss(line);
		std::getline(ss, input, '\r');
		if(!uset.count(input)){
			uset.insert(input);
			firstCount++;
		}
	}

	in.close();

	filename = argv[2];
	in.open(filename);
	if(!in.is_open()){
		std::cerr << "Can't open dictionary file\n";
		in.close();
		return 1;
	}

	while(!in.eof()){
		std::getline(in, line);
		std::stringstream ss(line);
		std::getline(ss, input, '\r');
		
		if(uset.count(input)){
			firstCount--;
		}else{
			uset.insert(input);
			secondCount++;
		}
	}

	in.close();

	std::ofstream outF;
	outF.open("dict/zippedWords.txt");
	if(!outF.is_open()){
		std::cerr << "Failed to write encoding key file\n";
		outF.close();
		return 1;
	}


	for(auto& word: uset){
		outF << word << "\n";
	}
	outF.close();

	std::cout << "\nZip Report:\n";
	std::cout << "Total words zipped: " << uset.size() << std::endl;
	std::cout << "Words found in both files: " << uset.size() - firstCount - secondCount << std::endl;
	std::cout << "Words exclusive to file 1: " << std::max(firstCount,0) << std::endl;
	std::cout << "Words exclusive to file 2: " << secondCount << std::endl;
	std::cout << std::endl;

}