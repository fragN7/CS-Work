//
// Created by Alen on 02/03/2022.
//

#include "array.h"

Array* create_array(int capacity, destroy_function destroy_function, copy_function copy_function)
{
    Array* dynamic_array = (Array*)malloc(sizeof(Array));
    dynamic_array->capacity = capacity;
    dynamic_array->size = 0;
    dynamic_array->elements = (Element*)malloc(sizeof(Element)*capacity);

    dynamic_array->destroy_function = destroy_function;
    dynamic_array->copy_function = copy_function;

    return dynamic_array;
}

void destroy_array(Array* dynamic_array)
{
    if(dynamic_array == NULL)
        return;
    if(dynamic_array->elements == NULL)
    {
        free(dynamic_array);
        return;
    }
    for(int i = 0; i < dynamic_array->size; i++)
    {
        if (dynamic_array->elements[i] != NULL)
            dynamic_array->destroy_function(dynamic_array->elements[i]);
    }
    free(dynamic_array->elements);
    free(dynamic_array);
}

void resize_array(Array* dynamic_array)
{
    dynamic_array->capacity *= 2;
    Element* new_elements = (Element*)malloc(sizeof(Element)*dynamic_array->capacity);
    for(int i = 0; i < dynamic_array->size; i++)
        new_elements[i] = dynamic_array->elements[i];
    free(dynamic_array->elements);
    dynamic_array->elements = new_elements;
}

Array* copy_array(Array* dynamic_array)
{
    Array* new_dynamic_array = (Array*)malloc(sizeof(Array));

    new_dynamic_array->capacity = dynamic_array->capacity;
    new_dynamic_array->size = dynamic_array->size;
    new_dynamic_array->elements = (Element*)malloc(sizeof(Element)*dynamic_array->capacity);

    new_dynamic_array->destroy_function = dynamic_array->destroy_function;
    new_dynamic_array->copy_function = dynamic_array->copy_function;

    for(int i = 0; i < dynamic_array->size; i++)
        new_dynamic_array->elements[i] = dynamic_array->copy_function(dynamic_array->elements[i]);

    return new_dynamic_array;
}
