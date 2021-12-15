#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <climits>

std::string getLine(std::ifstream& in){
	std::string s;
	std::getline(in, s);
	if(!in.good() || s.empty()) return s;
	std::stringstream ss(s);
	std::getline(ss, s, '\r');
	if(!in.good()) return s;
	return s;
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

	std::unordered_map<std::string, char> umap;

	while(!(line=getLine(in)).empty()){

		std::stringstream ss(line);
		ss >> pre >> arrow >> post;

		umap[pre] = post[0];

	}


	for(int steps=0; steps<maxSteps; steps++){

		std::string newWord = std::string();
		for(int i=0; i<word.length()-1; i++){
			newWord += word[i];
			newWord += umap[word.substr(i, 2)];
		}

		newWord += word[word.length()-1];
		word = newWord;

	}

	int freq[26] = {0};

	for(char c: word){
		freq[c-'A'] ++;
	}


	int minInd, maxInd;
	maxInd = 0;
	minInd = 0;
	int freqMin = INT_MAX;


	for(int i=0; i<26; i++){

		if(freq[i] && freq[i] < freqMin){
			minInd = i;
			freqMin = freq[minInd];
		}
		maxInd = (freq[maxInd] > freq[i]) ? maxInd : i;

	}

	std::cout << "Max: " << freq[maxInd] << "\t" << "Min: " << freq[minInd] << std::endl;
	std::cout << "Difference is: " << freq[maxInd] - freq[minInd] << std::endl;


	in.close();

	return 0;
}