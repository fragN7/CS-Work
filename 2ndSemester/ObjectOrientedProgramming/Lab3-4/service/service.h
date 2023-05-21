//
// Created by Alen on 02/03/2022.
//

#include "../repo/repository.h"
#include <time.h>
#pragma once

/// Check if the offer already exists, if not the offer is being added
/// \param dynamic_array - in which the offer is being added
/// \param type - string type
/// \param destination - string type
/// \param departure_date - string type
/// \param price - int type
/// \return 1 - the offer has been added, -1 - otherwise
int add_offer(Array *dynamic_array, char *type, char *destination, char *departure_date, int price);

/// Check if the offer already exists, if it exists the offer is being removed
/// \param dynamic_array - in which the offer is being added
/// \param destination - unique identifier
/// \param departure_date - unique identifier
/// \return 1 - the offer has been removed, -1 - otherwise
int delete_offer(Array *dynamic_array, char destination[], char departure_date[]);

/// Check if the offer already exists, if it exists the offer is being replaced
/// \param dynamic_array - in which the offer is being updated
/// \param type - string type
/// \param destination - string type
/// \param departure_date - string type
/// \param price - int type
/// \return 1 - the offer has been replaced, -1 - otherwise
int update_offer(Array *dynamic_array, char *type, char *destination, char *departure_date, int price);

/// Binary sorting an array by price ascending
/// \param copy_offer_repo - array which is being sorted
void sort_offers_price_asc(Array* copy_offer_repo);

/// Binary sorting an array by price descending
/// \param copy_offer_repo - array which is being sorted
void sort_offers_price_desc(Array* copy_offer_repo);

/// Binary sorting an array by destination ascending
/// \param copy_offer_repo - array which is being sorted
void sort_offers_destination(Array* copy_offer_repo);

/// Creates random valid characteristics / offers and add them to the array
/// \param offer_repo - array in which the offers are being added
void populate_array(Array* offer_repo);
