//
// Created by Alen on 16/03/2022.
//

#include <iostream>
#include <cstdlib>
#include "domain.h"
#include "../errors/exceptions.h"
#include "../array/Array.h"
#pragma once


class Event_Repo{

private:
    Array <Event> dynamic_array;

    /// Event finder by link
    /// \param link Unique identifier
    /// \return The event's index if it's found, -1 otherwise
    int find(const std::string& link);

public:

    /// Event Repo constructor
    /// \param dynamic_array Inherited from Array class
    explicit Event_Repo(const Array <Event>& dynamic_array) : dynamic_array{ dynamic_array } {};

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
    int get_event_number();

    /// All events getter
    /// \return All events
    Event* get_all_events();
};