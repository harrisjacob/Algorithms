#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctype.h>
#include <vector>

enum NodeType{literal, character};

struct Node{

	NodeType mode;
	char syntax;
	int value;
	Node* prev = NULL;
	Node* next = NULL;

};

std::string getLine(std::ifstream& in){
	std::string s;
	std::getline(in, s);
	if(!in.good() || s.empty()) return s;
	std::stringstream ss(s);
	std::getline(ss, s, '\r');
	if(!in.good()) return s;
	return s;
}


Node* generateNode(char c){

	Node* newNode = new Node;
	if(isdigit(c)){
		newNode->mode = literal;
		newNode->value = c-'0';
	}else{
		newNode->mode = character;
		newNode->syntax = c;
	}

	return newNode;
}

void printNumberUtil(Node* current){
	if(!current) return;
	if(current->mode == literal){
		std::cout << current->value;
	}else{
		std::cout << current->syntax;
	}
	printNumberUtil(current->next);
}

void printNumber(Node* current){
	printNumberUtil(current);
	std::cout << std::endl;
}


void freeNumbersUtil(Node* a){
	if(!a) return;
	freeNumbersUtil(a->next);
	delete a;
}


void freeNumbers(std::vector<Node*>& numbers){
	for(auto a: numbers){
		freeNumbersUtil(a);
	}
}

void join(Node* base, Node* added){

	Node* head;

	Node* temp = new Node();
	temp->mode = character;
	temp->syntax = '[';

	head = temp;

	head->next = base;
	base->prev = 

}


void addNumbers(std::vector<Node *>& numbers){

	for(int i=1; i<numbers.size(); i++){

		numbers[0]=join(numbers[0], numbers[1]);

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

	std::vector<Node*> numbers;

	std::string line;
	Node* current, *head;

	while(!((line=getLine(in)).empty())){

		head = generateNode(line[0]);
		current = head;
		for(int i=1; i<line.size();i++){
			current->next = generateNode(line[i]);
			current->next->prev = current;
			current = current->next;
		}

		numbers.push_back(head);

	}

	addNumbers(numbers);

	freeNumbers(numbers);

	in.close();

	return 0;
}