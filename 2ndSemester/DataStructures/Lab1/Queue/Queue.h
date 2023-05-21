#pragma once
#include <vector>
using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM (-11111)


class Queue
{
private:
	TElem* elements;
    int start, end, size;

    //resizes the array
    void resize();

public:
	Queue();

	//pushes an element to the end of the queue
	void push(TElem e);

	//returns the element from the front of the queue
	//throws exception if the queue is empty
	TElem top() const;

	//removes and returns the element from the front of the queue
	//throws exception if the queue is empty
	TElem pop();

    // removes and returns the smallest element in the queue
    // throws exception if the queue is empty
    TElem pop_minimum();

	//checks if the queue is empty
	bool isEmpty() const;

	// destructor
	~Queue();
};
