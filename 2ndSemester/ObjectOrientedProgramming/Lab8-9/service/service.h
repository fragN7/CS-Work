//
// Created by Alen on 16/03/2022.
//

#pragma once
#include <utility>
#include <algorithm>
#include "../repo/repository.h"
#include "../validation/validation.h"


class Event_Service {

private:
    Event_Repo* event_repo;
    Event_Validation event_validator;

public:
    /// Service constructor with inherited repo and validator
    /// \param event_repo Repo of events
    /// /// \param event_validator Validator of the event
    Event_Service(Event_Repo* event_repo, Event_Validation event_validator) : event_repo(event_repo), event_validator(event_validator){};

    /// Calls the repo and validator to add and validate the event
    /// \param link Link
    /// \param title Title
    /// \param description Description
    /// \param date_time Date and time
    /// \param people_number Number of people
    void add_event(std::string link, std::string title, std::string description, std::string date_time, unsigned int people_number);

    /// Removes the event by link, by calling the repo
    /// \param link Unique identifier
    void remove_event(const std::string& link);

    /// Updates and event by calling the repo
    /// \param link Link
    /// \param title Title
    /// \param description Description
    /// \param date_time Date and time
    /// \param people_number Number of people
    void update_event(std::string link, std::string title, std::string description, std::string date_time, unsigned int people_number);

    /// Populates the array with random valid events
    void populate_array();

    /// Getter for number of events for a given month
    /// \return Number of events for a given month
    unsigned int get_number_events_for_month(unsigned int month);

    /// Getter for number of events
    /// \return Number of events
    unsigned long long get_number_events();

    /// Sorts array by a certain function
    std::vector<Event> filter_array(unsigned int month);

    /// Returns the list of events
    /// \return List of events
    std::vector<Event> list_events();

    void add_to_generic_file(std::string file_name);
    void open_file(std::string file_name);

    void add_to_file(std::string file_name);
    void read_from_file(std::string file_name);
};