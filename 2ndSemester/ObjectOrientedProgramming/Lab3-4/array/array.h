///
/// Created by Alen on 02/03/2022.
///

#include "../domain/domain.h"
#include <stdlib.h>
#pragma once


typedef void* Element;
typedef void(*destroy_function)(Element);
typedef Element(*copy_function)(Element);

typedef struct{
    Element* elements;
    int size, capacity;
    destroy_function destroy_function;
    copy_function copy_function;
}Array;

/// Creates the a dynamic array of size and capacity, having the type of element TElem (Offers and other arrays)
/// \param capacity - capacity of the array (initially is 1)
/// \param destroy_function - free method having a pointer to void, int order to 'destroy' any type
/// \param copy_function - copy method of type Element for copying any type TElem
/// \return The created array
Array* create_array(int capacity, destroy_function destroy_function, copy_function copy_function);

/// Destroys the dynamic array, including all it's elements and functions / deallocates the memory
/// \param dynamic_array - to be destroyed
void destroy_array(Array* dynamic_array);

/// The capacity doubles everytime the size has reached the capacity / reallocates the memory by destroying it and
/// allocating it afterwards
/// \param dynamic_array - to be resized if the size reaches the capacity
void resize_array(Array* dynamic_array);

/// Allocating the same size, capacity and elements, including it's destroy and copy functions, used for copying the
/// element's characteristics
/// \param dynamic_array - of which the copy is made
/// \return A copy of the array
Array* copy_array(Array* dynamic_array);
