#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

int main(int argc, char* argv[]){

	std::string hiddenWord = "GUESS";
	std::string userWord;
	std::string exact;
	int count; 

	std::cout << "Welcome to Wordle!\nTry to guess the word\n\n";

	do{
		std::vector<char> wrongSpot;
		std::unordered_set<char> nonExact;

		count = 0;
		exact = "_ _ _ _ _";
		std::cin >> userWord;
		if(userWord.size() != 5){
			std::cout << "Word must be length 5" << std::endl;
			continue;
		}

		for(int i=0; i<5; i++){
			if(userWord[i]==hiddenWord[i]){
				exact[i*2] = hiddenWord[i];
				count++;
			}else{
				nonExact.insert(hiddenWord[i]);
			}
		}

		for(int i=0; i<5; i++){
			if(exact[i*2]!='_') continue;

			if(nonExact.count(userWord[i])){
				wrongSpot.push_back(userWord[i]);
				nonExact.erase(userWord[i]);
			}
		}

		std::cout << exact;
		if(wrongSpot.size()){
			std::cout << "\tLetters in the incorrect position: ";
			for(auto l: wrongSpot){
				std::cout << l <<  " ";
			}
		}
		std::cout << std::endl << std::endl;


	}while(count < 5);

	std::cout << "That's it!" << std::endl;

	return 0;
}