#pragma once
#include "MultiMap.h"

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;

class MultiMap;

class MultiMapIterator
{
    friend class MultiMap;


private:
    explicit MultiMapIterator(MultiMap &c);
    MultiMap& c;

    int current_key, current_element;

public:
    TElem getCurrent();
	bool valid() const;
	void next();
	void first();
};
