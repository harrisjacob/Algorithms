#include <iostream>
#include <limits>
#include "mergeSort.h"

void printArray(int a[], int len){
	for(int i=1; i<len; i++){
		std::cout << a[i-1] << ", ";
	}
	std::cout << a[len-1] << std::endl;
}


int main(int argc, char** argv){

	int numArray[] = {5, 8, 3, 5, 2, 7, 6, 1};
	int len = sizeof(numArray)/sizeof(numArray[0]);


	std::cout << "Original array: ";
	printArray(numArray, len);

	mergeSort(numArray, 0, len-1);


	std::cout << "Sorted array: ";
	printArray(numArray, len);
	
	return 0;
}