#include <iostream>
#include "maxHeap.h"


int main(int argc, char** argv){

	//int numArray[] = {5, 8, 3, 5, 2, 7, 6, 1};
	int numArray[] = {1, 33, 7, 3, 51, 10, 6, 13, 2, 64, 103, 9, 4, 24};
	int len = sizeof(numArray)/sizeof(numArray[0]);


	std::cout << "Original array: ";
	printArray(numArray, len);

	heapsort(numArray, len);

	std::cout << "Sorted array: ";
	printArray(numArray, len);
	
	return 0;
}