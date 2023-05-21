//
// Created by Alen on 16/03/2022.
//

#include "Ui.h"


void UserInterface::ui_add() {

    char link[61], title[41], description[41], date_time[41], people_number[41];
    unsigned int new_people_number;

    std::cout << "Link:\n";
    std::cin.getline(link, 61);
    if (link[0] == '\0')
        throw UserError("Invalid link\n");

    std::cout << "Title:\n";
    std::cin.getline(title, 41);
    if (title[0] == '\0')
        throw UserError("Invalid title\n");

    std::cout << "Description:\n";
    std::cin.getline(description, 41);
    if (description[0] == '\0')
        throw UserError("Invalid description\n");

    std::cout << "Date and time (dd/mm/yyyy hh:mm):\n";
    std::cin.getline(date_time, 41);
    if (date_time[0] == '\0')
        throw UserError("Invalid date and time\n");

    std::cout << "Number of people:\n";
    std::cin.getline(people_number, 41);
    if (people_number[0] == '\0')
        throw UserError("Invalid number of people\n");
    new_people_number = std::stoi(people_number);

    this->event_service.add_event(link, title, description, date_time, new_people_number);
}

void UserInterface::ui_delete() {

    char link[41];
    std::cout << "Link:\n";
    std::cin.getline(link, 41);
    if (link[0] == '\0')
        throw UserError("Invalid link\n");
    this->event_service.remove_event(link);
}

void UserInterface::ui_update() {

    char link[41], title[41], description[41], date_time[41], people_number[41];
    unsigned int new_people_number;

    std::cout << "Link:\n";
    std::cin.getline(link, 41);
    if (link[0] == '\0')
        throw UserError("Invalid link\n");

    std::cout << "Title:\n";
    std::cin.getline(title, 41);
    if (title[0] == '\0')
        throw UserError("Invalid title\n");

    std::cout << "Description:\n";
    std::cin.getline(description, 41);
    if (description[0] == '\0')
        throw UserError("Invalid description\n");

    std::cout << "Date and time (dd/mm/yyyy hh:mm):\n";
    std::cin.getline(date_time, 41);
    if (date_time[0] == '\0')
        throw UserError("Invalid date and time\n");

    std::cout << "Number of people:\n";
    std::cin.getline(people_number, 41);
    if (people_number[0] == '\0')
        throw UserError("Invalid number of people\n");
    new_people_number = std::stoi(people_number);

    this->event_service.update_event(link, title, description, date_time, new_people_number);
}

void UserInterface::ui_list() {

    Event* events = this->event_service.list_events();
    for(int i = 0; i <= this->event_service.get_number_events() - 1; i++)
        std::cout << events[i];
}

void UserInterface::ui_user_show_events() {

    char command[41], month[41];
    unsigned int int_month;

    while(true)
    {
        try {
            std::cout << "Please enter a month (1-12):\n";
            std::cin.getline(month, 41);
            int_month = std::stoi(month);
            if (int_month <= 0 || int_month >= 13)
                throw ValidError("Invalid month");
            break;
        }
        catch (ValidError &valid_error) {
            std::cout << valid_error.get_message() << std::endl;
        }
        catch (const std::invalid_argument &ia) {
            std::cout << "Invalid month" << std::endl;
        }
    }

    if(this->event_service.get_number_events_for_month(int_month) == this->user_event_service.get_number_events_for_month(int_month))
    {
        std::cout << "All events available for this month are already in your list of events\n";
        return;
    }

    std::cout << "Here are your options:\n";
    std::cout << "'add' - Add event to your list\n";
    std::cout << "'next' - Ignore this event\n";
    std::cout << "'exit' - Exit this menu\n";

    int i;
    bool valid1, valid2;

    Event* events = this->event_service.list_events();
    for(i = 0; i <= this->event_service.get_number_events() - 1; i++)
    {

        valid2 = true;
        if (events[i].get_month() != int_month)
            valid2 = false;

        valid1 = true;
        Event* user_events = this->user_event_service.list_events();

        if(valid2)
        {
            for(int j = 0; j <= this->user_event_service.get_number_events() - 1; j++)
                if (events[i].get_link() == user_events[j].get_link())
                {
                    valid1 = false;
                    break;
                }
        }

        if(valid1 && valid2)
        {
            std::cout << events[i];
            system(std::string("start " + events[i].get_link()).c_str());
            while (true)
            {
                std::cout << "Please enter your option:\n";
                std::cin.getline(command, 41);
                if (!strcmp(command, "add"))
                {
                    this->user_event_service.add_event(events[i].get_link(),
                                                       events[i].get_title(),
                                                       events[i].get_description(),
                                                       events[i].get_date_time(),
                                                       events[i].get_people_number() + 1);
                    events[i].set_people_number(events[i].get_people_number() + 1);
                    command[0] = '\0';
                    if(this->event_service.get_number_events_for_month(int_month) == this->user_event_service.get_number_events_for_month(int_month))
                    {
                        std::cout << "All events available for this month are already in your list of events\n";
                        return;
                    }
                    break;
                }
                else if (!strcmp(command, "next"))
                {
                    command[0] = '\0';
                    break;
                }
                else if (!strcmp(command, "exit"))
                    return;
                else
                {
                    std::cout << "Invalid command\n";
                    command[0] = '\0';
                }
            }
        }
        if (i == this->event_service.get_number_events() - 1)
            i = 0;
    }
    std::cout << "All events available for this month are already in your list of events\n";
}

void UserInterface::ui_user_my_events() {

    char command[41];

    if(this->user_event_service.get_number_events() == 0)
    {
        std::cout << "You are not interested in any event\n";
        return;
    }

    Event* user_events = this->user_event_service.list_events();
    for(int i = 0; i <= this->user_event_service.get_number_events() - 1; i++)
        std::cout << user_events[i];

    while(true)
    {
        try {
            std::cout << "Please enter your option:\n";
            std::cin.getline(command, 41);
            if (!strcmp(command, "delete"))
            {
                char link[61];
                std::cout << "Link:\n";
                std::cin.getline(link, 61);
                this->user_event_service.remove_event(link);

                Event* events = this->event_service.list_events();
                for(int i = 0; i <= this->event_service.get_number_events() - 1; i++)
                    if (events[i].get_link() == link)
                        events[i].set_people_number(events[i].get_people_number() - 1);

                break;
            }
            else if (!strcmp(command, "exit"))
                return;
            else
            {
                std::cout << "Invalid command\n";
                command[0] = '\0';
            }
        }
        catch (RepoError &repo_error) {
            std::cout << repo_error.get_message() << std::endl;
        }
        catch (ValidError &valid_error) {
            std::cout << valid_error.get_message() << std::endl;
        }
        catch (UserError &user_error) {
            std::cout << user_error.get_message() << std::endl;
        }
    }
}

void UserInterface::print_admin_menu() {

    std::cout << "Here is a list of your options (Admin Mode):\n";
    std::cout << "-------------------------------\n";
    std::cout << "'add': Add an event\n";
    std::cout << "'delete': Delete an event\n";
    std::cout << "'update': Update an event\n";
    std::cout << "-------------------------\n";
    std::cout << "'list': List all events\n";
    std::cout << "-----------------------\n";
    std::cout << "'exit': Exit admin mode\n";
}

void UserInterface::print_user_menu() {

    std::cout << "Here is a list of your options (User Mode):\n";
    std::cout << "-------------------------------\n";
    std::cout << "'show events': Lists all available events for a month for you to choose\n";
    std::cout << "'my events': Lists all events you're interested in\n";
    std::cout << "'exit' - Exit user mode\n";
}

void UserInterface::run()
{
    char command[41], user_command[41], admin_command[41];
    this->event_service.populate_array();
    std::cout << "Welcome to the Event Calendar!!!\n";
    std::cout << "Please enter a option: \n'admin' - To enter admin mode\n'user' - To enter user mode\n'exit' - Exit\n";
    while (true)
    {
        std::cout << "Please enter a mode (Admin or User):\n";
        std::cin.getline(command, 41);
        if (!strcmp(command, "user"))
        {
            while (true)
            {
                this->print_user_menu();
                std::cout << "Please enter your option:\n";
                std::cin.getline(user_command, 41);
                try {
                    if(!strcmp(user_command, "show events"))
                    {
                        this->ui_user_show_events();
                        user_command[0] = '\0';
                    }
                    else if (!strcmp(user_command, "my events"))
                    {
                        this->ui_user_my_events();
                        user_command[0] = '\0';
                    }
                    else if (!strcmp(user_command, "exit"))
                    {
                        user_command[0] = '\0';
                        break;
                    }
                    else
                    {
                        std::cout << "Invalid command\n";
                        user_command[0] = '\0';
                    }
                }
                catch (RepoError &repo_error) {
                    std::cout << repo_error.get_message() << std::endl;
                }
                catch (ValidError &valid_error) {
                    std::cout << valid_error.get_message() << std::endl;
                }
                catch (UserError &user_error) {
                    std::cout << user_error.get_message() << std::endl;
                }
            }
        }
        else if (!strcmp(command, "admin"))
        {
            this->print_admin_menu();
            while (true) {
                std::cout << "Please enter your option:\n";
                std::cin.getline(admin_command, 41);
                try {
                    if (!strcmp(admin_command, "add")) {
                        this->ui_add();
                        admin_command[0] = '\0';
                    } else if (!strcmp(admin_command, "delete")) {
                        this->ui_delete();
                        admin_command[0] = '\0';
                    } else if (!strcmp(admin_command, "update")) {
                        this->ui_update();
                        admin_command[0] = '\0';
                    } else if (!strcmp(admin_command, "list")) {
                        this->ui_list();
                        admin_command[0] = '\0';
                    } else if (!strcmp(admin_command, "exit"))
                        break;
                    else
                        std::cout << "Invalid command!\n";
                }
                catch (RepoError &repo_error) {
                    std::cout << repo_error.get_message() << std::endl;
                }
                catch (ValidError &valid_error) {
                    std::cout << valid_error.get_message() << std::endl;
                }
                catch (UserError &user_error) {
                    std::cout << user_error.get_message() << std::endl;
                }
                catch (const std::invalid_argument &ia) {
                    std::cout << "Invalid number of people" << std::endl;
                }
            }
            command[0] = '\0';
        }
        else if (!strcmp(command, "exit"))
            return;
        else
        {
            std::cout << "Invalid mode!\n";
            command[0] = '\0';
        }
    }
}
