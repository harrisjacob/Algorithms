#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>

class Entry{

public:

	Entry(std::string& line){
		for(char c: line){
			switch(c){
				case'[':
					brackets.push_back(1);
					break;
				case ']':
					brackets.push_back(-1);
					break;
				case ',':
					brackets.push_back(2);
					break;
				default:
					brackets.push_back(3);
					values.push_back(c-'0');
			}
		}
	}

	void print(){

	}


}

std::string getLine(std::ifstream& in){
	std::string s;
	std::getline(in, s);
	if(!in.good() || s.empty()) return s;
	std::stringstream ss(s);
	std::getline(ss, s, '\r');
	if(!in.good()) return s;
	return s;
}


void freeEntries(std::vector<Entry*>& entries){
	for(auto& entry: entries){
		delete entry;
	}
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

	std::vector<Entry*> entries;

	while(!((line=getLine(in)).empty())){

		Entry oneEntry = new Entry(line);
		entries.push_back(oneEntry);
		oneEntry->print();
	
	}

	freeEntries(entries);

	
	


	in.close();

	return 0;
}