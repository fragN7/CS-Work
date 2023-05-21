//
// Created by Alen on 16/03/2022.
//

#pragma once
#include <string>
#include <cstring>
#include "../errors/exceptions.h"

class Event_Validation {

private:

    /// Title Validation
    /// \param title Title
    static void validate_title(const std::string& title);

    /// Description validator
    /// \param description Description
    static void validate_description(const std::string& description);

    /// Date and time validator
    /// \param date_time Date and time
    static void validate_date_time(const std::string& date_time);

public:

    /// Link validator (ID)
    /// \param link Link
    static void validate_link(std::string link);

    /// Event Validator (Whole event)
    /// \param link Link
    /// \param title Title
    /// \param description Description
    /// \param date_time Date and time
    static void validate_event(std::string link, const std::string& title, const std::string& description, const std::string& date_time);

};
