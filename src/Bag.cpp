#include "Bag.hpp"
#include <iostream>

/**
 * A Bag is a collection of Tokens (chips) that supports
 * functions that work by enumerating the contents.
 *
 * @author: Ali Eldaoushy
 */

Bag::Bag(int numTokens) : contents(numTokens) {}

void Bag::firstToken() const {
    if (!contents.empty())
        std::cout << contents[0].toString() << std::endl;
}

void Bag::allTokens() const {
    for (const auto& token : contents) {
        // TODO: print out the currently chosen Token
        std::cout << token.toString() << std::endl;
    }
}

void Bag::allTokensWhile() const {
    size_t i = 0;
    // TODO: turn this into a while loop that enumerates and
    // prints all of the tokens in the bag
    while (i < contents.size()) {
        std::cout <<  contents[i].getValue() << contents[i].getColor() << std::endl;
        i = i + 1;
    }
}

int Bag::addTokens() const {
    // TODO: write a loop that enumerates the entire bag
	// and sums the total of all of the Token values
    size_t i = 0;
    size_t sum = 0;
    while (i < contents.size()){
        sum = sum + contents[i].getValue();
        i = i + 1;
    }
    return sum;
}

int Bag::highValueTokens() const {
    // TODO: write a loop that enumerates the entire bag
    // and returns the number of high value Tokens
    size_t i = 0;
    size_t count = 0;
    while (i < contents.size()) {
        if (contents[i].isHighValue()) {
            count += 1;
        }
        i += 1;
    }
    return count;	
}

int Bag::firstGreen() const {
    // TODO: search bag for a green Token, if found, return its index
    size_t i = 0;
    while (i < contents.size()) {
        if (contents[i].getColor() == "Green") {
            return i;
        }  
        else {
            i = i + 1;
        }
    }
    return -1;
}