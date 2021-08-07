#!/usr/bin/env python3

def mergeSortJoin(numArray, start, mid, end):

	leftArray = []
	rightArray = []

	for element in numArray[start:mid+1]:
		leftArray.append(element)

	for element in numArray[mid+1:end+1]:
		rightArray.append(element)

	leftIndex = 0
	rightIndex = 0

	for i in range(start,end+1):
		if leftIndex >= len(leftArray):
			numArray[i] = rightArray[rightIndex]
			rightIndex+=1
			continue

		if rightIndex >= len(rightArray):
			numArray[i] = leftArray[leftIndex]
			leftIndex +=1
			continue

		if(leftArray[leftIndex] < rightArray[rightIndex]):
			numArray[i] = leftArray[leftIndex]
			leftIndex +=1
		else:
			numArray[i] = rightArray[rightIndex]
			rightIndex +=1


def mergeSort(numArray, start, end):
	if start >= end:
		return

	mid = (start+end)//2

	mergeSort(numArray, start, mid)
	mergeSort(numArray, mid+1, end)
	mergeSortJoin(numArray, start, mid, end)


if __name__ == "__main__":
	numArray = [5, 8, 3, 5, 2, 7, 6, 1]
	arrayLen = len(numArray)

	print("Original Array: ", numArray)
	mergeSort(numArray, 0, arrayLen-1)
	print("Sorted Array: ", numArray)