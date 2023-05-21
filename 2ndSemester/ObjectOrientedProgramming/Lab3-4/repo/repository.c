//
// Created by Alen on 02/03/2022.
//

#include "repository.h"

int find(char offer_destination[], char offer_departure_date[], Array* dynamic_array)
{
    for (int i = 0; i < dynamic_array->size; i++)
        if (strcmp(get_destination(dynamic_array->elements[i]), offer_destination) == 0 && strcmp(get_departure_date(dynamic_array->elements[i]), offer_departure_date) == 0)
            return i;
    return -1;
}

void add(Element element, Array* dynamic_array)
{
    if(dynamic_array->size == dynamic_array->capacity)
        resize_array(dynamic_array);
    dynamic_array->elements[dynamic_array->size++] = dynamic_array->copy_function(element);
}

int delete(char offer_destination[], char offer_departure_date[], Array* dynamic_array)
{
    int index = find(offer_destination, offer_departure_date, dynamic_array);
    if (index == -1)
        return -1;
    destroy_offer(dynamic_array->elements[index]);
    for (int i = index; i < dynamic_array->size - 1; i++)
        dynamic_array->elements[i] = dynamic_array->elements[i + 1];
    dynamic_array->size--;
    return 1;
}

void update(Offer* offer, Array* dynamic_array, int index)
{
    destroy_offer(dynamic_array->elements[index]);
    dynamic_array->elements[index] = copy_offer(offer);
}
