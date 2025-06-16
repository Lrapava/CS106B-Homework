/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	capacity = 1;
	pqsize = 0;
	arr = new string[capacity];
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] arr;
}

int HeapPriorityQueue::size() {
	return pqsize;
}

bool HeapPriorityQueue::isEmpty() {
	return pqsize == 0;
}

void HeapPriorityQueue::bubbleUp(int i) {
	if (i != 0) {	
		int parent = (i-1)/2;
		if (arr[parent] > arr[i]) {
			swap(arr[parent], arr[i]);
			bubbleUp(parent);
		}
	}
}

void HeapPriorityQueue::enqueue(string value) {
	if (pqsize == capacity) {
		expandCapacity();
	}
	arr[pqsize] = value;
	bubbleUp(pqsize);
	pqsize++;
}

string HeapPriorityQueue::peek() {
	if (pqsize == 0) {
		error("Error: peek called on empty priority queue\n");
	}
	return arr[0];
}

void HeapPriorityQueue::expandCapacity() {
	capacity *= 2;
	string* newArr = new string[capacity];
	for (int i = 0; i < pqsize; i++) {
		newArr[i] = arr[i];
	}
	delete[] arr;
	arr = newArr;
}

void HeapPriorityQueue::bubbleDown(int i) {
	int cand1 = 2*i + 1;
	int cand2 = 2*i + 2;
	if (cand1 >= pqsize) return;

	int finalCand = cand1;
	if (cand2 < pqsize && arr[cand2] < arr[cand1]) {
		finalCand = cand2;
	}

	if (arr[i] > arr[finalCand]) {
		swap(arr[i], arr[finalCand]);
		bubbleDown(finalCand);
	}
}

string HeapPriorityQueue::dequeueMin() {
	if (pqsize == 0) {
		error("Error: dequeueMin called on empty priority queue\n");
	}
	string val = arr[0];
	arr[0] = arr[pqsize - 1];
	pqsize--;
	bubbleDown(0);
	return val;
}
