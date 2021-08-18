#include <iostream>
#include <limits>
#include "maxHeap.h"


int maxArrSize = 101;
int heapSize = 14;


//Increases the key of the element at node to newKey (newKey must be greater than node's current value)
void increaseKey(int arr[], int node, int newKey){
	
	if(arr[node] > newKey){
		std::cout << "Failed to increase key: newKey failed to exceed the key of the requested node" << std::endl;
		return;
	}

	arr[node] = newKey;

	int hold;

	//Condition 1: The current node is not at the root
	//Condition 2: The child is greater than its parent
	while(node > 0 && arr[node] > arr[getParent(node)]){
		
		//Swap node with its parent
		hold = arr[node];
		arr[node] = arr[getParent(node)];
		arr[getParent(node)] = hold;


		//Get the next parent up
		node = getParent(node);
	}

}


//Insert node with key x into the priority queue
void insert(int arr[], int newKey){
	if (heapSize+1 >= maxArrSize){
		std::cout << "Failed to insert: Heap is full" << std::endl;
		return;
	}

	heapSize++;
	arr[heapSize - 1] = std::numeric_limits<int>::min(); //Set key to -infinity then use increaseKey() to make the correct updates
	increaseKey(arr, heapSize-1, newKey);

}





//Returns the maximum key (without removal)
int getMax(int arr[]){

	if(heapSize < 1){
		std::cout << "Failed to get max: Heap underflow";
		return -1;
	}
	return arr[0];
}

//Extracts the maximum key
int extractMax(int arr[]){

	if (heapSize < 1){
		std::cout << "Failed to extract max: Heap underflow" << std::endl;
		return -1;
	}

	int currentMax = getMax(arr);
	if(currentMax < 0) return -1;

	arr[0] = arr[heapSize-1];

	heapSize--;

	maxHeapify(arr, heapSize, 0);

	return currentMax;

}




int main(int argc, char** argv){

	int arr[maxArrSize] = {1, 33, 7, 3, 51, 10, 6, 13, 2, 64, 103, 9, 4, 24};

	std::cout << "Original array: ";
	printArray(arr, heapSize);

	buildMaxHeap(arr, heapSize);

	std::cout << "Priority queue as an array: ";
	printArray(arr, heapSize);


	std::cout << "The current max is: "<< getMax(arr) << std::endl;

	int insertNum = 150;
	std::cout << "Inserting " << insertNum << " into priority queue" << std::endl;
	insert(arr, 150);

	std::cout << "Priority queue after " << insertNum << " was added: ";
	printArray(arr, heapSize);

	std::cout << "Extracting max"<<std::endl;
	std::cout << "The extracted max was: " << extractMax(arr) << std::endl;

	std::cout << "The priority queue after extraction is: ";
	printArray(arr, heapSize);



	
	return 0;
}