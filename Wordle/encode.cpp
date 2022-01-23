#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <cstdint>

struct Letter{
	int count = 0;
	char val;
};

struct LetterComparator{
	bool operator()(Letter& l, Letter& r){
		return l.count >= r.count;
	}
};


int main(int argc, char* argv[]){

	if(argc < 2){
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
	std::priority_queue<Letter, std::vector<Letter>, LetterComparator> pq;
	for(auto& letter: letterFreq){
		pq.push(letter);
	}


	//Write the encoding key to a file
	std::ofstream outF;
	outF.open("encodingKey.txt");
	if(!outF.is_open()){
		std::cerr << "Failed to write encoding key file\n";
		outF.close();
		return 1;
	}


	//Write value to encoding key file - see README.md
	int letterTranslation[26] = {0};

	int count=0;
	while(!pq.empty()){
		char c = pq.top().val; pq.pop();
		letterTranslation[c-'a'] = 1 << count++;
		outF << c << " " << letterTranslation[c-'a'] << "\n";
	}


	outF.close();


	//Encode words and sort words - see README.md
	std::priority_queue<uint64_t> encodingPQ;	

	for(auto& word: words){
		uint64_t encoding=0x7FFC000000;

		//Encode the letters that are contained
		for(char c: word){
			encoding |= letterTranslation[c-'a'];
		}

		//Encode the word itself
		for(char c: word){
			encoding = encoding << 5;
			encoding |= c - 'a';
		}

		encodingPQ.push(encoding);

	}

	//Write encoded words to a file
	std::ofstream outWords;
	outWords.open("encodedWords.txt");
	if(!outWords.is_open()){
		std::cerr << "Failed to write encoded words file\n";
		outWords.close();
		return 1;
	}

	while(!encodingPQ.empty()){
		outWords << encodingPQ.top()<<"\n"; 
		encodingPQ.pop();
	}

	outWords.close();

	return 0;

}