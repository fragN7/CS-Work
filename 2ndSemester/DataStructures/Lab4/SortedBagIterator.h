#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	explicit SortedBagIterator(const SortedBag& b);

	int current_pos, copy_current_pos;
    struct Node* element;
    TComp* copy_elements;

public:
	TComp getCurrent();
	bool valid() const;
	void next();
	void first();
    void previous();
};

