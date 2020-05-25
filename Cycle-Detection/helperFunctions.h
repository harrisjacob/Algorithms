#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "Node.h"


Node<int>* checkNew(int val, Node<int>* head){
	Node<int>* current = head;
	while(current){
		if(current->getData() == val) return current;
		current = current->getNext();
	}

	return NULL;
}

Node<int>* readIn(std::string s){
	
	int val;
	std::ifstream myfile(s);
	
	Node<int>* head = new Node<int>();
	Node<int> *current, *prev, *tested;

	myfile>>val;
	head->setData(val);
	prev = head;

	while(myfile>>val){
		if((tested = checkNew(val, head))){
			prev->setNext(tested);
			return head;
		}
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


void addTailLoop(Node<int>* head, int LoopDest){
	if(!head) return;
	
	int elemCounter=0;
	Node<int>* current = head;
	Node<int>* dest = NULL;
	while(current->getNext()){
		if(elemCounter == LoopDest) dest = current;
		current=current->getNext();
		elemCounter++;
	}

	if(!dest) dest = current;
	current->setNext(dest);
}