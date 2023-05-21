/*
//
// Created by Alen on 16/03/2022.
//

#pragma once
#include <string>

/// Created a templated class for the dynamic array
/// \tparam Element Any type of element
template <class Element>
class Array {
private:

    int size{}, capacity{};
    void resize_array();

public:

    Element *elements;

    explicit Array(int capacity = 10);

    Array(const Array &copy_array);

    ~Array();

    void append_array(const Element &element_to_add);

    void operator+(const Element &element_to_add) {
        if (this->size == this->capacity)
            this->resize_array();
        this->elements[this->size++] = element_to_add;
    }

    void remove_array(int index);
    void update_array(int index, const Element& element_to_update);
    int get_size() const;
    Element* get_all_elements() const;
};

///  Constructor class
/// \tparam Element Any type of element
/// \param capacity Max size of array
template <class Element>
Array<Element>::Array(int capacity) {

    this->size = 0;
    this->capacity = capacity;
    this->elements = new Element[capacity];
}

/// Array setter
/// \tparam Element Any type of element
/// \param copy_array Copy of the array
template <class Element>
Array<Element>::Array(const Array& copy_array) {

    this->size = copy_array.size;
    this->capacity = copy_array.capacity;
    this->elements = new Element[this->capacity];

    for(int i = 0; i < this->size; i++)
        this->elements[i] = copy_array.elements[i];
}

/// Destructor class
/// \tparam Element Any type of element
template <class Element>
Array<Element>::~Array() {

    delete[] elements;
}

/// Add function, adds the element at the end of the array
/// \tparam Element Any type of element
/// \param element_to_add Element to be added
template <class Element>
void Array<Element>::append_array(const Element &element_to_add) {

    if (this->size == this->capacity)
        this->resize_array();
    this->elements[this->size++] = element_to_add;
}

///  Remove function, removes the element at the given index
/// \tparam Element Any type of element
/// \param index The index of the element who is going to be removed
template <class Element>
void Array<Element>::remove_array(int index) {
    this->size--;
    for (int i = index; i < this->size; i++)
        this->elements[i] = this->elements[i+1];
}

/// Update function, changes the element at the given index with the given element
/// \tparam Element Any type of element
/// \param index The position of the element who is going to be updated
/// \param element_to_update Element which is replacing the current element
template <class Element>
void Array<Element>::update_array(int index, const Element &element_to_update) {

    this->elements[index] = element_to_update;
}

/// Getter for the size of the array
/// \tparam Element Any type of element
/// \return Size of the array
template <class Element>
int Array<Element>::get_size() const {

    return this->size;
}

/// Getter for all elements in the array
/// \tparam Element Any type of element
/// \return The elements of the array
template <class Element>
Element* Array<Element>::get_all_elements() const {

    return this->elements;
}

/// Resize function if the size reaches the capacity, the capacity increases
/// \tparam Element Any type of element
template <class Element>
void Array<Element>::resize_array() {

    this->capacity *=static_cast<int>(2);

    auto* copy_elements = new Element[this->capacity];
    for(int i = 0; i < this->size; i++)
        copy_elements[i] = this->elements[i];

    delete[] this->elements;
    this->elements = copy_elements;
}

template <class Element>
Array<Element>& operator+(Element event, Array<Element>& dynamic_array) {
    dynamic_array.append_array(event);
    return dynamic_array;
}*/
