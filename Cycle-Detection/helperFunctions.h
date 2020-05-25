#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "Node.h"


bool checkNew(int val, Node<int>* head){
	Node<int>* current = head;
	while(current){
		if(current->getData() == val) return 1;
		current = current->getNext();
	}

	return 0;
}

Node<int>* readIn(std::string s){
	
	int val;
	std::ifstream myfile(s);
	
	Node<int>* head = new Node<int>();
	Node<int> *current, *prev;

	myfile>>val;
	head->setData(val);
	prev = head;

	while(myfile>>val){
		if(checkNew(val, head)) return head;
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


void addTailLoop(Node<int>* head){
	if(!head) return;
	Node<int>* current = head;
	while(current->getNext()){
		current=current->getNext();
	}
	current->setNext(head);
}