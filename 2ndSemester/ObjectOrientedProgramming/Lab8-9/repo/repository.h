//
// Created by Alen on 16/03/2022.
//

#include <iostream>
#include <cstdlib>
#include "domain.h"
#include "../errors/exceptions.h"
#include "../array/Array.h"
#include <vector>
#pragma once


class Event_Repo{

protected:
    std::vector<Event> events;

private:

    /// Event finder by link
    /// \param link Unique identifier
    /// \return The event's index if it's found, -1 otherwise
    int find(const std::string& link);

public:

    /// Event Repo constructor
    /// \param dynamic_array Inherited from Array class
    Event_Repo() = default;

    /// Adds an event to the dynamic array
    /// \param event Event to be added
    void add(Event event);

    /// Removes an event from the dynamic array
    /// \param link Link from the event to be removed
    void remove(const std::string& link);

    /// Updates and event from the dynamic array
    /// \param event The new event
    void update(Event event);

    /// Number of events getter
    /// \return Number of events
    unsigned long long get_event_number();

    /// All events getter
    /// \return All events
    std::vector<Event> get_all_events();

    Event& operator[](int index) {return events[index];}

    virtual void file_write(std::string file_name){};
    virtual void file_write_txt(std::string file_name);
    virtual void file_read(std::string file_name){};
    virtual void file_read_txt(std::string file_name);
    virtual void file_open(const std::string file_name){};
};

class Event_CSV_Repo : public Event_Repo {

public:
    void file_write(std::string file_name) override;
    void file_read(std::string file_name) override;
    void file_open(std::string file_name) override;
};

class Event_HTML_Repo : public Event_Repo {

public:

    void file_write(std::string file_name) override;
    void file_open(std::string file_name) override;
};
