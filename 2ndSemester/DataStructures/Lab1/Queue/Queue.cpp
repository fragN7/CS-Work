#include "Queue.h"
#include <exception>
#include <iostream>

using namespace std;


Queue::Queue() {

    this->size = 2;
    this->start = -1;
    this->end = -1;
    this->elements = new TElem[this->size];
}

/// BC = WC = T = O(1)
bool Queue::isEmpty() const {
    if(this->start == -1 && this->end == -1)
        return true;
    return false;
}

/// Depends on the resize function so, BC = Theta(1), WC = Theta(n), T = O(n)
void Queue::push(const TElem elem) {

    if ((this->start == 0 && this->end == this->size - 1) || (this->end + 1 == this->start ))
    {
        this->resize();
        this->elements[this->end] = elem;
    }
    else if (this->start == -1)
    {
        this->start = 0;
        this->end = 0;
        this->elements[this->end] = elem;
    }
    else if (this->start != 0 && this->end == this->size - 1)
    {
        this->end = 0;
        this->elements[this->end] = elem;
    }
    else if (this->end != this->size - 1)
    {
        this->end++;
        this->elements[this->end] = elem;
    }
}

/// BC = WC = T = Theta(1)
TElem Queue::top() const {

    if(this->start == -1)
        throw std::invalid_argument("No elements in list\n");
	return this->elements[this->start];
}

/// BC = WC = T = Theta(1)
TElem Queue::pop() {

    if(this->start == -1)
        throw std::invalid_argument("No elements in list\n");

    TElem temp_elem = this->elements[this->start];
    if (this->start == this->end)
    {
        this->start = -1;
        this->end = -1;
    }
    else if (this->start == this->size - 1)
        this->start = 0;
    else
        this->start++;

    return temp_elem;
}

/// BC = WC = T = Theta(n)
TElem Queue::pop_minimum() {

    int min = INT_MAX, index;
    if(this->start == -1)
        throw std::invalid_argument("No elements in list\n");

    if(this->start < this->end)
    {
        for (int i = this->start; i <= this->end; i++)
            if (this->elements[i] < min)
            {
                min = this->elements[i];
                index = i;
            }

        for (int i = index; i <= this->size - 2; i++)
            this->elements[i] = this->elements[i + 1];

        this->size--;
        this->end--;
        return min;
    }
    else
    {
        for (int i = this->start; i <= this->size - 1; i++)
            if (this->elements[i] < min)
            {
                min = this->elements[i];
                index = i;
            }

        for (int i = 0; i <= this->end; i++)
            if (this->elements[i] < min)
            {
                min = this->elements[i];
                index = i;
            }

        for (int i = index; i <= this->size - 2; i++)
            this->elements[i] = this->elements[i + 1];

        this->start--;
        this->end--;
        this->size--;

        return min;
    }
}

/// BC = WC = T = Theta(1)
Queue::~Queue() {
	delete[] this->elements;
}

/// BC = Theta(1), WC = O(n)
void Queue::resize() {

    auto* temp_elements = new TElem[this->size * 2];
    int index = 0;

    if (this->start < this->end)
    {
        for(int i = this->start; i <= this->end; i++)
        {
            temp_elements[index] = this->elements[i];
            index++;
        }
        this->start = 0;
        this->end = index;
    }
    else
    {
        for(int i = this->start; i <= this->size - 1; i++)
        {
            temp_elements[index] = this->elements[i];
            index++;
        }

        for (int i = 0; i <= this->end; i++)
        {
            temp_elements[index] = this->elements[i];
            index++;
        }

        this->start = 0;
        this->end = index;
    }

    this->size *= 2;

    delete[] this->elements;
    this->elements = temp_elements;

}
