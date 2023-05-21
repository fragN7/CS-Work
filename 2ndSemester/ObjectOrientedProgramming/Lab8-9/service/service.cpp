//
// Created by Alen on 16/03/2022.
//

#include "service.h"

#include <utility>


void Event_Service::add_event(std::string link, std::string title, std::string description, std::string date_time, unsigned int people_number) {

    Event event(link, title, description, date_time, people_number);
    this->event_validator.validate_event(link, title, description, date_time);
    this->event_repo->add(event);
}

void Event_Service::remove_event(const std::string& link) {

    this->event_validator.validate_link(link);
    this->event_repo->remove(link);
}

void Event_Service::update_event(std::string link, std::string title, std::string description, std::string date_time, unsigned int people_number) {

    Event event(link, title, description, date_time, people_number);
    this->event_validator.validate_event(link, title, description, date_time);
    this->event_repo->update(event);
}

std::vector<Event> Event_Service::list_events() {
    return this->event_repo->get_all_events();
}

unsigned long long Event_Service::get_number_events() {
    return this->event_repo->get_event_number();
}

unsigned int Event_Service::get_number_events_for_month(unsigned int month) {

    unsigned int number_of_events = 0;
    std::vector<Event> events = this->event_repo->get_all_events();
    for (auto& event: events)
        if(event.get_month() == month)
            number_of_events++;

    return number_of_events;
}

void Event_Service::populate_array() {

    std::string link[12] = {"https://neversea.com", "https://tomorrowland.com", "https://untold.com", "https://youtube.com",
                            "https://musicfinland.com","https://arsenal.com","https://nba.com","https://fifa.com",
                            "https://rocnation.com","https://eminem.com", "https://thebeatles.com", "https://steveaoki.com"};
    std::string title[12] = {"Chain-Smokers", "Eminem", "50 Cent", "Dr.Dre",
                             "Avicii", "Busta Rhymes", "KSI", "2 Chainz",
                             "Thor", "Iron Man", "Ramen Noodles", "Lionel Messi"};
    std::string description[5] = {"Music", "Arts", "Sports", "Group","Reggae"};
    std::string date_time[8] = {"20/03/2022 17:52", "30/09/2002 23:00", "18/09/2002 11:00", "30/06/2023 20:45",
                                "06/07/2022 18:15","05/03/1953 21:50", "14/12/1799 13:13", "01/01/2022 00:00"};
    unsigned int link_index, title_index, description_index, date_time_index, price;
    srand(time(nullptr));
    while(this->event_repo->get_event_number() != 10)
    {
        link_index = rand() % 12;
        title_index = rand() % 12;
        description_index = rand() % 5;
        date_time_index = rand() % 8;
        price = rand() % 1000;
        try{
            add_event(link[link_index], title[title_index], description[description_index], date_time[date_time_index], price);
        }
        catch (RepoError& repo_error) {}
    }
}

std::vector<Event> Event_Service::filter_array(unsigned int month) {

    std::vector<Event> events = this->event_repo->get_all_events();
    std::vector<Event> new_events;
    std::copy_if(events.begin(), events.end(), std::back_inserter(new_events), [&month](auto the_event){return the_event.get_month() == month;});

    return new_events;
}

void Event_Service::add_to_file(std::string file_name) {

    this->event_repo->file_write_txt(std::move(file_name));
}

void Event_Service::add_to_generic_file(std::string file_name) {

    this->event_repo->file_write(std::move(file_name));
}

void Event_Service::open_file(std::string file_name) {

    this->event_repo->file_open(std::move(file_name));
}

void Event_Service::read_from_file(std::string file_name) {

    this->event_repo->file_read_txt(std::move(file_name));
}



