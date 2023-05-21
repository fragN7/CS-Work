//
// Created by Alen on 16/03/2022.
//

#include "repository.h"


int Event_Repo::find(const std::string& link) {

    for(int i = 0; i < this->dynamic_array.get_size(); i++)
        if(this->dynamic_array.elements[i].get_link() == link)
            return i;
    return -1;
}

void Event_Repo::add(Event event)
{
    if(find(event.get_link()) != -1)
        throw RepoError("Event already exists");
    this->dynamic_array.append_array(event);
    ///this->dynamic_array + event;
    ///this->dynamic_array = event + this->dynamic_array;
}

void Event_Repo::remove(const std::string& link) {

    int index = find(link);
    if (index == -1)
        throw RepoError("Event doesn't exist");
    this->dynamic_array.remove_array(index);
}

void Event_Repo::update(Event event) {

    int index = find(event.get_link());
    if (index == -1)
        throw RepoError("Event doesn't exist");
    this->dynamic_array.update_array(index, event);
}

Event* Event_Repo::get_all_events() {

    return this->dynamic_array.get_all_elements();
}

int Event_Repo::get_event_number() {
    return this->dynamic_array.get_size();
}


