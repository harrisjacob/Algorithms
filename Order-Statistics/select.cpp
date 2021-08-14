#include <iostream>

int partition(int arr[], int start, int end, int part){

	//Move partition element to end of array
	int partition = arr[part];
	arr[part] = arr[end];
	arr[end] = partition;

	int hold;
	int i = start - 1;
	for(int j=start; j<=end-1; j++){
		//Any elements smaller than partition should be moved to the left
		if(arr[j] < partition){
			i++;
			hold = arr[i];
			arr[i] = arr[j];
			arr[j] = hold;
		}
	}

	//Swap partition to correct location
	i++;
	arr[end] = arr[i];
	arr[i] = partition;

	return i;
}

void insertionSort(int vals[], int len){

	int key, pos;
	for(int i=1; i<len; i++){
		key = vals[i];
		pos = i-1;
		while (pos>0 && vals[pos]>=key){
			vals[pos+1] = vals[pos];
			pos--;
		}
		vals[pos+1] = key;
	}

}

int select(int vals[], int rank){

	return 0;
}


void printArray(int arr[], int len){

	for(int i=0; i<len; i++){
		std::cout << arr[i] << ", ";
	}
	std::cout << std::endl;
}

int main(int argc, char** argv){

	int vals[] = {1, 33, 7, 3, 51, 2, 6, 10, 13, 64, 4, 103, 9, 24};
	int len = sizeof(vals)/sizeof(vals[0]);
	int rank = 0;

	printArray(vals, len);

	insertionSort(vals, len);
	//std::cout << pos << std::endl;

	printArray(vals, len);

	//std::cout << "The element with rank " << rank << " is " << select(vals, rank) << std::endl;

	return 0;
}