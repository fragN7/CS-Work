//
// Created by Alen on 16/03/2022.
//

#include "domain.h"

Event::Event() = default;

Event::Event(std::string& link, std::string& title, std::string& description, std::string& date_time, unsigned int people_number)
{
    this->link = link;
    this->title = title;
    this->description = description;
    this->date_time = date_time;
    this->people_number = people_number;
}

Event::~Event() = default;

std::string Event::get_title() {
    return title;
}

std::string Event::get_description() {
    return description;
}

std::string Event::get_date_time() {
    return date_time;
}

unsigned int Event::get_month() {

    std::string new_month;
    char first_month, second_month;

    first_month = date_time[3];
    second_month = date_time[4];

    if (first_month == '0')
        return second_month - '0';

    new_month[0] = first_month;
    new_month[1] = second_month;

    return stoi(new_month);
}

std::string Event::get_link() {
    return link;
}

unsigned int Event::get_people_number() const {
    return people_number;
}

void Event::set_title(std::string &new_title) {
    this->title = new_title;
}

void Event::set_description(std::string &new_description) {
    this->description = new_description;
}

void Event::set_date_time(std::string &new_date_time) {
    this->date_time = new_date_time;
}

void Event::set_people_number(unsigned int new_people_number) {
    this->people_number = new_people_number;
}

std::ostream &operator<<(std::ostream &output, const Event &event_to_print) {

    output << event_to_print.link << " | " << event_to_print.title << " | " << event_to_print.description << " | " << event_to_print.date_time << " | " << event_to_print.people_number << "\n";
    return output;
}
