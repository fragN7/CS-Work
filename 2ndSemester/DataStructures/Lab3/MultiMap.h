#pragma once
#include <vector>
#include <utility>
#include "MultiMapIterator.h"

//ADT MultiMap–using a SLLA with unique keys. Every key will be associated with a SLLA of the values belonging to that key
//DO NOT INCLUDE MultiMapIterator


//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE (-111111)
#define NULL_TELEM pair<int,int>(-111111, -111111)
class MultiMapIterator;


class MultiMap
{
	friend class MultiMapIterator;

private:

    struct MainNode{
        TValue* slla_elem;
        int* next;
        int length_slla, capacity_slla, first_empty, head, tail;
        TKey key;
    };

    MainNode* array;
    int* next;
    int length, capacity, first_empty, head, tail;
    void init_node(MultiMap::MainNode& node);

public:
	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	std::vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator();

    //removes all elements from the multi map
    void empty();

	//destructor
	~MultiMap();

};



