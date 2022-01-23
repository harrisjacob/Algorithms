#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>

struct Word{
	uint64_t data;
	Word* next = NULL;
};


void freeWords(Word* current){
	if(!current) return;
	freeWords(current->next);
	delete current;
}


std::string decodeWord(uint64_t encoded){
	uint64_t letterMask = 0x1F; //Selects lowest 5 bits
	std::string word = "";
	for(int i=0; i<5; i++){
		word = (char)('a'+(encoded&letterMask))+word;
		encoded = encoded >> 5;
	}

	return word;
}

bool contains(uint64_t encoded, uint64_t check){
	return (encoded&check == check);
}

bool doesNotContain(uint64_t encoded, uint64_t check){
	return !(encoded&check);
}

bool hasExact(uint64_t encoded, uint64_t check, uint64_t mask){
	uint64_t maskedEncoded = encoded&mask;
	return (maskedEncoded&check) == (maskedEncoded|check);
}



int main(int argc, char* argv[]){

	if(argc < 3){
		std::cerr << "Usage:\n\t./wordleSolver {encodedWords} {encodingKey}\n";
		return 1;
	}


	//Set up linked list
	Word* head = new Word;
	Word* tail = new Word;
	head->next = tail;




	//Read in encription key
	std::string filename = argv[2];
	std::ifstream in;


	in.open(filename);
	if(!in.is_open()){
		std::cerr << "Can't open encoded key\n";
		in.close();
		return 1;
	}


	uint64_t translate[26] = {0};

	std::string line;
	int letter;
	uint64_t value;
	while(!in.eof()){
		std::getline(in, line);
		std::stringstream ss(line);
		ss >> letter >> value;
		translate[letter-'a'] = value<<25;
	}

	in.close(); 



	//Read in encoded words
	filename = argv[1];
	in.open(filename);
	if(!in.is_open()){
		std::cerr << "Can't open encoded words\n";
		in.close();
		return 1;
	}

	//Read in words and their score
	uint64_t data;

	Word* current = head;

	while(!in.eof()){
		std::getline(in, line);
		std::stringstream ss(line);
		ss >> data;

		Word* newWord = new Word;
		newWord->data = data;
		newWord->next = current->next;

		current->next = newWord;
		current = current->next;
	}

	in.close();

	//Set up search pointers
	Word* prev = head;
	current = head->next;

	

	freeWords(head);

	return 0;
}