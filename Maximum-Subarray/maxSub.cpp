#include <iostream>
#include <limits>
#include "mergeSort.h"

struct Range{
	int startIndex;
	int endIndex;
	int value;
};


Range* findMaxCrossingSub(int arr[], int start, int mid, int end){
	int leftSum = std::numeric_limits<int>::min();
	int rightSum = std::numeric_limits<int>::min();
	int sum = 0;

	Range* midRange = (Range *)(malloc(sizeof(Range)));
	for(int i=mid; i>=start; i--){
		sum += arr[i];
		if(sum > leftSum){
			leftSum = sum;
			midRange->startIndex = i;
		}
	}

	sum = 0;
	

	for(int i=mid+1; i<end; i++){
		sum+= arr[i];
		if(sum > rightSum){
			rightSum = sum;
			midRange->endIndex = i;
		}
	}

	if(leftSum == std::numeric_limits<int>::min()) leftSum = 0;
	if(rightSum == std::numeric_limits<int>::min()) rightSum = 0;


	midRange->value = rightSum+leftSum;
	return midRange;
}


Range* findMaxSub(int arr[], int start, int end){
	if(start>=end){
		Range* baseRange = (Range *)(malloc(sizeof(Range)));
		baseRange->startIndex = start;
		baseRange->endIndex = end;
		baseRange->value = arr[start];
		return baseRange;
	}

	int mid = (start+end)/2;

	Range* leftRange = findMaxSub(arr, start, mid);
	Range* rightRange = findMaxSub(arr, mid+1, end);
	Range* crossing = findMaxCrossingSub(arr, start, mid, end); 

	if(leftRange->value >= rightRange->value && leftRange->value >= crossing->value){
		free(rightRange);
		free(crossing);
		return leftRange;
	}else if(rightRange->value >= leftRange->value && rightRange->value >= crossing->value){
		free(leftRange);
		free(crossing);
		return rightRange;
	}

	free(leftRange);
	free(rightRange);
	return crossing;
}


void calcDailyChange(int prices[], int dailyChange[], int len){

	for(int i=1; i<len; i++){
		dailyChange[i-1] = prices[i] - prices[i-1];
	}

}

int main(int argc, char** argv){

	int prices[] = {100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 94, 90, 97};
	int priceLen = sizeof(prices)/sizeof(prices[1]);

	int dailyChange[priceLen] = {};
	int dailyChangeLen = priceLen-1;

	calcDailyChange(prices, dailyChange, priceLen);

	Range* outputRange = findMaxSub(dailyChange, 0, dailyChangeLen-1);
	
	std::cout << "Maximum Subarray Result:"<<std::endl;
	std::cout << "Buy before day " << outputRange->startIndex << " opens" << std::endl;
	std::cout << "Sell after day " << outputRange->endIndex << " closes (before day " << (outputRange->endIndex)+1 << " opens)" << std::endl;
	std::cout << "Maximized profit: " << outputRange->value << std::endl;

	free(outputRange);


	return 0;
}