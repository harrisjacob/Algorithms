#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Node.h"



Node<int>* readIn(std::string s){
	
	std::string line;
	std::ifstream myfile(s);
	getline(myfile, line);

	std::stringstream data(line);
	
	int val;
	Node<int>* head = new Node<int>();
	Node<int> *current, *prev;

	data >> val;
	head->setData(val);
	prev = head;

	while(data>>val){
		current = new Node<int>(val, nullptr);
		prev->setNext(current);
		prev = current;
	}

	return head;

}

void printNodes(Node<int>* head){
	Node<int>* current = head;
	while(current){
		std::cout << *current << std::endl;
		current = current->getNext();
	}
}


int main(int argc, char** argv){

	Node<int>* head = readIn(argv[1]);
	printNodes(head);

	return 0;
}