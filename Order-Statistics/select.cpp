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

void insertionSort(int vals[], int start, int len){
	
	int key, pos;
	for(int i=1+start; i<start+len; i++){
		key = vals[i];
		pos = i-1;
		while (pos>start-1 & vals[pos]>=key){
			vals[pos+1] = vals[pos];
			pos--;
		}
		vals[pos+1] = key;
	}
}

int select(int vals[], int len, int rank){

	int groupSize = 5;

	int groups = len / groupSize;
	int remaining = len % groupSize;

	//Is there a partial group that is unfilled?
	groups += (!remaining) ? 0 : 1;


	//insertion sort the members of each of the groups
	//ignore the final group
	for(int groupNum=0; groupNum<groups-1; groupNum++){
		insertionSort(vals, groupNum*groupSize, groupSize);
	}

	//insertion sort the members of the last group
	if(!remaining){
		insertionSort(vals, (groups-1)*groupSize, groupSize); //Group is completely filled
	}else{
		insertionSort(vals, (groups-1)*groupSize, remaining); //Group is partially filled
	}



	return 0;
}


void printArray(int arr[], int len){

	for(int i=0; i<len; i++){
		std::cout << arr[i] << ", ";
	}
	std::cout << std::endl;
}

int main(int argc, char** argv){

	int vals[] = {1, 33, 7, 3, 51, 10, 6, 13, 2, 64, 103, 9, 4, 24};
	int len = sizeof(vals)/sizeof(vals[0]);
	int rank = 0;

	printArray(vals, len);

	select(vals, len, 0);
	//std::cout << pos << std::endl;

	printArray(vals, len);

	//std::cout << "The element with rank " << rank << " is " << select(vals, len, rank) << std::endl;

	return 0;
}