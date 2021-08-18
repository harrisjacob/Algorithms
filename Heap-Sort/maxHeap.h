#include <iostream>

void printArray(int a[], int len){
	for(int i=1; i<len; i++){
		std::cout << a[i-1] << ", ";
	}
	std::cout << a[len-1] << std::endl;
}

//Returns left child
int leftChild(int ind){
	return ind*2;
}

//Return right child
int rightChild(int ind){
	return ind*2+1; 
}

int getParent(int ind){
	return ind/2;
}

//Maintains max-heap property
void maxHeapify(int arr[], int heapSize, int node){
	int largest, hold;
	//Retrieve children
	int left = leftChild(node);
	int right = rightChild(node);

	//Find the largest of the current node and its children
	//Checking against heapSize determines if child is valid
	if(left<heapSize && arr[left] > arr[node])
		largest = left;
	else
		largest = node;

	if(right<heapSize && arr[right] > arr[largest])
		largest = right;

	if(largest!=node){
		//Push the largest element up the heap
		hold = arr[largest];
		arr[largest] = arr[node];
		arr[node] = hold;

		//Fix the heap where the old node value was moved
		maxHeapify(arr, heapSize, largest);
	}

}

//Builds the max-heap
void buildMaxHeap(int arr[], int heapSize){

	//Elements n/2, ... , n-1 are the leaves of the heap
	for(int i=heapSize/2-1; i>=0; i--){
		maxHeapify(arr, heapSize, i);
	}

}

//Sorts the array in place
void heapsort(int arr[], int heapSize){
	buildMaxHeap(arr, heapSize);
	int hold;
	int activeSize = heapSize;
	for(int i=activeSize-1; i>0; i--){
		//Switch max element with element in current heap
		hold = arr[0];
		arr[0] = arr[activeSize-1];
		arr[activeSize-1] = hold;

		//Reduce active heap size to exclude sorted elements
		activeSize--;
		
		//Fix max heap after swap
		maxHeapify(arr, activeSize, 0);
	}

}