#!/usr/bin/env python3

def findCrossingMaxSub(arr, start, mid, end):
	leftSum = None
	rightSum = None

	leftIndex = mid
	rightIndex = mid

	currentSum = 0

	for i in range(start,mid+1):
		j = mid - i
		currentSum += arr[j]

		if not leftSum or currentSum > leftSum:
			leftSum = currentSum
			leftIndex = j

	currentSum = 0

	for i in range(mid+1, end+1):
		currentSum += arr[i]

		if not rightSum or currentSum > rightSum:
			rightSum = currentSum
			rightIndex = i


	return(leftIndex, rightIndex, leftSum+rightSum)

		



def findMaxSub(arr, start, end):
	
	if start >= end:
		return (start, end, arr[start])


	mid = (start+end)//2

	checkLeft = findMaxSub(arr, start, mid)
	checkRight = findMaxSub(arr, mid+1, end)
	crossing = findCrossingMaxSub(arr, start, mid, end)

	if checkLeft[2] >= checkRight[2] and checkLeft[2] >= crossing[2]:
		return checkLeft
	elif checkRight[2] >= checkLeft[2] and checkRight[2] >= crossing[2]:
		return checkRight
	else:
		return crossing




if __name__ == "__main__":

	prices = [100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 94, 90, 97]

	dailyChange = []

	for i in range(1,len(prices)):
		dailyChange.append(prices[i] - prices[i-1])

	maxSubResult = findMaxSub(dailyChange, 0, len(dailyChange)-1)

	print("Maximum Subarray Result:")
	print(f"Buy at the beginning of day {maxSubResult[0]}")
	print(f"Sell at the end of day {maxSubResult[1]+1}")
	print(f"Maximized profit: {maxSubResult[2]}")