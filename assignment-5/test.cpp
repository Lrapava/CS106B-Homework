#include <iostream>
#include "pqueue-vector.h"
#include "pqueue-linkedlist.h"
#include "pqueue-doublylinkedlist.h"
#include "pqueue-heap.h"

int main() {
	// VectorPriorityQueue pq;
	// LinkedListPriorityQueue pq;
	// DoublyLinkedPriorityQueue pq;
	HeapPriorityQueue pq;
	
	pq.enqueue("World");
	pq.enqueue("Hello");
	pq.enqueue("123");
	pq.enqueue("112");
	std::cout << "peek " << pq.peek() << "\n";
	std::cout << "size " << pq.size() << "\n";
	
	std::cout << "dqmi " << pq.dequeueMin() << "\n";
	std::cout << "dqmi " << pq.dequeueMin() << "\n";
	std::cout << "dqmi " << pq.dequeueMin() << "\n";
	std::cout << "size " << pq.size() << "\n";
	std::cout << "peek " << pq.peek() << "\n";
	std::cout << "dqmi " << pq.dequeueMin() << "\n";
	std::cout << "peek " << pq.peek() << "\n";
	std::cout << "dqmi " << pq.dequeueMin() << "\n";
	
}
