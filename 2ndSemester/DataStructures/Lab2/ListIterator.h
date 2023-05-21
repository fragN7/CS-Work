#pragma once
#include "IteratedList.h"

//DO NOT CHANGE THIS PART
class IteratedList;
typedef int TElem;

class ListIterator{
	friend class IteratedList;
private:
    IteratedList::Node* current;

	//DO NOT CHANGE THIS PART
	const IteratedList& list;
	explicit ListIterator(const IteratedList& list);

public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;

};


