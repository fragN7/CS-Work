//
// Created by Alen on 11/03/2022.
//
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma once

/// Type validator
/// \param type - string type
/// \return True if type is seaside, mountain or city break, False otherwise
bool validate_type(char* type);

/// Departure date validator
/// \param departure_date - string type
/// \return True if departure date is a valid date, False otherwise
bool validate_departure_date(char* departure_date);

/// After date validator
/// \param normal_date - the date of an offer
/// \param given_date - the given date
/// \return True if the given date is before the date of an offer, False otherwise
bool validate_after_date(char* normal_date, char* given_date);

/// Price validator
/// \param price - string type
/// \return Price of type integer
int validate_price(char* price);
