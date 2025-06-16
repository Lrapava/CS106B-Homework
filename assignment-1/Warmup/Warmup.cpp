/*
 * File: Warmup.cpp
 * ----------------
 * Name: Luka Rapava
 * Section: [TODO: enter section leader here]
 * This program generates a hash code based on user's name.
 * As given, this code has two compiler errors you need to track down 
 * and fix in order to get the program up and running.
 * [Originally written by Julie Zelenski]
 */

// Made the code compatible with STL + few minor improvements.

#include <iostream>
#include <string>

/* Constants */

const int HASH_SEED = 5381;               /* Starting point for first cycle */
const int HASH_MULTIPLIER = 33;           /* Multiplier for each cycle      */
const int HASH_MASK = unsigned(-1) >> 1;  /* All 1 bits except the sign     */

/* Function prototypes */

unsigned int hashCode(std::string key);

/* Main program to test the hash function */

int main() {

	std::string name;
	
	std::cout << "Please enter your name: ";
    getline(std::cin, name);
    
    unsigned int code = hashCode(name);
    std::cout << "The hash code for your name is " << code << ".\n";

    return 0;
}

/*
 * Function: hash
 * Usage: unsigned int code = hashCode(std::string key);
 * --------------------------------
 * This function takes the key and uses it to derive a hash code,
 * which is nonnegative integer related to the key by a deterministic
 * function that distributes keys well across the space of integers.
 * The general method is called linear congruence, which is also used
 * in random-number generators.  The specific algorithm used here is
 * called djb2 after the initials of its inventor, Daniel J. Bernstein,
 * Professor of Mathematics at the University of Illinois at Chicago.
 */
unsigned int hashCode(std::string str) {
    unsigned int hash = HASH_SEED;
    int nchars = str.length();
    for (int i = 0; i < nchars; i++) {
        hash = HASH_MULTIPLIER * hash + str[i];
    }
    return (hash & HASH_MASK);
}
