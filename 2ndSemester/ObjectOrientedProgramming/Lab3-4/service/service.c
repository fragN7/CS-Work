//
// Created by Alen on 02/03/2022.
//

#include "service.h"

int add_offer(Array * offer_repo, char *type, char *destination, char *departure_date, int price)
{
    if(find(destination, departure_date, offer_repo) != -1)
        return -1;

    Offer *offer = create_offer(type, destination, departure_date, price);
    add(offer, offer_repo);
    destroy_offer(offer);

    return 1;
}

int delete_offer(Array *offer_repo, char destination[], char departure_date[])
{
    return delete(destination, departure_date, offer_repo);
}

int update_offer(Array *offer_repo, char* type, char* destination, char* departure_date, int price)
    {
    int index = find(destination, departure_date, offer_repo);
    if (index == -1)
        return -1;
    Offer* offer = create_offer(type, destination, departure_date, price);
    update(offer, offer_repo, index);
    destroy_offer(offer);
    return 1;
}

void sort_offers_price_asc(Array* copy_offer_repo)
{
    int i, j;
    for (i = 0; i < copy_offer_repo->size - 1; i++)
        for (j = i + 1; j < copy_offer_repo->size; j++)
            if (get_price(copy_offer_repo->elements[i]) > get_price(copy_offer_repo->elements[j]))
            {
                Offer* aux;
                aux = copy_offer_repo->copy_function(copy_offer_repo->elements[i]);
                copy_offer_repo->destroy_function(copy_offer_repo->elements[i]);
                copy_offer_repo->elements[i] = copy_offer_repo->copy_function(copy_offer_repo->elements[j]);
                copy_offer_repo->destroy_function(copy_offer_repo->elements[j]);
                copy_offer_repo->elements[j] = copy_offer_repo->copy_function(aux);
                copy_offer_repo->destroy_function(aux);
            }
}
void sort_offers_price_desc(Array* copy_offer_repo)
{
    int i, j;
    for (i = 0; i < copy_offer_repo->size - 1; i++)
        for (j = i + 1; j < copy_offer_repo->size; j++)
            if (get_price(copy_offer_repo->elements[i]) < get_price(copy_offer_repo->elements[j]))
            {
                Offer* aux;
                aux = copy_offer_repo->copy_function(copy_offer_repo->elements[i]);
                copy_offer_repo->destroy_function(copy_offer_repo->elements[i]);
                copy_offer_repo->elements[i] = copy_offer_repo->copy_function(copy_offer_repo->elements[j]);
                copy_offer_repo->destroy_function(copy_offer_repo->elements[j]);
                copy_offer_repo->elements[j] = copy_offer_repo->copy_function(aux);
                copy_offer_repo->destroy_function(aux);
            }
}

void sort_offers_destination(Array* copy_offer_repo)
{
    int i, j;
    for (i = 0; i < copy_offer_repo->size - 1; i++)
        for (j = i + 1; j < copy_offer_repo->size; j++)
            if (strcmp(get_destination(copy_offer_repo->elements[i]), get_destination(copy_offer_repo->elements[j])) > 0)
            {
                Offer* aux;
                aux = copy_offer_repo->copy_function(copy_offer_repo->elements[i]);
                copy_offer_repo->destroy_function(copy_offer_repo->elements[i]);
                copy_offer_repo->elements[i] = copy_offer_repo->copy_function(copy_offer_repo->elements[j]);
                copy_offer_repo->destroy_function(copy_offer_repo->elements[j]);
                copy_offer_repo->elements[j] = copy_offer_repo->copy_function(aux);
                copy_offer_repo->destroy_function(aux);
            }
}

void populate_array(Array* offer_repo)
{
    char types[3][11] = {"seaside", "mountain", "city break"};
    char destinations[7][11] = {"Milano", "New York", "London", "Birmingham", "Kiev", "Miami", "Lima"};
    char departure_dates[9][11] = {"28/3/2022", "8/3/2022", "30/9/2002", "12/9/2002", "15/8/2021", "13/8/2023", "1/1/1998", "26/5/2030", "28/2/2018"};
    int type_index, destination_index, departure_date_index, price, result;
    srand(time(NULL));
    for(int i = 0; i < 10; i++)
    {
        type_index = rand() % 3;
        destination_index = rand() % 7;
        departure_date_index = rand() % 9;
        price = rand() % 1000;
        result = add_offer(offer_repo, types[type_index], destinations[destination_index], departure_dates[departure_date_index], price);
        if(result == -1)
            i--;
    }
}
