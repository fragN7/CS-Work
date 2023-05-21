//
// Created by Alen on 02/03/2022.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#pragma once


typedef struct{
    char *type;
    char *destination;
    char *departure_date;
    int price;
}Offer;

/// Creates an entity of type Offer of the below characteristics
/// \param type - seaside, mountain or city break
/// \param destination - any string is allowed
/// \param departure_date - of format dd/mm/yyyy / d/m/yyyy
/// \param price - any integer is allowed
/// \return An entity of type Offer
Offer* create_offer(char* type, char* destination, char* departure_date, int price);

/// Getter for the type
/// \param offer - whose offer the type it's extracted
/// \return Type of the offer entity (seaside, mountain or city break)
char* get_type(Offer* offer);

/// Getter for the destination
/// \param offer - whose offer the destination it's extracted
/// \return Destination of the offer entity
char* get_destination(Offer* offer);

/// Getter for the departure date
/// \param offer - whose offer the departure_date it's extracted
/// \return Departure date of the offer entity
char* get_departure_date(Offer* offer);

/// Getter for the price
/// \param offer - whose offer the price it's extracted
/// \return Price of the offer entity
int get_price(Offer* offer);

/// Destroys the offer including it's characteristics / Deallocating the memory
/// \param offer_to_destroy - to be destroyed
void destroy_offer(Offer* offer_to_destroy);

/// Allocating the same characteristics of the offer to the copy
/// \param offer_to_copy - of which the copy is made
/// \return A copy of the offer
Offer* copy_offer(Offer* offer_to_copy);

/// Transforms the offer's characteristics into a string type
/// \param print_offer - offer whose characteristics are being used
/// \param offer_list - the string in which it's pretty printed the offer
void to_str(Offer* print_offer, char offer_list[]);
