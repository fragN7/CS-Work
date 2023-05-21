#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <vector>

using namespace std;


/// Theta(1)
MultiMap::MultiMap() {

    this->length = 0;
    this->capacity = 3;
    this->first_empty = 0;
    this->head = this->tail = -1;
    this->next = new int[this->capacity];

    for(int i = 0; i < this->capacity; i++)
        this->next[i] = i + 1;

    this->next[this->capacity] = -1;
    this->array = new MainNode[this->capacity];
}

void MultiMap::init_node(MultiMap::MainNode& node) {

    node.capacity_slla = 3;
    node.length_slla = 0;
    node.first_empty = 0;
    node.head = -1;
    node.tail = -1;
    node.next = new int[4];

    for(int i = 0; i < node.capacity_slla; i++)
        node.next[i] = i + 1;

    node.next[node.capacity_slla] = -1;

    node.slla_elem = new TValue[3];
}

/// O(n) - all values
void MultiMap::add(TKey c, TValue v) {

    int position, value;

    if(this->length == 0)
    {
        this->init_node(this->array[this->first_empty]);
        this->array[this->first_empty].key = c;
        this->array[this->first_empty].head = this->array[this->first_empty].first_empty;
        this->array[this->first_empty].tail = this->array[this->first_empty].head;
        this->array[this->first_empty].slla_elem[this->array[this->first_empty].first_empty] = v;
        this->array[this->first_empty].first_empty = this->array[this->first_empty].next[this->array[this->first_empty].first_empty];
        this->array[this->first_empty].length_slla += 1;

        this->head = this->first_empty;
        this->tail = this->first_empty;
        this->first_empty = this->next[this->first_empty];
    }
    else
    {
       position = this->head;
       while(position != this->first_empty && this->array[position].key != c)
           position = this->next[position];

       // key not in map
       if(position == this->first_empty)
       {
           // resize
           if(this->next[this->first_empty] == -1)
           {
               int *new_next = new int[this->capacity * 2 + 1];
               auto *new_array = new MainNode[this->capacity * 2];

               for (int i = 0; i < this->capacity; i++) {
                   new_next[i] = this->next[i];
                   new_array[i] = this->array[i];
               }

               for (int i = this->capacity; i < this->capacity * 2; i++)
                   new_next[i] = i + 1;

               new_next[this->capacity * 2] = -1;
               delete[] this->next;
               delete this->array;

               this->next = new_next;
               this->capacity *= 2;
               this->array = new_array;
           }

           this->init_node(this->array[this->first_empty]);
           this->array[this->first_empty].key = c;
           this->array[this->first_empty].head = this->array[this->first_empty].first_empty;
           this->array[this->first_empty].tail = this->array[this->first_empty].head;
           this->array[this->first_empty].slla_elem[this->array[this->first_empty].first_empty] = v;
           this->array[this->first_empty].first_empty = this->array[this->first_empty].next[this->array[this->first_empty].first_empty];
           this->array[this->first_empty].length_slla += 1;
       }
       else
       {
           if(this->array[position].length_slla == this->array[position].capacity_slla)
           {
                int* new_slla_next = new int[this->array[position].capacity_slla * 2 + 1];
                auto* new_slla_elem = new TValue[this->array[position].capacity_slla*2];

                for(int i = 0; i < this->array[position].capacity_slla; i++)
                {
                    new_slla_next[i] = this->array[position].next[i];
                    new_slla_elem[i] = this->array[position].slla_elem[i];
                }

                for(int i = this->array[position].capacity_slla; i < this->array[position].capacity_slla*2;i++)
                    new_slla_next[i] = i + 1;

                new_slla_next[this->array[position].capacity_slla * 2] = -1;
                delete[] this->array[position].next;
                this->array[position].next = new_slla_next;

                delete[] this->array[position].slla_elem;
                this->array[position].slla_elem = new_slla_elem;
                this->array[position].capacity_slla *= 2;
           }
           this->array[position].slla_elem[this->array[position].first_empty] = v;
           this->array[position].length_slla += 1;
           this->array[position].tail = this->array[position].first_empty;
           this->array[position].first_empty = this->array[position].next[this->array[position].first_empty];
       }
    }
    this->length++;
}

/// O(n) -all main nodes
bool MultiMap::remove(TKey c, TValue v) {

    int pos, value_pos, prev_pos, prev_value_pos;
    TValue null_value = NULL_TVALUE;

    if(this->length == 0)
        return false;

    prev_pos = -2;
    pos = this->head;

    while(pos != this->first_empty && this->array[pos].key != c)
    {
        prev_pos = pos;
        pos = this->next[pos];
    }

    if(pos == this->first_empty)
        return false;

    value_pos = this->array[pos].head;
    prev_value_pos = -2;

    while(value_pos != this->array[pos].first_empty && this->array[pos].slla_elem[value_pos] != v)
    {
        prev_value_pos = value_pos;
        value_pos = this->array[pos].next[value_pos];
    }

    if(value_pos == this->array[pos].first_empty)
        return false;

    this->array[pos].length_slla -= 1;
    this->length -= 1;

    if(this->array[pos].head == value_pos)
    {
        if(this->array[pos].length_slla == 0)
        {
            delete[] this->array[pos].next;
            delete[] this->array[pos].slla_elem;

            this->array[pos].head = -1;
            this->array[pos].tail = -1;
            this->array[pos].first_empty = value_pos;

            if(pos == this->head)
            {
                if(this->length == 0)
                {
                    this->next[pos] = this->first_empty;
                    this->first_empty = pos;
                    this->head = -1;
                    this->tail = -1;
                }
                else
                {
                    this->head = this->next[pos];
                    this->next[pos] = this->first_empty;
                    this->next[this->tail] = pos;
                    this->first_empty = pos;
                }
            }
            else
            {
                if(this->next[pos] != this->first_empty)
                {
                    this->next[prev_pos] = this->next[pos];
                    this->next[this->tail] = pos;
                }
                else
                    this->tail = prev_pos;

                this->next[pos] = this->first_empty;
                this->first_empty = pos;
            }
        }
        else
        {
            this->array[pos].head = this->array[pos].next[value_pos];
            this->array[pos].next[value_pos] = this->array[pos].first_empty;
            this->array[pos].next[this->array[pos].tail] = value_pos;
            this->array[pos].first_empty = value_pos;
        }
    }
    else
    {
        if(this->array[pos].next[value_pos] != this->array[pos].first_empty)
        {
            this->array[pos].next[prev_value_pos] = this->array[pos].next[value_pos];
            this->array[pos].next[this->array[pos].tail] = value_pos;
        }
        else
            this->array[pos].tail = prev_value_pos;

        this->array[pos].next[value_pos] = this->array[pos].first_empty;
        this->array[pos].first_empty = value_pos;
    }

    return true;
}

/// O(n) - size of sll of the key
vector<TValue> MultiMap::search(TKey c) const {

    std::vector<TValue> temp_elements;
    int position, value;

    if(this->length == 0)
        return {};

    position = this->head;
    while(position != this->first_empty && this->array[position].key != c)
        position = this->next[position];

    if(position != this->first_empty)
    {
        value = this->array[position].head;
        while(value != this->array[position].first_empty)
        {
            temp_elements.push_back(this->array[position].slla_elem[value]);
            value = this->array[position].next[value];
        }
    }

    return temp_elements;
}

/// Theta(1)
int MultiMap::size() const {

	return this->length;
}

/// Theta(1)
bool MultiMap::isEmpty() const {

	if(this->length == 0)
        return true;
    return false;
}

/// Theta(1)
MultiMapIterator MultiMap::iterator() {
	return MultiMapIterator(*this);
}

/// Theta(1)
MultiMap::~MultiMap() {

    for(int i = this->head; i != this->first_empty && i != -1; i = this->next[i])
    {
        if(this->array[i].length_slla != 0)
        {
            delete[] this->array[i].slla_elem;
            delete[] this->array[i].next;
        }
    }

    delete[] this->array;
    delete[] this->next;
}


