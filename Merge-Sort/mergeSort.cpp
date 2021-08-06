#include <iostream>
#include <limits>

void printArray(int a[], int len){
	for(int i=1; i<len; i++){
		std::cout << a[i-1] << ", ";
	}
	std::cout << a[len-1] << std::endl;
}


void mergeSortJoin(int numArray[], int start, int mid, int end){

	int leftSize = mid-start+1;
	int rightSize = end-mid;

	int leftArray[leftSize+1] = {0};
	int rightArray[rightSize+1] = {0};

	//copy left array
	for(int i=0; i<leftSize; i++){
		leftArray[i] = numArray[start+i];
	}

	//Left terminal value
	leftArray[leftSize] = std::numeric_limits<int>::max();

	//copy right array
	for(int i=0; i<rightSize; i++){
		rightArray[i] = numArray[mid+1+i];
	}

	//Right terminal value
	rightArray[rightSize] = std::numeric_limits<int>::max();

	int leftIndex = 0;
	int rightIndex = 0;

	for(int i=start; i<=end; i++){
		if(leftArray[leftIndex] < rightArray[rightIndex]){
			numArray[i] = leftArray[leftIndex++];
		}else{
			numArray[i] = rightArray[rightIndex++];
		}
	}

}


void mergeSort(int numArray[], int start, int end){
	//Base condition
	if (start>=end) return;

	int mid = (start+end)/2;

	mergeSort(numArray, start, mid);
	mergeSort(numArray, mid+1, end);
	mergeSortJoin(numArray, start, mid, end);
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