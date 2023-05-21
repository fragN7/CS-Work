//
// Created by Alen on 11/03/2022.
//

#include "validation.h"


bool validate_type(char* type)
{
    if(strcmp(type, "seaside") == 0 || strcmp(type, "mountain") == 0 || strcmp(type, "city break") == 0)
        return true;
    return false;
}

bool validate_departure_date(char* departure_date)
{
    char new_departure_date[21];
    char day[21], month[21], year[21], *p;
    const char slash[2] = "/";
    int int_day, int_month, int_year;
    int slash_number = 0, count = 0;

    if (strlen(departure_date) != 8 && strlen(departure_date) != 9 && strlen(departure_date) != 10)
        return false;

    for(int j = 0; j <= strlen(departure_date) - 1; j++)
        if(departure_date[j] == '/')
            slash_number++;
    if (slash_number != 2)
        return false;


    strcpy(new_departure_date, departure_date);
    p = strtok(new_departure_date, slash);
    while(p != NULL)
    {
        if (count == 0)
            strcpy(day, p);
        else if (count == 1)
            strcpy(month, p);
        else if (count == 2)
            strcpy(year, p);
        count++;
        p = strtok(NULL, slash);
    }

    for(int i = 0; i <= strlen(day) - 1; i++)
        if (isalpha(day[i]))
            return false;
    int_day = atoi(day);

    if(int_day <= 0)
        return false;

    for(int i = 0; i <= strlen(month) - 1; i++)
        if(isalpha(month[i]))
            return false;
    int_month = atoi(month);

    for(int i = 0; i <= strlen(year) - 1; i++)
        if(isalpha(year[i]))
            return false;
    int_year = atoi(year);

    if(int_month <= 0 || int_month >= 13)
        return false;

    if(int_year % 4 == 0)
    {
        if(int_month == 2)
            if(int_day >= 30)
                return false;
    }
    else
        if(int_month == 2)
            if(int_day >= 29)
                return false;

    if(int_month == 1 || int_month == 3 || int_month == 5 || int_month == 7 || int_month == 8 || int_month == 10 || int_month == 12)
        if(int_day <= 0 || int_day >= 32)
            return false;

    if(int_month == 4 || int_month == 6 || int_month == 9 || int_month == 11)
        if(int_day <= 0 || int_day >= 31)
            return false;

    return true;
}

bool validate_after_date(char* normal_date, char* given_date)
{
    char new_normal_date[21];
    char new_normal_day[21], new_normal_month[21], new_normal_year[21], *p1, slash[2] = "/";
    int normal_day, normal_month, normal_year, count1 = 0;

    strcpy(new_normal_date, normal_date);
    p1 = strtok(new_normal_date, slash);
    while(p1 != NULL)
    {
        if (count1 == 0)
            strcpy(new_normal_day, p1);
        else if (count1 == 1)
            strcpy(new_normal_month, p1);
        else if (count1 == 2)
            strcpy(new_normal_year, p1);
        count1++;
        p1 = strtok(NULL, slash);
    }

    normal_day = atoi(new_normal_day);
    normal_month = atoi(new_normal_month);
    normal_year = atoi(new_normal_year);


    char new_given_date[21];
    char new_given_day[21], new_given_month[21], new_given_year[21], *p2;
    int given_day, given_month, given_year, count2 = 0;

    strcpy(new_given_date, given_date);
    p2 = strtok(new_given_date, slash);
    while(p2 != NULL)
    {
        if (count2 == 0)
            strcpy(new_given_day, p2);
        else if (count2 == 1)
            strcpy(new_given_month, p2);
        else if (count2 == 2)
            strcpy(new_given_year, p2);
        count2++;
        p2 = strtok(NULL, slash);
    }

    given_day = atoi(new_given_day);
    given_month = atoi(new_given_month);
    given_year = atoi(new_given_year);

    if(normal_year > given_year)
        return false;
    else if (normal_year < given_year)
        return true;
    else if (normal_year == given_year)
    {
        if (normal_month > given_month)
            return false;
        else if (normal_month < given_month)
            return true;
        else if (normal_month == given_month)
        {
            if (normal_day < given_day)
                return true;
        }
    }
    return false;
}

int validate_price(char* price)
{
    for(int i = 0; i <= strlen(price) - 1; i++)
        if(isdigit(price[i]) == 0)
            return -1;
    return atoi(price);
}