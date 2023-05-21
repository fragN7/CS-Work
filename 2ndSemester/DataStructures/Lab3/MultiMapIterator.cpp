#include "MultiMapIterator.h"
#include <stdexcept>


MultiMapIterator::MultiMapIterator(MultiMap &c) : c(c) {

    this->current_key = this->c.head;
    this->current_element = -1;
    if(this->current_key != -1)
        this->current_element = this->c.array[this->current_key].head;
}

/// Theta(1)
TElem MultiMapIterator::getCurrent(){

    if(!this->valid())
        throw std::invalid_argument("");

    TElem elem;
    elem.first = this->c.array[this->current_key].key;
    elem.second = this->c.array[this->current_key].slla_elem[this->current_element];
    return elem;
}

/// Theta(1)
bool MultiMapIterator::valid() const {

    if(this->current_key != this->c.first_empty && this->current_key != -1)
        return true;
    return false;
}

/// Theta(1)
void MultiMapIterator::next() {

    if(!this->valid())
        throw std::invalid_argument("");

    if(this->c.array[this->current_key].next[this->current_element] != this->c.array[this->current_key].first_empty)
        this->current_element = this->c.array[this->current_key].next[this->current_element];
    else
    {
        this->current_key = this->c.next[this->current_key];
        if(this->current_key != this->c.first_empty)
            this->current_element = this->c.array[this->current_key].head;
        else
            this->current_element = -1;
    }
}

/// Theta(1)
void MultiMapIterator::first() {

    this->current_key = this->c.head;
    this->current_element = -1;
    if(this->current_key != -1)
        this->current_element = this->c.array[this->current_key].head;
}

