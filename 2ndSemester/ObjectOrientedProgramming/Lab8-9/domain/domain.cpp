//
// Created by Alen on 16/03/2022.
//

#include "domain.h"
#include <iostream>
#include <string>

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

void Event::set_link(std::string &new_link) {
    this->link = new_link;
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

std::istream &operator>>(std::istream &inputStream, Event& event_to_read) {

    if (inputStream.eof())
        inputStream.setstate(std::ios_base::failbit);
    else
    {
        std::getline(inputStream, event_to_read.link, '|');
        //event_to_read.link.erase(std::remove(event_to_read.link.begin(), event_to_read.link.end(), ' '), event_to_read.link.end());

        std::getline(inputStream, event_to_read.title, '|');
        //event_to_read.title.erase(std::remove(event_to_read.title.begin(), event_to_read.title.end(), ' '), event_to_read.title.end());

        std::getline(inputStream, event_to_read.description, '|');
        //event_to_read.description.erase(std::remove(event_to_read.description.begin(), event_to_read.description.end(), ' '), event_to_read.description.end());

        std::getline(inputStream, event_to_read.date_time, '|');
        //event_to_read.date_time.erase(std::remove(event_to_read.date_time.begin(), event_to_read.date_time.end(), ' '), event_to_read.date_time.end());

        std::string people_number;
        std::getline(inputStream, people_number, '\n');
        //people_number.erase(std::remove(people_number.begin(), people_number.end(), ' '), people_number.end());

        event_to_read.set_people_number(std::stoi(people_number));
    }
    return inputStream;
}