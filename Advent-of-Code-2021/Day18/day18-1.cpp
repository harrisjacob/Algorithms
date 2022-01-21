#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctype.h>
#include <vector>
#include <stack>


enum PairType{literal, group}; 

struct Pair{

	Pair* left = NULL;
	Pair* right = NULL;
	int value;
	PairType mode;

};

void freePairsUtil(Pair* pair){
	if(!pair) return;
	if(pair->left) freePairsUtil(pair->left);
	if(pair->right) freePairsUtil(pair->right);
	delete pair;
}


void freePairs(std::vector<Pair*>& p){
	for(auto i: p){
		freePairsUtil(i);
	}
}

Pair* createPair(std::string& s, int& offset){

	if(offset >= s.size()){
		std::cerr << "An error has occured while parsing" << std::endl;
		return NULL;
	}


	char c = s[offset++];

	Pair* newPair = new Pair;

	if(isdigit(c)){
		newPair->value = c-'0';
		newPair->mode = literal;
		return newPair;
	}

	newPair->mode = group;

	newPair->left = createPair(s, offset);
	offset++;
	newPair->right = createPair(s, offset);
	offset++;

	return newPair;

}

Pair* zeroPair(){
	Pair* newPair = new Pair;
	newPair->mode = literal;
	newPair->value = 0;
	return newPair;
}

void printPairUtil(Pair* pair){
	if(!pair) return;
	if(pair->mode == literal){
		std::cout << pair->value;
		return;
	}

	std::cout << "[";
	printPairUtil(pair->left);
	std::cout << ",";
	printPairUtil(pair->right);
	std::cout << "]";

}

void printPair(Pair* pair){
	printPairUtil(pair);
	std::cout << std::endl;
}

Pair* genSplitPair(int value){


	Pair* leftPair = new Pair;
	leftPair->mode = literal;
	leftPair->value = value/2;

	Pair* rightPair = new Pair;
	rightPair->mode = literal;
	rightPair->value = value/2 + (value%2);

	Pair* groupPair = new Pair;
	groupPair->mode = group;

	groupPair->left = leftPair;
	groupPair->right= rightPair;

	return groupPair;
}


bool resolvePair(Pair* &pair, int depth, std::stack<int*>& prev, int& next){


	// std::cout << depth << std::endl;

	if(pair->mode == literal){
		// std::cout << "Adding " << next << " to " << pair->value << std::endl;
		if(next > -1){
			pair->value += next;
			next = -1;
			return true;
		}


		if(pair->value > 9){
			Pair* splitPair = genSplitPair(pair->value);
			prev.push(&(splitPair->left->value));
			prev.push(&(splitPair->right->value));
			pair = splitPair;
			// std::cout << "Split!\n";
			return true;

		}else{
			prev.push(&(pair->value));
		}
		
		// std::cout << "Pushing " << pair->value << std::endl;
	}else{




		if(depth > 4){
			// std::cout << "Exploding " << pair->left->value << " and "<< pair->right->value << std::endl;
			// std::cout << "Explode!\n";
			next = pair->right->value;

			// std::cout << "next: " << next << std::endl;
				//There should be two values on the stack
				// prev.pop();
				// prev.pop();
			if(!prev.empty()){
				*(prev.top()) += pair->left->value;
			}
			freePairsUtil(pair);
			pair = zeroPair();
		}else{
			if(resolvePair(pair->left, depth+1, prev, next)) return true;
			if(resolvePair(pair->right, depth+1, prev, next)) return true;
		}
				

	}

	return false;

}

void dumpStack(std::stack<int*>& prev){
	while(!prev.empty()){
		std::cout << *prev.top() << std::endl;;
		prev.pop();
	}
}


void addPairs(std::vector<Pair*>& pairs){

		
		// bool needsUpdate = true;
		// while(needsUpdate){
		// 	int next = -1;
		// 	std::stack<int*> prev;
		// 	needsUpdate = resolvePair(pairs[0], 1, prev, next);
		// 	if(next > -1) needsUpdate = true;
		// 	// printPair(pairs[0]);
		// 	// std::cout << "Update: " << needsUpdate << std::endl;
		// }
		// // dumpStack(prev);

	for(int i=1; i<pairs.size(); i++){

		Pair* base = pairs[0];
		Pair* current = pairs[i];
		Pair* newPair = new Pair;
		newPair->left = base;
		newPair->right = current;
		newPair->mode = group;
		std::cout << "New Pair: ";
		printPair(newPair);

		bool needsUpdate = true;
		while(needsUpdate){
			int next = -1;
			std::stack<int*> prev;
			needsUpdate = (resolvePair(newPair, 1, prev, next) || next > -1);
			printPair(newPair);
		}

		pairs[0] = newPair;
		pairs[i] = NULL;	//Prevents double free, pointer can still be accessed through newly created pair
		// printPair(pairs[0]);
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

	std::vector<Pair*> pairs;

	while(!((line=getLine(in)).empty())){

		int offset = 0;
		Pair* node = createPair(line, offset);
		pairs.push_back(node);

	}

	
	printPair(pairs[0]);
	addPairs(pairs);

	
	

	freePairs(pairs);

	in.close();

	return 0;
}