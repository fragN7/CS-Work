//
// Created by Alen on 16/03/2022.
//

#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "../errors/exceptions.h"


class Event {

private:

    std::string link;
    std::string description;
    std::string date_time;
    std::string title;
    unsigned int people_number{};

public:

    Event();
    ~Event();
    Event(std::string& link, std::string& title, std::string& description, std::string& date_time, unsigned int people_number);

    /// Link getter
    /// \return The object's link
    std::string get_link();

    /// Title getter
    /// \return The object's title
    std::string get_title();

    /// Description getter
    /// \return The object's description
    std::string get_description();

    /// Date and time getter
    /// \return The object's date and time
    std::string get_date_time();

    /// Month getter
    /// \return Month
    unsigned int get_month();

    /// Number people getter
    /// \return The object's number of people
    unsigned int get_people_number() const;

    /// Link setter for reading from a file
    /// \param new_link
    void set_link(std::string& new_link);

    /// Title setter
    /// \param new_title
    void set_title(std::string& new_title);

    /// Description setter
    /// \param new_description
    void set_description(std::string& new_description);

    /// Date and time setter
    /// \param new_date_time
    void set_date_time(std::string& new_date_time);

    /// Number of people setter
    /// \param new_people_number
    void set_people_number(unsigned int new_people_number);

    /// Pretty print
    /// \param outputStream The output pretty printed
    /// \param event_to_print Event object
    /// \return The pretty printed string
    friend std::ostream& operator<<(std::ostream &outputStream, const Event& event_to_print);

    /// Pretty read
    /// \param inputStream
    /// \param event_to_read
    /// \return The event
    friend std::istream& operator>>(std::istream &inputStream, Event& event_to_read);
};