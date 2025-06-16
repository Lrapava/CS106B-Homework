/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = new linkedListElement();
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	linkedListElement* cur = head;
	while (cur != NULL) {
		linkedListElement* prev = cur;
		cur = cur->next;
		delete prev;
	}
}

int LinkedListPriorityQueue::size() {
	return pqsize;
}

bool LinkedListPriorityQueue::isEmpty() {
	return pqsize == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	linkedListElement* newVal = new linkedListElement(value);
	linkedListElement* cur = head;

	while (cur->next != NULL && cur->next->value < value) {
		cur = cur->next;
	}
	newVal->next = cur->next;
	cur->next = newVal;
	pqsize++;
}

string LinkedListPriorityQueue::peek() {
	if (pqsize == 0) {
		error("Error: peek called on empty priority queue\n");
	}
	return head->next->value;
}

string LinkedListPriorityQueue::dequeueMin() {
	if (pqsize == 0) {
		error("Error: tried calling dequeueMin from an empty priority queue\n");
	}
	pqsize--;
	std::string val = head->next->value;
	linkedListElement* prev = head->next;
	head->next = head->next->next;
	delete prev;
	return val;
}

