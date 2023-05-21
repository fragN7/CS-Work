//
// Created by Alen on 02/03/2022.
//

#include "domain.h"


Offer * create_offer(char* type, char* destination, char* departure_date, int price)
{
    Offer* offer = (Offer*)malloc(sizeof(Offer));

    offer->type = malloc(sizeof(char) * (strlen(type) + 1));
    strcpy(offer->type, type);

    offer->destination = malloc(sizeof(char) * (strlen(destination) + 1));
    strcpy(offer->destination, destination);

    offer->departure_date = malloc(sizeof(char) * (strlen(departure_date) + 1));
    strcpy(offer->departure_date, departure_date);

    offer->price = price;

    return offer;
}

char * get_type(Offer * offer)
{
    return offer->type;
}

char * get_destination(Offer * offer)
{
    return offer->destination;
}

char * get_departure_date(Offer * offer)
{
    return offer->departure_date;
}

int get_price(Offer * offer)
{
    return offer->price;
}

void destroy_offer(Offer* offer_to_destroy)
{
    if(offer_to_destroy == NULL)
        return;

    free(offer_to_destroy->type);
    free(offer_to_destroy->destination);
    free(offer_to_destroy->departure_date);
    free(offer_to_destroy);
}

Offer* copy_offer(Offer* offer_to_copy)
{
    Offer* offer_copy = (Offer*)malloc(sizeof(Offer));

    offer_copy->type = malloc(sizeof(char)*(strlen(offer_to_copy->type)+1));
    strcpy(offer_copy->type, offer_to_copy->type);

    offer_copy->destination = malloc(sizeof(char)*(strlen(offer_to_copy->destination)+1));
    strcpy(offer_copy->destination, offer_to_copy->destination);

    offer_copy->departure_date = malloc(sizeof(char)*(strlen(offer_to_copy->departure_date)+1));
    strcpy(offer_copy->departure_date, offer_to_copy->departure_date);

    offer_copy->price = offer_to_copy->price;

    return offer_copy;
}

void to_str(Offer* print_offer, char *offer)
{
    char price[41];
    strcpy(offer, print_offer->type);
    strcat(offer, " ");

    strcat(offer, print_offer->destination);
    strcat(offer, " ");

    strcat(offer, print_offer->departure_date);
    strcat(offer, " ");

    sprintf(price, "%d", print_offer->price);
    strcat(offer, price);

    strcat(offer, "\n");
}
