CC=g++
CFLAGS=-std=c++11

all: heapSort priorityQueue

heapSort: heapSort.cpp maxHeap.h
	$(CC) -o $@ $^ $(CFLAGS)

priorityQueue: priorityQueue.cpp maxHeap.h
	$(CC) -o $@ $^ $(CFLAGS)


clean:
	rm heapSort priorityQueue