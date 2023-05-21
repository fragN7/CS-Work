#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

/// O(n + m^2)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {

    // copy elements of hash table in array
    this->copy_elements = new TComp[b.length];
    int k = 0;
    for(int i = 0; i < this->bag.capacity; i++)
    {
        struct Node* current_node = this->bag.node[i];
        while(current_node != nullptr)
        {
            this->copy_elements[k] = current_node->elem;
            k++;
            current_node = current_node->next;
        }
    }

    // sort it
    for(int i = 0; i < this->bag.length - 1; i++)
        for(int j = i + 1; j < this->bag.length; j++)
            if(this->bag.relation(this->copy_elements[i], this->copy_elements[j]))
            {
                int aux = copy_elements[i];
                copy_elements[i] = copy_elements[j];
                copy_elements[j] = aux;
            }

    this->copy_current_pos = 0;

    // initialize hash table iterator
    int first_elem = this->copy_elements[0];
    this->current_pos = this->bag.hash(first_elem);

    this->element = this->bag.node[this->current_pos];
}

/// O(n)
TComp SortedBagIterator::getCurrent() {

    if(!this->valid())
        throw std::exception();

    this->current_pos = this->bag.hash(this->copy_elements[this->copy_current_pos]);
    struct Node* current_node = this->bag.node[this->current_pos];

    while(current_node != nullptr && this->copy_elements[this->copy_current_pos] != current_node->elem)
        current_node = current_node->next;

    this->element = current_node;

    return this->element->elem;
}

/// Theta(1)
bool SortedBagIterator::valid() const {

    if(this->copy_current_pos == this->bag.length)
        return false;
    return true;
}

/// O(n)
void SortedBagIterator::next() {

    if(!this->valid())
        throw std::exception();

    this->copy_current_pos++;

    if(this->copy_elements[this->copy_current_pos] == this->copy_elements[this->copy_current_pos - 1])
        this->element = this->element->next;
    else
    {
        this->current_pos = this->bag.hash(this->copy_elements[this->copy_current_pos]);
        struct Node* current_node = this->bag.node[this->current_pos];

        while(current_node != nullptr && this->copy_elements[this->copy_current_pos] != current_node->elem)
            current_node = current_node->next;

        this->element = current_node;
    }
}

/// Theta(1)
void SortedBagIterator::first() {

    this->copy_current_pos = 0;

    int first_elem = this->copy_elements[0];
    this->current_pos = first_elem % this->bag.length;
    this->element = this->bag.node[this->current_pos];
}

/// Theta(1)
void SortedBagIterator::previous() {

    if(!this->valid())
        throw std::exception();

    if(this->copy_current_pos == 0)
        throw std::exception();

    this->copy_current_pos--;

    int the_element = this->copy_elements[this->copy_current_pos];
    this->current_pos = the_element % this->bag.length;
    this->element = this->bag.node[this->current_pos];
}

