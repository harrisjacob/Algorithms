#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Node{
	int count = -1;
	Node* left = 0;
	Node* right = 0;
};


void printWords(Node* node, int depth){
	if(node->left){
		for(int i=0; i<depth; i++) std::cout << "-";
		std::cout << node->left->count << std::endl;
		printWords(node->left, depth+1); 
	}
	if(node->right){
		for(int i=0; i<depth; i++) std::cout << "-";
		std::cout << node->right->count << std::endl; 
		printWords(node->right, depth+1);
	}

}

void freeWords(Node* node){
	if(node->left) freeWords(node->left);
	if(node->right) freeWords(node->right);
	delete node;
}

void addWord(std::string input, Node* node, int offset){
	if(offset >= input.size()) return;
	
	Node* target;
	if(input[offset]=='0'){
		if(!node->left){
			target = new Node;
			node->left = target;
		}else{
			target = node->left;
		}
	}else{
		if(!node->right){
			target = new Node;
			node->right = target;
		}else{
			target = node->right;
		}
	}

	target->count +=1;

	addWord(input, target, offset+1);

}

int getMaj(Node* node, int retVal){
	if(!node->left && !node->right) return retVal;
	
	retVal = retVal << 1;

	if(!node->right && node->left) return getMaj(node->left, retVal);
	
	if((!node->left && node->right) || node->right->count >= node->left->count){
		retVal |= 1;
		return getMaj(node->right, retVal);
	}


	return getMaj(node->left, retVal);

}

int getMin(Node* node, int retVal){
	if(!node->left && !node->right) return retVal;

	retVal = retVal << 1;

	if(!node->right && node->left) return getMin(node->left, retVal);
	if(!node->left && node->right){
		retVal |= 1;
		return getMin(node->right, retVal);
	}


	if(node->left->count <= node->right->count){
		return getMin(node->left, retVal);
	}else{
		retVal |= 1;
		return getMin(node->right, retVal);
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

	std::string line, input;
	Node* head = new Node;

	//Generate Tree
	while(!in.eof()){
		std::getline(in, line);
		if(line.empty()) continue; 
		std::istringstream iss(line.c_str());
		iss>>input;

		addWord(input, head, 0);

	}

	//printWords(head, 0);

	int oxygen = getMaj(head, 0);
	std::cout << oxygen << std::endl;
	int co2 = getMin(head, 0);
	std::cout << co2 << std::endl;



	std::cout << "Answer: " << co2*oxygen << std::endl;


	freeWords(head);
	in.close();
	return 0;
}