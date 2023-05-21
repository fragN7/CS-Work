#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& multime;
	explicit SortedSetIterator(const SortedSet& m);

	Node** stack;
    Node* node;
    int pos;

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
    void previous();
};

