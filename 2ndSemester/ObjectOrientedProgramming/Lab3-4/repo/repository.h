//
// Created by Alen on 02/03/2022.
//

#include "../domain/domain.h"
#include "../array/array.h"
#include <string.h>
#pragma once

/*
typedef struct{
    int size, capacity;
    Offer* offers;
}OfferRepo;
*/

/// Find function to check if an offer is already in the repo
/// \param offer_destination - string type (identifier)
/// \param offer_departure_date - string type (identifier)
/// \param offer_repo - the repository of the offer's
/// \return 1 - if the offer is in the repo, -1 - otherwise
int find(char offer_destination[], char offer_departure_date[], Array* dynamic_array);

/// Add function to add in the array
/// \param element - element to be added
/// \param offer_repo - repository in which the element is added
void add(Element element, Array* dynamic_array);

/// Delete function to delete a certain element in the array
/// \param offer_destination - string type (identifier)
/// \param offer_departure_date - string type (identifier)
/// \param offer_repo - the repo in which the element is removed from
/// \return 1 - if the element has been removed, -1 - otherwise
int delete(char offer_destination[], char offer_departure_date[], Array* dynamic_array);

/// Update function to update a certain element in the array, delete and add (with the same identifier)
/// \param offer - offer that is added
/// \param offer_repo - the repo in which the element is added
/// \param index - the index of the element that is going to be updated/replaced
void update(Offer* offer, Array* dynamic_array, int index);
