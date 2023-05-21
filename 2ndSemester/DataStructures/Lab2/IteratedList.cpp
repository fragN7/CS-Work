#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"
#include <iostream>

/// BC = WC = T = Theta(1)
IteratedList::IteratedList() {

	this->capacity = 0;
    this->head = nullptr;
}

/// BC = WC = T = Theta(1)
int IteratedList::size() const {

	return this->capacity;
}

/// BC = WC = T = Theta(1)
bool IteratedList::isEmpty() const {

    if(this->capacity == 0)
        return true;
	return false;
}

/// BC = WC = T = Theta(1)
ListIterator IteratedList::first() const {
	ListIterator it(*this);
    return it;
}

/// BC = WC = T = Theta(1)
TElem IteratedList::getElement(ListIterator pos) {

    return pos.getCurrent();
}

/// BC = Theta(1), WC = T = O(n)
TElem IteratedList::remove(ListIterator& pos) {

    if(!pos.valid())
        throw std::exception();

    TElem temp_element = this->getElement(pos);
    Node* current = this->head;

    if(pos.getCurrent() == 0)
        this->head = this->head->next;
    else if (pos.getCurrent() == this->size())
    {
        while (current->next != nullptr)
            current = current->next;
        current->next = nullptr;
    }
    else
    {
        while(current->next != pos.current)
            current = current->next;
        current->next = current->next->next;
    }

    this->capacity--;
    return temp_element;
}

/// BC = WC = T = Theta(1)
ListIterator IteratedList::search(TElem e) const{

    ListIterator it(*this);

    it.first();
    try {
        while(it.getCurrent() != e)
            it.next();
    }
    catch (std::exception &){};

    return it;
}

/// BC = WC = T = Theta(1)
TElem IteratedList::setElement(ListIterator pos, TElem e) {

    if(!pos.valid())
        throw std::exception();

    TElem temp = pos.getCurrent();
    Node* current = pos.current;
    current->data = e;

	return temp;
}

/// BC = WC = T = Theta(1)
void IteratedList::addToBeginning(TElem e) {

    this->capacity++;
    Node* first = new Node;
    first->data = e;
    first->next = this->head;
    this->head = first;
}

/// BC = WC = T = Theta(1)
void IteratedList::addToPosition(ListIterator& pos, TElem e) {

    if(!pos.valid())
        throw std::exception();

    Node* current = pos.current;

    Node* new_node = new Node;
    new_node->data = e;
    new_node->next = current->next;
    current->next = new_node;

    this->capacity++;
}

/// BC = Theta(1), WC = T = O(n)
void IteratedList::addToEnd(TElem e) {

    Node* current = this->head;
    if (this->capacity != 0)
    {
        while (current->next != nullptr)
            current = current->next;

        Node *new_node = new Node;
        new_node->data = e;
        new_node->next = nullptr;
        current->next = new_node;
    }
    else
    {
        Node *new_node = new Node;
        new_node->data = e;
        new_node->next = nullptr;
        this->head = new_node;
    }
    this->capacity++;
}

ListIterator IteratedList::lastIndexOf(TElem elem) const {

    ListIterator it(*this);

    Node* current = this->head;

    while(current->next != nullptr)
    {
        if(current->data == elem)
        {
            it.current->data = elem;
            it.current->next = current->next;
        }
        current = current->next;
    }
    return it;
}

/*void IteratedList::print_list() {

    ListIterator it(*this);
    it.first();
    std::cout << it.getCurrent() << "\n";
    for(int i = 0; i <= this->capacity - 2; i++)
    {
        it.next();
        std::cout << it.getCurrent() << std::endl;
    }

    std::cout << std::endl;
}*/

/// BC = WC = T = Theta(1)
IteratedList::~IteratedList() = default;
