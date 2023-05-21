#include <valarray>
#include "SortedBag.h"
#include "SortedBagIterator.h"

/// Theta(n) - number of positions
SortedBag::SortedBag(Relation r) {

    this->capacity = 601;
    this->length = 0;
    this->node = new struct Node*[this->capacity];
    for(int i = 0; i < this->capacity; i++)
        this->node[i] = nullptr;

    this->relation = r;
}

/// O(n^3 + m^2) n - elements, m - length of sll
void SortedBag::resize() {

    auto* temp_elements = new TComp[this->length];

    // save elements from old hash table to temp_elements
    int k = 0;
    for(int i = 0; i < this->capacity; i++)
    {
        struct Node* current = this->node[i];
        while(current != nullptr)
        {
            temp_elements[k] = current->elem;
            k++;
            current = current->next;
        }
    }

    // delete old hash and every element
    for(int i = 0; i < this->capacity; i++)
    {
        struct Node* current = this->node[i];
        while(current != nullptr)
        {
            struct Node* next = current->next;
            delete current;
            current = next;
        }
    }

    delete[] this->node;

    // create a new hash with double capacity
    this->capacity *= 2;
    this->length = 0;
    this->node = new struct Node*[this->capacity];

    for(int i = 0; i < this->capacity; i++)
        this->node[i] = nullptr;

    //re-hash
    for(int i = 0; i < k; i++)
        this->add(temp_elements[i]);

    delete[] temp_elements;
}

/// O(n)
void SortedBag::add(TComp e) {

    TComp pos = this->hash(e);
    auto load_factor = this->length/this->capacity;

    if(load_factor >= 1)
        this->resize();

    auto* new_node = new struct Node;
    new_node->elem = e;

    struct Node* current = this->node[pos];
    struct Node* prev = nullptr;

    while(current != nullptr && !this->relation(e, current->elem))
    {
        prev = current;
        current = current->next;
    }

    if(prev == nullptr) // add at beginning
    {
        new_node->next = this->node[pos];
        this->node[pos] = new_node;
    }
    else // otherwise
    {
        new_node->next = current;
        prev->next = new_node;
    }

    this->length++;
}

/// O(n)
bool SortedBag::remove(TComp e) {

    TComp pos = this->hash(e);

    struct Node* current = this->node[pos];
    struct Node* prev = nullptr;

    while(current != nullptr && e != current->elem)
    {
        prev = current;
        current = current->next;
    }

    if(current != nullptr)
    {
        if(prev == nullptr) // delete head
            this->node[pos] = this->node[pos]->next;
        else
            prev->next = current->next;

        this->length--;
        return true;
    }

    return false;
}

/// O(n)
bool SortedBag::search(TComp e)  {

    TComp pos = this->hash(e);
    struct Node* current = this->node[pos];

    while(current != nullptr && current->elem != e)
        current = current->next;

    if(current != nullptr)
        return true;

    return false;
}

/// O(n)
int SortedBag::nrOccurrences(TComp e)  {

    TComp pos = this->hash(e);
    struct Node* current = this->node[pos];

    while(current != nullptr && current->elem != e)
        current = current->next;

    int count = 0;
    while(current != nullptr && e == current->elem) //sorted so every element is next to each other
    {
        count++;
        current = current->next;
    }

    return count;
}

/// Theta(n)
int SortedBag::size() const  {

    return this->length;
}

/// Theta(n)
bool SortedBag::isEmpty() const {

    if(this->length == 0)
        return true;
    return false;
}

/// Theta(1)
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

/// O(n + m)
SortedBag::~SortedBag() {

    for(int i = 0; i < this->capacity/2; i++)
    {
        struct Node* current = this->node[i];
        while(current != nullptr)
        {
            struct Node* next_node = current->next;
            delete current;
            current = next_node;
        }
    }

    delete[] this->node;
}

/// Theta(1)
TComp SortedBag::hash(TComp e) const {

    int result = e % this->capacity;

    if (e < 0)
        return result + this->capacity;
    return result;
}
