//
// Created by Alen on 02/03/2022.
//

#include "ui.h"


int ui_add(Array *offer_repo)
{
    char type[21], destination[21], departure_date[21], price[21];
    int result;

    while(true)
    {
        printf("Type (seaside, mountain or city break):\n");
        gets(type);
        if (validate_type(type))
            break;
        else
        {
            printf("Invalid type\n");
            type[0] = '\0';
        }
    }

    printf("Destination:\n");
    gets(destination);

    while(true)
    {
        printf("Departure date (d/m/y):\n");
        gets(departure_date);
        if(validate_departure_date(departure_date))
            break;
        else
        {
            printf("Invalid departure date\n");
            departure_date[0] = '\0';
        }
    }

    int new_price;
    while(true)
    {
        printf("Price:\n");
        gets(price);
        new_price = validate_price(price);
        if(new_price != -1)
            break;
        else
        {
            price[0] = '\0';
            printf("Invalid price\n");
        }
    }
    result = add_offer(offer_repo, type, destination, departure_date, new_price);
    return result;
}

int ui_delete(Array *offer_repo)
{
    char destination[21], departure_date[21];
    int result;

    printf("Destination:\n");
    gets(destination);

    while(true)
    {
        printf("Departure date (d/m/y):\n");
        gets(departure_date);
        if(validate_departure_date(departure_date))
            break;
        else
        {
            printf("Invalid departure date\n");
            departure_date[0] = '\0';
        }
    }

    result = delete_offer(offer_repo, destination, departure_date);
    return result;
}

int ui_update(Array *offer_repo)
{
    char type[21], destination[21], departure_date[21], price[21];
    int result;

    while(true)
    {
        printf("Type (seaside, mountain or city break):\n");
        gets(type);
        if (validate_type(type))
            break;
        else
        {
            printf("Invalid type\n");
            type[0] = '\0';
        }
    }

    printf("Destination:\n");
    gets(destination);

    while(true)
    {
        printf("Departure date (d/m/y):\n");
        gets(departure_date);
        if(validate_departure_date(departure_date))
            break;
        else
        {
            printf("Invalid departure date\n");
            departure_date[0] = '\0';
        }
    }

    int new_price;
    while(true)
    {
        printf("Price:\n");
        gets(price);
        new_price = validate_price(price);
        if(new_price != -1)
            break;
        else
        {
            price[0] = '\0';
            printf("Invalid price\n");
        }
    }

    result = update_offer(offer_repo, type, destination, departure_date, new_price);
    return result;
}

void ui_list(Array* offer_repo)
{
    char offer[51];
    if(offer_repo->size == 0)
        printf("No offers in list\n");
    else
        for(int i = 0; i <= offer_repo->size - 1; i++)
        {
            to_str(offer_repo->elements[i], offer);
            printf("%s", offer);
        }
}

void call(void (*sort_function)(), Array* offer_repo)
{
    sort_function(offer_repo);
}

void ui_list_string(Array* offer_repo)
{
    char offer[51], destination_string[21];
    if(offer_repo->size == 0)
        printf("No offers in list\n");
    else
    {
        Array* copy_offer_repo = copy_array(offer_repo);
        call(sort_offers_price_desc, copy_offer_repo);
        ///call(sort_offers_price_asc, copy_offer_repo);

        ///printf("Please enter a destination:\n");
        ///gets(destination_string);

        char price[21];
        int start_price;
        while(true)
        {
            printf("Please enter a starting price:\n");
            gets(price);
            start_price = validate_price(price);
            if(start_price != -1)
                break;
            else
            {
                price[0] = '\0';
                printf("Invalid price\n");
            }
        }
        start_price = atoi(price);

        price[0] = '\0';
        int end_price;
        while(true)
        {
            printf("Please enter a ending price:\n");
            gets(price);
            end_price = validate_price(price);
            if(end_price != -1)
                break;
            else
            {
                price[0] = '\0';
                printf("Invalid price\n");
            }
        }
        end_price = atoi(price);

        for (int i = 0; i <= copy_offer_repo->size - 1; i++)
            ///if(strstr(get_destination(copy_offer_repo->elements[i]), destination_string))
            if(start_price <= get_price(copy_offer_repo->elements[i]) &&  get_price(copy_offer_repo->elements[i]) <= end_price)
            {
                to_str(copy_offer_repo->elements[i], offer);
                printf("%s", offer);
            }
        destroy_array(copy_offer_repo);
    }
}

void ui_list_sorted(Array* offer_repo)
{
    char offer[51];
    if(offer_repo->size == 0)
        printf("No offers in list\n");
    else
    {
        Array* copy_offer_repo = copy_array(offer_repo);
        call(sort_offers_destination, copy_offer_repo);
        for (int i = 0; i <= copy_offer_repo->size - 1; i++)
        {
            to_str(copy_offer_repo->elements[i], offer);
            printf("%s", offer);
        }
        destroy_array(copy_offer_repo);
    }
}

void ui_list_type(Array* offer_repo)
{
    char type[21], departure_date[21], offer[41], choice[21];

    if(offer_repo->size == 0)
        printf("No offers in list\n");
    else
    {
        while (true)
        {
            printf("Please chose ascending/descending sorting:\n");
            gets(choice);
            if (!strcmp(choice, "ascending") || !strcmp(choice, "descending"))
                break;
            else
            {
                printf("Invalid choice\n");
                choice[0] = '\0';
            }
        }

        while (true)
        {
            printf("Type (seaside, mountain or city break):\n");
            gets(type);
            if (validate_type(type))
                break;
            else
            {
                printf("Invalid type\n");
                type[0] = '\0';
            }
        }

        while (true)
        {
            printf("Departure date (d/m/y):\n");
            gets(departure_date);
            if (validate_departure_date(departure_date))
                break;
            else
            {
                printf("Invalid departure date\n");
                departure_date[0] = '\0';
            }
        }
        Array* copy_offer_repo = copy_array(offer_repo);

        if (!strcmp(choice, "ascending"))
            call(sort_offers_price_asc, copy_offer_repo);
        else
            call(sort_offers_price_desc, copy_offer_repo);

        for (int i = 0; i <= copy_offer_repo->size - 1; i++)
            if (strcmp(get_type(copy_offer_repo->elements[i]), type) == 0 &&
                !validate_after_date(get_departure_date(copy_offer_repo->elements[i]), departure_date))
            {
                to_str(copy_offer_repo->elements[i], offer);
                printf("%s", offer);
            }
        destroy_array(copy_offer_repo);
    }
}

void print_menu()
{
    printf("\nWelcome employers of 'Happy Holidays'!!!\n");
    printf("Here are your options:\n");
    printf("-------------------------\n");
    printf("'add': Add an offer\n");
    printf("'delete': Remove an offer\n");
    printf("'update': Update an offer\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("'list': List all offers\n");
    printf("'list string': List all offers containing a given string/have a price in a given range, sorted ascending by price\n");
    printf("'list type': List all offers containing a given type, after a given departure date, sorted by your choice\n");
    printf("'list sorted': List all offers, sorted ascending by destination\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("'undo': Undo previous action\n");
    printf("'redo': Redo previous action\n");
    printf("----------------------------\n");
    printf("'exit': Exit\n");
}

void run(Array* offer_repo, Array* undo_redo_repo)
{
    print_menu();
    populate_array(offer_repo);
    add(offer_repo, undo_redo_repo);
    int undo_redo_index = 0, result;
    while(true)
    {
        char command[101];
        Array* auxiliary_array = undo_redo_repo->copy_function(undo_redo_repo->elements[undo_redo_index]);

        printf("Please enter your option:\n");
        gets(command);
        if (!strcmp(command, "add"))
        {
            command[0] = '\0';
            result = ui_add(auxiliary_array);
            if (result == -1)
                printf("Offer already exists\n");
            add(auxiliary_array, undo_redo_repo);
            undo_redo_index = undo_redo_repo->size - 1;
        }
        else if (!strcmp(command, "delete"))
        {
            command[0] = '\0';
            result = ui_delete(auxiliary_array);
            if (result == -1)
                printf("Offer doesn't exist\n");
            add(auxiliary_array, undo_redo_repo);
            undo_redo_index = undo_redo_repo->size - 1;
        }
        else if (!strcmp(command, "update"))
        {
            command[0] = '\0';
            result = ui_update(auxiliary_array);
            if (result == -1)
                printf("Offer doesn't exist\n");
            add(auxiliary_array, undo_redo_repo);
            undo_redo_index = undo_redo_repo->size - 1;
        }
        else if (!strcmp(command, "list"))
        {
            command[0] = '\0';
            ui_list(auxiliary_array);
        }
        else if (!strcmp(command, "list string"))
        {
            command[0] = '\0';
            ui_list_string(auxiliary_array);
        }
        else if (!strcmp(command, "list sorted"))
        {
            command[0] = '\0';
            ui_list_sorted(auxiliary_array);
        }
        else if (!strcmp(command, "list type"))
        {
            command[0] = '\0';
            ui_list_type(auxiliary_array);
        }
        else if (!strcmp(command, "undo"))
        {
            command[0] = '\0';
            if (undo_redo_index > 0)
                undo_redo_index--;
            else
                printf("Can not undo\n");
        }
        else if (!strcmp(command, "redo"))
        {
            command[0] = '\0';
            if (undo_redo_index < undo_redo_repo->size - 1)
                undo_redo_index++;
            else
                printf("Can not redo\n");
        }
        else if (!strcmp(command, "exit"))
        {
            destroy_array(auxiliary_array);
            return;
        }
        else
        {
            command[0] = '\0';
            printf("Invalid operation\n");
        }
        destroy_array(auxiliary_array);
    }
}
