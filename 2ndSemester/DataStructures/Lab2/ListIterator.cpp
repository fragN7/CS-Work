#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>

/// All operations perform on constant time

ListIterator::ListIterator(const IteratedList& list) : list(list) {

	this->current = list.head;
}

void ListIterator::first() {

	this->current = this->list.head;
}

void ListIterator::next() {

    if(!this->valid())
        throw std::exception();

    if (this->current != nullptr)
        this->current = this->current->next;
}

bool ListIterator::valid() const {

    if(this->current != nullptr)
        return true;
    return false;
}

TElem ListIterator::getCurrent() const {

    if(!this->valid())
        throw std::exception();

    return this->current->data;
}
