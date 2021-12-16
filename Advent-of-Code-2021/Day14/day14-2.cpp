#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <climits>
#include <vector>

std::string getLine(std::ifstream& in){
	std::string s;
	std::getline(in, s);
	if(!in.good() || s.empty()) return s;
	std::stringstream ss(s);
	std::getline(ss, s, '\r');
	if(!in.good()) return s;
	return s;
}


void printTable(std::unordered_map<std::string, std::vector<int>>& t){

	for(auto i: t){
		std::cout << i.first << ":";
		for(auto j: i.second){
			std::cout << " " << j;
		} 
		std::cout << std::endl;
	}

}


void printCharTable(std::unordered_map<char, long>& charCount){
	for(auto& c: charCount){
		std::cout << c.first << ": " << c.second << std::endl;
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

	int maxSteps = 1;

	if(argc == 3){
		maxSteps = std::stoi(argv[2]);
	}

	std::string word = getLine(in);

	//Discard blank line
	getLine(in);

	std::string line;
	std::string pre, arrow, post;

	std::unordered_map<std::string, std::vector<std::string>> rules;
	std::unordered_map<std::string, std::vector<long>> tokenCount;
	std::unordered_map<char, long> charCount;
	std::unordered_map<std::string, char> charRules;

	while(!(line=getLine(in)).empty()){

		std::stringstream ss(line);
		ss >> pre >> arrow >> post;

		//Create tokens that are created as a result
		std::string leftToken = std::string() + pre[0] + post[0];
		std::string rightToken = std::string() + post[0] + pre[1];

		rules[pre].push_back(leftToken);
		rules[pre].push_back(rightToken);
		tokenCount[pre].resize(maxSteps+1, 0);

		charRules[pre] = post[0];

		charCount[pre[0]] = 0;
		charCount[pre[1]] = 0;

	}

	//Set initial state of table
	for(int i=0; i<word.size()-1; i++){
		tokenCount[word.substr(i,2)][0]++;
		charCount[word[i]]++;
	}


	charCount[word[word.size()-1]]++;

	for(int i=0; i<maxSteps; i++){
		
		//Iterate through the tokens
		for(auto& tokenItem : tokenCount){

			charCount[charRules[tokenItem.first]] += tokenItem.second[i];

			//Look up the tokens produced by the current token
			for(auto& rule: rules[tokenItem.first]){		
				tokenCount[rule][i+1] += tokenItem.second[i];
			}

		}


	}

	//Get max and min
	long valMin = LONG_MAX;
	long valMax = LONG_MIN;

	for(auto& charFreq : charCount){

		valMin = std::min(valMin, charFreq.second);
		valMax = std::max(valMax, charFreq.second);

	}

	std::cout << "The max is " << valMax << " and the min is " << valMin << std::endl;
	std::cout << "The difference is " << valMax - valMin << std::endl;

	in.close();

	return 0;
}