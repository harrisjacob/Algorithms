#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <queue>
#include <unordered_set>

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
	return ((encoded&check) == check);
}

bool doesNotContain(uint64_t encoded, uint64_t check){
	return !(encoded&check);
}

bool hasExact(uint64_t encoded, uint64_t check, uint64_t mask){
	uint64_t maskedEncoded = encoded&mask;
	return (maskedEncoded&check) == (maskedEncoded|check);
}

bool keepWord(uint64_t encoded, uint64_t canHave, uint64_t cannotHave, uint64_t exactly, uint64_t exactMask){
	return contains(encoded, canHave) && doesNotContain(encoded, cannotHave) && hasExact(encoded, exactly, exactMask);
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
	char letter;
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

	
	int correctLetters = 0;

	uint64_t canHave = 0;
	uint64_t cannotHave = 0;
	uint64_t exactly = 0;
	uint64_t exactlyMask = 0;

	int suggestion;
	int suggestLimit = 5;

	std::unordered_set<char> sepChars; //Separates the characters that are in an out of the set


	while(correctLetters < 5){

		std::cout << "Can have: " << canHave << std::endl;
		std::cout << "Cannot have: " << cannotHave << std::endl;
		std::cout << "Exactly: " << exactly << std::endl;
		std::cout << "Exactly mask: " << exactlyMask << std::endl;

		suggestion = 0;

		prev = head;
		current = head->next;

		std::cout << "Suggested Guesses:\n";
		while(current!=tail && suggestion < suggestLimit){

			if(keepWord(current->data, canHave, cannotHave, exactly, exactlyMask)){
				suggestion++;
				std::cout << " " << decodeWord(current->data) << std::endl;
			}else{
				prev->next = current->next;
				delete current;
				current = prev->next;
				continue;
			}
			prev = current;
			current = current->next;
		
		}

		if(suggestion == 0){
			std::cout << "No suggestions remaining\n" << std::endl;
			freeWords(head);
			return 0;
		}

		//Get user guess
		bool validGuess = false;
		while(!validGuess){


			std::cout << "\nType in what guess was submitted. 5 characters in total. Press enter when done.\n\n";
			std::string guess;
			std::getline(std::cin, guess);
			std::cout << std::endl;

			if(guess.size()!=5){
				std::cout << "Guess was not length 5.  Try again.\n";
				continue;
			}

			validGuess = true;

			sepChars.clear();

			for(int i=0; i<(int)guess.size(); i++){
				if(guess[i] >= 'a' && guess[i]<= 'z'){
					sepChars.insert(guess[i]);
				}else{
					std::cout << "Guess contained an invalid character. Try again.\n";
					validGuess = false;
					break;
				}
			}	

		}


		//Get correct positions
		bool incorrectInput = true;
		while(incorrectInput){

			correctLetters = 0;
			std::queue<char> includedChars;

			incorrectInput = false;

			std::cout << "\nType the letters of your guess that were in the correct position\n";
			std::cout << "For every other position, type a star (*).  5 characters total. Press enter when done.\n\n";
			
			std::string correctInput;
			std::getline(std::cin, correctInput);
			std::cout << std::endl;

			uint64_t update_exactly = 0;
			uint64_t update_exactlyMask = 0;


			if(correctInput.size()!=5){
				std::cout << "Input was not five characters in length. Please try again.\n";
				incorrectInput = true;
				continue;
			}

			for(int i=0;i<5;i++){
				if(correctInput[i] == '*'){
					
					update_exactly = update_exactly << 5;
					update_exactlyMask = update_exactlyMask << 5;

				}else if(correctInput[i] >= 'a' && correctInput[i]<='z'){

					correctLetters++;
					includedChars.push(correctInput[i]);
					update_exactly = update_exactly << 5;
					update_exactlyMask = update_exactlyMask << 5;
					update_exactly = update_exactly | (correctInput[i]-'a');
					update_exactlyMask = update_exactlyMask | 0x1F;

			
				}else{
					std::cout << "Unknown character given. Please try again.\n";
					incorrectInput = true;
					break;
				}
			}

			if(!incorrectInput){
				exactly = update_exactly;
				exactlyMask = update_exactlyMask;

				while(!includedChars.empty()){
					canHave |= translate[includedChars.front()-'a'];
					sepChars.erase(includedChars.front());
					includedChars.pop();
				}
			}
		}


		//Get known letters, wrong position
		std::cout << "\nType the letters that were in the word, but not in the correct position.\n";
		std::cout << "It is not necessary to include letters in the correct position. Input should be 0-5 characters. Press enter when done.\n\n";

		std::string moveLetters;
		std::getline(std::cin, moveLetters);
		std::cout << std::endl;

		for(int i=0; i<(int)moveLetters.size() && i<5; i++){
			if(moveLetters[i] >= 'a' && moveLetters[i]<= 'z'){
				canHave |= translate[moveLetters[i]-'a'];
				if(sepChars.count(moveLetters[i])){
					sepChars.erase(moveLetters[i]);
				}
			}
		}

		for(auto& c: sepChars){
			cannotHave |= translate[c-'a'];
		}

	}

	std::cout << "You've found the word! Thanks for using the wordle tool!" << std::endl;

	freeWords(head);

	return 0;
}