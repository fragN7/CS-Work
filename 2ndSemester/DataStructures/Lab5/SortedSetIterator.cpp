#include "SortedSetIterator.h"
#include <exception>
#include <iostream>

using namespace std;

/// O(n)
SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	this->stack = new Node*[multime.capacity];

    Node* new_node = multime.head;
    this->pos = -1;

    while(new_node != nullptr)
    {
        this->pos++;
        this->stack[this->pos] = new_node;
        new_node = new_node->left;
    }

    if(pos >= 0)
        this->node = this->stack[this->pos];
    else
        this->node = nullptr;
}

/// O(n)
void SortedSetIterator::first() {

    Node* new_node = multime.head;
    this->pos = -1;

    while(new_node != nullptr)
    {
        this->pos++;
        this->stack[this->pos] = new_node;
        new_node = new_node->left;
    }

    if(this->pos >= 0)
        this->node = this->stack[this->pos];
    else
        this->node = nullptr;
}

/// O(n)
void SortedSetIterator::next() {

    if(!this->valid())
        throw exception();

    Node* new_node = this->stack[this->pos];
    this->pos--;

    if(new_node->right != nullptr)
    {
        new_node = new_node->right;
        while(new_node != nullptr)
        {
            this->pos++;
            this->stack[this->pos] = new_node;
            new_node = new_node->left;
        }
    }

    if(this->pos >= 0)
        this->node = this->stack[this->pos];
    else
        this->node = nullptr;
}

/// Theta(1)
TElem SortedSetIterator::getCurrent()
{
	if(!this->valid())
        throw exception();
    return this->node->value;
}

/// Theta(1)
bool SortedSetIterator::valid() const {

    if(this->node == nullptr)
        return false;
    return true;
}

/// Theta(1)
void SortedSetIterator::previous() {

    if(!this->valid())
        throw exception();

    if(this->pos == -1)
        throw exception();

    this->pos++;
    this->node = this->stack[pos];
}

