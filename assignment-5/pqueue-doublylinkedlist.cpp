/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = new DoublyLinkedListElement();
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	DoublyLinkedListElement* cur = head;
	while (cur != NULL) {
		DoublyLinkedListElement* prev = cur;
		cur = cur->next;
		delete prev;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return pqsize;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return pqsize == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	pqsize++;
	DoublyLinkedListElement* newElem = new DoublyLinkedListElement(value);
	newElem->next = head->next;
	newElem->prev = head;
	head->next = newElem;
    if (newElem->next != NULL) {
        newElem->next->prev = newElem;
    }
}

string DoublyLinkedListPriorityQueue::peek() {
	if (pqsize == 0) {
		error("Error: peek called on empty priority queue\n");
	}
	DoublyLinkedListElement* cur = head->next;
	DoublyLinkedListElement* minVal = cur;
	while (cur != NULL) {
		if (cur->value < minVal->value) {
			minVal = cur;
		}
		cur = cur->next;
	}
	return minVal->value;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if (pqsize == 0) {
		error("Error: tried calling dequeueMin from an empty priority queue\n");
	}
	DoublyLinkedListElement* cur = head->next;
	DoublyLinkedListElement* minVal = cur;
	while (cur != NULL) {
		if (cur->value < minVal->value) {
			minVal = cur;
		}
		cur = cur->next;
	}
	std::string val = minVal->value;
	if (minVal->prev != NULL) {
		minVal->prev->next = minVal->next;
	}
	if (minVal->next != NULL) {
		minVal->next->prev = minVal->prev;
	}
	pqsize--;
	delete minVal;
	return val;
}

