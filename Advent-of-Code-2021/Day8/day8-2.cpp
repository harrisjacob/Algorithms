#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>


class Word{

	std::string data;
	Word* next = NULL;

public:
	Word(std::string& s) {
		std::sort(s.begin(), s.end());
		data = s;
	}

	void setNext(Word* w){
		next = w;
	}

	std::string word(){
		return data;
	}

	Word* getNext(){
		return next;
	}

};

void printCand(Word* words[]){
	for(int i=0; i<10; i++){
		Word* current = words[i];
		std::cout << i << ": ";
		while(current){
			std::cout << current->word() << " -> ";
			current = current->getNext();
		}
		std::cout << std::endl;
	}
}

void freeCand(Word* words[]){
	for(int i=0; i<10; i++){
		Word* current, *next;
		current = words[i];
		while(current){
			next = current->getNext();
			delete current;
			current = next;
		}
	}
}

char getDiff(std::string alpha, std::string beta){
	for(int i=0; i<alpha.size(); i++){
		if(i==alpha.size()-1 || alpha[i]!=beta[i]) return alpha[i];
	}
	return 'z';
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


	std::string line, seg;
	char sides[7];
	//Top: 0, top left:1, top right: 2, middle:3, bottom left: 4, bottom right:5, bottom:6
	std::string numbers[10];


	int segSz;

	int total = 0;

	while(!in.eof()){
		std::getline(in, line);
		std::stringstream ss(line.c_str());
		if(line.empty()) break;

		Word* words[10] = {0};
		Word* addWord;

		for(int i=0; i<10; i++){
			ss >> seg;
			segSz = seg.size();

			addWord = new Word(seg);

			if(!words[segSz]){
				words[segSz] = addWord;
			}else{
				addWord->setNext(words[segSz]);
				words[segSz] = addWord;
			}

		}


		//Add numbers 1, 7, 4, 8
		numbers[1] = words[2]->word();
		numbers[7] = words[3]->word();
		numbers[4] = words[4]->word();
		numbers[8] = words[7]->word();



		//Get top segment
		sides[0] = getDiff(numbers[7], numbers[1]);

		//Get 6 (6 is the only 6 segment digit that doesn't contain both segments of digit 1)
		Word* current, *prev;
		current = words[6];
		prev = NULL;
		bool found = false;
		while(current){
			//Compare it to 8 because there is only one different character for 6 segment charactesr
			char diffChar = getDiff(numbers[8], current->word());
			if(diffChar == numbers[1][0]){
				numbers[6] = current->word();
				sides[2] = diffChar; //Upper right segment
				sides[5] = numbers[1][1]; //Bottom right segment of 1
				found = true;
			}else if(diffChar == numbers[1][1]){
				numbers[6] = current->word();
				sides[2] = diffChar; //Upper right segment
				sides[5] = numbers[1][0]; //Bottom right segment of 1
				found = true;
			}

			//Remove 6 fron list
			if(found){
				if(!prev){
					words[6] = current->getNext();
				}else{
					prev->setNext(current->getNext());
				}

				delete current;
				break;
			}



			prev = current;
			current = current->getNext();
		}

		//5 is the only 5 segment digit that doesn't contain upper right
		prev = NULL;
		current = words[5];
		while(current){
			//Search each word for the upper right segment
			if(current->word().find(sides[2]) == std::string::npos){
				numbers[5] = current->word();

			
				if(!prev){
					words[5] = current->getNext();
				}else{
					prev->setNext(current->getNext());
				}

				break;

			}

			prev = current;
			current = current->getNext();
		}


		//The difference between 5 and 6 is the bottom left segment
		sides[4] = getDiff(numbers[6], numbers[5]);


		//Use 8 and bottom left segment to find 9 (0 will be the only 6 seg remaining)
		Word* sixCand = words[6];

		char sixSegDiff = getDiff(numbers[8], sixCand->word());
		if(sixSegDiff == sides[4]){						//If this is the 9
			numbers[9] = sixCand->word();				//Record it as the 9
			numbers[0] = sixCand->getNext()->word();	//The remaining 6 seg is the 0
		}else{
			numbers[0] = sixCand->word();
			numbers[9] = sixCand->getNext()->word();
		}

		sides[3] = getDiff(numbers[8], numbers[0]); //Record middle segment 



		//2 and 3 are the only 5 segment displays remaining
		//Search for the word that has the bottom left segment (only the 2 digit has this)

		Word* fiveCand = words[5];
		if(words[5]->word().find(sides[4]) == std::string::npos){ //If the word doesn't have the bottom left
			//Its the 3
			numbers[3] = words[5]->word();
			numbers[2] = words[5]->getNext()->word();

		}else{
			//Its the 2
			numbers[2] = words[5]->word();
			numbers[3] = words[5]->getNext()->word();
		}



		//All numbers should be known by now

		//Get rid of the bar
		ss >> seg;


		int decode = 0;
		//Read the 4 coded numbers
		for(int i=0; i<4; i++){
			decode*=10;
			ss >> seg;
			std::sort(seg.begin(), seg.end());

			for(int i=0; i<10; i++){
				if(!seg.compare(numbers[i])) decode +=i;
			}

		}

		total+= decode;


		freeCand(words);

	}

	std::cout << "The total is: " << total << std::endl;

	in.close();

	return 0;
}