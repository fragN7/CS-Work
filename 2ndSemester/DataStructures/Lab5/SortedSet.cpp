#include <exception>
#include "SortedSet.h"
#include "SortedSetIterator.h"

/// Theta(1)
SortedSet::SortedSet(Relation r) {

    this->head = nullptr;
    this->capacity = 0;
    this->relation = r;
}

/// O(n)
bool SortedSet::add(TComp elem) {

    auto* new_node = new Node;

    new_node->value = elem;
    new_node->left = nullptr;
    new_node->right = nullptr;

    if(this->head == nullptr)
    {
        this->head = new_node;
        this->capacity++;
        return true;
    }

    Node* current_node = this->head;

    while(current_node != nullptr)
    {
        if(current_node->value == elem)
            return false;

        if(this->relation(current_node->value, new_node->value) && current_node->right != nullptr)
            current_node = current_node->right;
        else if(this->relation(current_node->value, new_node->value))
        {
            current_node->right = new_node;
            this->capacity++;
            return true;
        }
        else if(this->relation(new_node->value, current_node->value) && current_node->left != nullptr)
            current_node = current_node->left;
        else if(this->relation(new_node->value, current_node->value))
        {
            current_node->left = new_node;
            this->capacity++;
            return true;
        }
    }

	return false;
}

/// O(n)
bool SortedSet::remove(TComp elem) {

    Node* current_node = this->head;
    Node* parent_node = this->head;

    bool found = false;
    while(current_node != nullptr && !found)
    {
        if(current_node->value == elem)
            found = true;
        else if(this->relation(current_node->value, elem))
        {
            parent_node = current_node;
            current_node = current_node->right;
        }
        else
        {
            parent_node = current_node;
            current_node = current_node->left;
        }
    }

    if(!found)
        return false;

    this->capacity--;
    if(current_node == this->head)
    {
        if(current_node->left == nullptr && current_node->right != nullptr)
            this->head = this->head->right;
        else if(current_node->left != nullptr && current_node->right == nullptr)
            this->head = this->head->left;
        else if(current_node->left != nullptr && current_node->right != nullptr)
        {
            Node* min_node = this->head->right;
            Node* parent_min = this->head;

            while(min_node->left != nullptr)
            {
                parent_min = min_node;
                min_node = min_node->right;
            }

            this->head->value = min_node->value;
            if(parent_min == this->head)
                this->head->right = nullptr;
            else
                parent_min->left = nullptr;
        }
        else // element is the only one
        {
            this->head = nullptr;
            this->capacity = 0;
        }
    }
    else
    {
        if(current_node->left == nullptr && current_node->right == nullptr)
        {
            if(parent_node->right == current_node)
                parent_node->right = nullptr;
            else
                parent_node->left = nullptr;
        }
        else if(current_node->left == nullptr && current_node->right != nullptr)
            parent_node->right = current_node->right;
        else if(current_node->left != nullptr && current_node->right == nullptr)
            parent_node->left = current_node->left;
        else
        {
            Node* min_node = current_node->right;
            Node* parent_min = current_node;

            while(min_node->left != nullptr)
            {
                parent_min = min_node;
                min_node = min_node->left;
            }

            current_node->value = min_node->value;
            parent_min->left = nullptr;

            if(parent_min == current_node)
                current_node->right = nullptr;
            else
                parent_min->left = nullptr;
        }
    }

    return true;
}

/// O(n)
bool SortedSet::search(TComp elem) const {

    Node* current_node = this->head;
    while(current_node != nullptr)
    {
        if(current_node->value == elem)
            return true;

        if(this->relation(current_node->value, elem))
            current_node = current_node->right;
        else
            current_node = current_node->left;
    }

	return false;
}

/// Theta(1)
int SortedSet::size() const {

	return this->capacity;
}

/// Theta(1)
bool SortedSet::isEmpty() const {

	return this->capacity == 0;
}

/// Theta(1)
SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}

bool SortedSet::is_subset(SortedSet &s) const {

    SortedSetIterator subset_iterator = s.iterator();
    SortedSetIterator set_iterator = this->iterator();

    while(set_iterator.getCurrent() != subset_iterator.getCurrent())
        set_iterator.next();

    while(set_iterator.getCurrent() == subset_iterator.getCurrent() && subset_iterator.valid() && set_iterator.valid())
    {
        try{
            set_iterator.next();
            subset_iterator.next();
        if(set_iterator.getCurrent() != subset_iterator.getCurrent())
            return false;
        }
        catch(std::exception){return true;}
    }

    return true;
}

/// O(n)
SortedSet::~SortedSet() {

    Node** stack = new Node*[this->capacity];
    int pos = -1;

    Node* node = this->head;

    while(node != nullptr)
    {
        if (node->right != nullptr) {
            pos++;
            stack[pos] = node->right;
        }

        pos++;
        stack[pos] = node;
        node = node->left;
    }

    while (pos >= 0)
    {
        node = stack[pos];
        pos--;
        if (pos >= 0 && node->right == stack[pos])
        {
            stack[pos] = node;
            node = node->right;
        }
        else
        {
            delete node;
            node = nullptr;
        }

        while (node != nullptr)
        {
            if (node->right != nullptr)
            {
                pos++;
                stack[pos] = node->right;
            }

            pos++;
            stack[pos] = node;
            node = node->left;
        }
    }
}
