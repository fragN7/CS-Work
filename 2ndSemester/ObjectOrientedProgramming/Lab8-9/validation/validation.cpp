//
// Created by Alen on 16/03/2022.
//

#include "validation.h"


void Event_Validation::validate_link(const std::string& link) {

    if (link.empty())
        throw ValidError("Invalid link");
    if (link[0] != 'h' && link[1] != 't' && link[2] != 't' && link[3] != 'p' && link[4] != 's' && link[5] != ':' && link[6] != '/' && link[7] != '/')
        throw ValidError("Invalid link");
}

void Event_Validation::validate_title(const std::string& title) {

    if (title.empty())
        throw ValidError("Invalid title");
}

void Event_Validation::validate_description(const std::string& description) {

    if (description.empty())
        throw ValidError("Invalid title");
}

void Event_Validation::validate_date_time(const std::string& date_time) {

    if(date_time.empty())
        throw ValidError("Invalid date and time");

    if(date_time.length() != 16)
        throw ValidError("Invalid date and time");

    std::string date, time;
    size_t s = date_time.find(' ');

    date = date_time;
    date.erase(s, date.length());

    if(date.length() != 10)
        throw ValidError("Invalid date");

    if(date[2] != '/' && date[5] != '/')
        throw ValidError("Invalid date");

    if(date[0] != '0' && date[0] != '1' && date[0] != '2' && date[0] != '3')
        throw ValidError("Invalid date");

    if(std::isalpha(date[1]))
        throw ValidError("Invalid date");

    if(date[3] != '0' && date[3] != '1')
        throw ValidError("Invalid date");

    if(std::isalpha(date[4]))
        throw ValidError("Invalid date");

    if(std::isalpha(date[6]) || std::isalpha(date[7]) || std::isalpha(date[8]) || std::isalpha(date[9]))
        throw ValidError("Invalid date");

    time = date_time;
    time.erase(0, s + 1);

    if(time[2] != ':')
        throw ValidError("Invalid time");

    if(time[0] != '0' && time[0] != '1' && time[0] != '2')
        throw ValidError("Invalid time");

    if(std::isalpha(time[1]))
        throw ValidError("Invalid time");

    if(time[3] < '0' || time[3] > '5')
        throw ValidError("Invalid time");

    if(std::isalpha(time[4]))
        throw ValidError("Invalid time");
}

void Event_Validation::validate_event(const std::string& link, const std::string& description, const std::string& title, const std::string& date_time) {

    std::string err;

    try {
        validate_link(link);
    }
    catch (ValidError &ve) {
        err += ve.get_message();
        err += "\n";
    }

    try {
        validate_title(title);
    }
    catch (ValidError &ve) {
        err += ve.get_message();
        err += "\n";
    }

    try {
        validate_description(description);
    }
    catch (ValidError &ve) {
        err += ve.get_message();
        err += "\n";
    }

    try {
        validate_date_time(date_time);
    }
    catch (ValidError &ve) {
        err += ve.get_message();
    }

    if (!err.empty())
        throw ValidError(err);
}