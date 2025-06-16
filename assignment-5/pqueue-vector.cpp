/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

#include <algorithm>
#include <vector>
#include <functional>

VectorPriorityQueue::VectorPriorityQueue() {}

VectorPriorityQueue::~VectorPriorityQueue() {}

int VectorPriorityQueue::size() {
	return vec.size();
}

bool VectorPriorityQueue::isEmpty() {
	return vec.size() == 0;
}

void VectorPriorityQueue::enqueue(string value) {
	vec.push_back(value);
}

string VectorPriorityQueue::peek() {
	if (vec.empty()) {
		error("Error: peek called on empty priority queue\n");
	}
	std::string minima = vec[0];
	for (std::string obj : vec) {
		if (obj < minima) {
			minima = obj;
		}
	}
	return minima;
}

string VectorPriorityQueue::dequeueMin() {
	if (vec.empty()) {
		error("Error: tried calling dequeueMin from an empty priority queue\n");
	}
	std::vector<std::string>::iterator minIt = 
		std::min_element(vec.begin(), vec.end());

	std::string value = *minIt;
	vec.erase(minIt);
	return value;
}
