#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>

struct Letter{
	int count = 0;
	char val;
};

struct Comparator{
	bool operator()(Letter& l, Letter& r){
		return l.count >= r.count;
	}
};

int main(int argc, char* argv[]){

	if(argc < 1){
		std::cerr << "Encoding requires a newline separated dictionary\n";
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

	std::vector<std::string> words;

	//Open the dictionary file
	std::string line, input;
	while(!in.eof()){
		std::getline(in, line);
		std::stringstream ss(line);
		std::getline(ss, input, '\r');
		words.push_back(input);
	}

	//Initialize the frequency of each letter
	std::vector<Letter> letterFreq;
	for(int i=0; i<26; i++){
		Letter newLetter;
		newLetter.val = 'a'+i;
		letterFreq.push_back(newLetter);
	}

	//Count the frequency of each letter
	for(auto& word: words){
		for(char c: word){
			letterFreq[c-'a'].count++;
		}
	}

	//Sort the letters by their frequency
	std::priority_queue<Letter, std::vector<Letter>, Comparator> pq;
	for(auto& letter: letterFreq){
		pq.push(letter);
	}

	//Assign a value according to 2^(26-k) where k is the rank (k=0 is the most popular letter, k=25 is the least popular)
	std::unordered_map<char, int> letterTranslation;
	int count=0;
	while(!pq.empty()){
		letterTranslation[pq.top().val] = 1 << (count++);
		pq.pop();
	}

	//Write the encoding key to a file
	std::ofstream outF;
	outF.open("encodingKey.txt");
	if(!outF.is_open()){
		std::cerr << "Failed to write encoding key file\n";
		outF.close();
		return 1;
	}

	for(auto& item: letterTranslation){
		outF << item.first << " " << item.second << "\n";
	}

	outF.close();


	//Write encoded words to a file
	std::ofstream outWords;
	outWords.open("encodedWords.txt");
	if(!outWords.is_open()){
		std::cerr << "Failed to write encoded words file\n";
		outWords.close();
		return 1;
	}

	for(auto& word: words){
		int encoding=0;
		for(char c: word){
			encoding |= letterTranslation[c];
		}

		outWords << word << " " << encoding << "\n";
	}

	outWords.close();



	return 0;

}