#include "Stack.h"
#include <exception>
#include <iostream>


using namespace std;

/// BC = WC = T = Theta(1)
Stack::Stack() {

	this->size = 0;
    this->capacity = 1;
    this->elements = new TElem[this->capacity];
}

/// BC = Theta(1) WC = Theta(n) T = O(log2n)
void Stack::push(TElem elem) {

    if(this->size == this->capacity)
        this->resize();
    this->elements[this->size++] = elem;
}

/// BC = WC = T = Theta(1)
TElem Stack::top() const {

    if(this->size == 0)
        throw std::invalid_argument("No elements in list\n");
    return this->elements[this->size - 1];
}

/// BC = WC = T = Theta(1)
TElem Stack::pop() {

    if(this->size == 0)
        throw std::invalid_argument("No elements in list\n");

    TElem last_element = this->elements[this->size - 1];
    this->size--;
    return last_element;
}

/// BC = WC = T = Theta(1)
bool Stack::isEmpty() const {
    if(this->size)
	    return false;
    return true;
}

/// BC = WC = T = Theta(1)
Stack::~Stack() {

    delete[] elements;
}

/// BC = WC = T = Theta(n)
void Stack::resize() {
    this->capacity *= 2;
    auto* temp_elements = new TElem[this->capacity];
    for (int i = 0; i <= this->size - 1; i++)
        temp_elements[i] = this->elements[i];

    delete[] this->elements;
    this->elements = temp_elements;
}
