//
// Created by Alen on 16/03/2022.
//

#include <windows.h>
#include <fstream>
#include "repository.h"
#include "../validation/validation.h"


int Event_Repo::find(const std::string& link) {

    std::vector<Event> the_events = this->events;
    for (auto& event : the_events)
    {
        if(event.get_link() == link)
            return &event - &the_events[0];
    }
    return -1;
}

void Event_Repo::add(Event event)
{
    if(find(event.get_link()) != -1)
        throw RepoError("Event already exists");
    this->events.push_back(event);

    ///this->dynamic_array + event;
    ///this->dynamic_array = event + this->dynamic_array;
}

void Event_Repo::remove(const std::string& link) {

    int index = find(link);
    if (index == -1)
        throw RepoError("Event doesn't exist");
    this->events.erase(this->events.begin() + index);

}

void Event_Repo::update(Event event) {

    int index = find(event.get_link());
    if (index == -1)
        throw RepoError("Event doesn't exist");
    this->events[index] = event;

}

std::vector<Event> Event_Repo::get_all_events() {

    return this->events;
}

unsigned long long Event_Repo::get_event_number() {

    return this->events.size();
}

void Event_Repo::file_write_txt(std::string file_name) {

    std::ofstream file;
    file.open(file_name, std::ofstream::out | std::ofstream::trunc);
    file.close();
    file.open(file_name);
    for(auto& event: events) {
        file << event;
    }
    file.close();
}

void Event_Repo::file_read_txt(std::string file_name) {

    std::ifstream file;
    file.open(file_name);

    this->events.clear();

    Event event;
    while(file >> event)
        this->add(event);

    file.close();
}

void Event_CSV_Repo::file_write(std::string file_name) {

    std::ofstream file;
    file.open(file_name, std::ofstream::out | std::ofstream::trunc);
    file.close();
    file.open(file_name);

    for(auto& event : this->events)
        file << event;

    file.close();
}

void Event_CSV_Repo::file_read(std::string file_name) {

    std::ifstream file;
    file.open(file_name);

    this->events.clear();

    Event event;
    while(file >> event)
        this->add(event);

    file.close();
}

void Event_CSV_Repo::file_open(const std::string file_name) {

    std::string path = "notepad \"" + file_name + "\"";
    system(path.c_str());
}

void Event_HTML_Repo::file_write(std::string file_name) {

    std::ofstream file;
    file.open(file_name, std::ofstream::out | std::ofstream::trunc);
    file.close();
    file.open(file_name);

    file << "<!DOCTYPE html> \n";
    file << "<html> \n";
    file << "<head> \n";
    file << "<title>Events</title> \n";
    file << "</head> \n";
    file << "<body> \n";
    file << "<table border=1> \n";
    file << "<tr> \n";
    file << "<td>Link</td> \n";
    file << "<td>Title</td> \n";
    file << "<td>Description</td> \n";
    file << "<td>Date & Time</td> \n";
    file << "<td>Number of people</td> \n";
    file << "</tr> \n";

    for (auto& event : this->events){
        file << "<tr>\n";
        file << "<td><a href=\"" << event.get_link() << "\">Link</a></td> \n";
        file << "<td>\n" << event.get_title() <<"</td> \n";
        file << "<td>\n" << event.get_description() <<"</td> \n";
        file << "<td>\n" << event.get_date_time() <<"</td> \n";
        file << "<td>\n" << event.get_people_number() <<"</td> \n";
        file << "</tr>\n";
    }

    file << "</table>";
    file << "</body>";
    file << "</html> \n";
}

void Event_HTML_Repo::file_open(const std::string file_name) {

    ShellExecute(nullptr, "open", file_name.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}