//
// Created by Alen on 16/03/2022.
//

#include "tests.h"

Testing::~Testing() = default;

void Testing::test_array() {


    Array <Event> test_dynamic_array(2);
    Array <Event> test_dynamic_array2(2);

    std::string link = "www.1.com";
    std::string title = "title";
    std::string description = "desc";
    std::string date_time = "12/12/1222 12:12";
    Event test_event(link, title, description, date_time, 45);
    test_dynamic_array.append_array(test_event);

    //test_dynamic_array2 + test_event;
    //assert(test_dynamic_array2.get_size() == 1);

    std::string title1 = "titles";
    std::string description1 = "sed";
    std::string date_time1 = "12/12/1222 12:45";
    Event test_event3(link, title1, description1, date_time1, 34);

    test_event + test_dynamic_array2;
    test_dynamic_array2.update_array(0, test_event3);
    assert(test_dynamic_array2.get_all_elements()[0].get_people_number() == 34);
    assert(test_dynamic_array2.get_size() == 1);

    Array <Event> test_dynamic_array1(test_dynamic_array);
    assert(test_dynamic_array1.get_size() == 1);
}

void Testing::test_domain() {

    Event default_event{};

    std::string link = "www.1.com";
    std::string title = "title";
    std::string description = "desc";
    std::string date_time = "12/12/1222 12:12";
    Event test_event(link, title, description, date_time, 45);

    assert(test_event.get_link() == link);
    assert(test_event.get_title() == title);
    assert(test_event.get_description() == description);
    assert(test_event.get_date_time() == date_time);
    assert(test_event.get_people_number() == 45);

    std::string link1 = "www.2.com";
    std::string title1= "title";
    std::string description1 = "desc";
    std::string date_time1 = "12/09/1222 12:12";
    Event test_event1(link1, title1, description1, date_time1, 90);

    assert(test_event1.get_month() == 9);
    assert(test_event.get_month() == 12);

    std::string new_title = "new title";
    test_event.set_title(new_title);
    assert(test_event.get_title() == new_title);

    std::string new_description = "new description";
    test_event.set_description(new_description);
    assert(test_event.get_description() == new_description);

    std::string new_date_time = "new date_time";
    test_event.set_date_time(new_date_time);
    assert(test_event.get_date_time() == new_date_time);

    test_event.set_people_number(80);
    assert(test_event.get_people_number() == 80);

    std::stringstream string_event;
    string_event << test_event;
    assert(string_event.str() == "www.1.com | new title | new description | new date_time | 80\n");
}

void Testing::test_repo() {

    Array<Event> test_dynamic_array(1);
    Event_Repo test_event_repo(test_dynamic_array);
    Event default_event{};

    std::string link = "www.1.com";
    std::string title = "title";
    std::string description = "desc";
    std::string date_time = "12/12/1222 12:12";
    Event test_event(link, title, description, date_time, 45);

    test_event_repo.add(test_event);
    assert(test_event_repo.get_event_number() == 1);

    try {
        test_event_repo.add(test_event);
    }
    catch(RepoError& re){
        assert(true);
    }

    std::string link1 = "www.2.com";
    Event test_event1(link1, title, description, date_time, 80);

    try {
        test_event_repo.update(test_event1);
    }
    catch(RepoError& re){
        assert(true);
    }

    test_event_repo.update(test_event);

    std::string link2 = "www.3.com";
    Event test_event2(link2, title, description, date_time, 60);
    test_event_repo.add(test_event2);

    try {
        test_event_repo.remove(test_event1.get_link());
    }
    catch (RepoError& re) {
        assert(true);
    }

    test_event_repo.remove(test_event.get_link());
    assert(test_event_repo.get_event_number() == 1);
}

void Testing::test_service() {

    Array<Event> test_dynamic_array(1);
    Event_Repo test_event_repo(test_dynamic_array);
    Event_Validation test_event_validation;
    Event_Service test_event_service(test_event_repo, test_event_validation);

    std::string link = "www.1.com";
    std::string title = "title";
    std::string description = "desc";
    std::string date_time = "12/12/1222 12:12";

    test_event_service.add_event(link, title, description, date_time, 10);
    assert(test_event_service.get_number_events() == 1);

    test_event_service.update_event(link, title, description, date_time, 50);
    assert(test_event_service.list_events()[0].get_people_number() == 50);

    assert(test_event_service.get_number_events_for_month(12) == 1);

    test_event_service.remove_event(link);
    assert(test_event_service.get_number_events() == 0);

}

void Testing::test_validation() {

    std::string link;
    try {
        Event_Validation::validate_link(link);
    }
    catch(ValidError& ve){
        assert(true);
    }

    std::string link1 = "121";
    try {
        Event_Validation::validate_link(link1);
    }
    catch(ValidError& ve){
        assert(true);
    }
    std::string link2 = "ww2.olm.moc";
    try {
        Event_Validation::validate_link(link2);
    }
    catch(ValidError& ve){
        assert(true);
    }

    std::string link3;
    std::string title;
    std::string description;
    std::string date;
    try {
        Event_Validation::validate_event(link3, title, description, date);
    }
    catch(ValidError& ve){
        assert(true);
    }

    std::string date0 = "123";
    try {
        Event_Validation::validate_event(link3, title, description, date0);
    }
    catch(ValidError& ve){
        assert(true);
    }

    std::string date1 = "11 1111111111111";
    try {
        Event_Validation::validate_event(link3, title, description, date1);
    }
    catch(ValidError& ve){
        assert(true);
    }

    std::string date2 = "1111111111 11111";
    try {
        Event_Validation::validate_event(link3, title, description, date2);
    }
    catch(ValidError& ve){
        assert(true);
    }

    std::string date3 = "91/11/1111 11:11";
    try {
        Event_Validation::validate_event(link3, title, description, date3);
    }
    catch(ValidError& ve){
        assert(true);
    }

    std::string date4 = "1a/11/1111 11:11";
    try {
        Event_Validation::validate_event(link3, title, description, date4);
    }
    catch(ValidError& ve){
        assert(true);
    }

    std::string date5 = "11/51/1111 11:11";
    try {
        Event_Validation::validate_event(link3, title, description, date5);
    }
    catch(ValidError& ve){
        assert(true);
    }

    std::string date6 = "11/1s/1111 11:11";
    try {
        Event_Validation::validate_event(link3, title, description, date6);
    }
    catch(ValidError& ve){
        assert(true);
    }

    std::string date7 = "11/11/1a11 11:11";
    try {
        Event_Validation::validate_event(link3, title, description, date7);
    }
    catch(ValidError& ve){
        assert(true);
    }

    std::string date8 = "11/11/1111 31:11";
    try {
        Event_Validation::validate_event(link3, title, description, date8);
    }
    catch(ValidError& ve){
        assert(true);
    }

    std::string date9 = "11/11/1111 1a:11";
    try {
        Event_Validation::validate_event(link3, title, description, date9);
    }
    catch(ValidError& ve){
        assert(true);
    }

    std::string date10 = "11/11/1111 11:61";
    try {
        Event_Validation::validate_event(link3, title, description, date10);
    }
    catch(ValidError& ve){
        assert(true);
    }

    std::string date11 = "11/11/1111 11:1a";
    try {
        Event_Validation::validate_event(link3, title, description, date11);
    }
    catch(ValidError& ve){
        assert(true);
    }

    std::string date12 = "11/11/1111 11111";
    try {
        Event_Validation::validate_event(link3, title, description, date12);
    }
    catch(ValidError& ve){
        assert(true);
    }

    std::string date13 = "11/11/1111 11:11";
    try {
        Event_Validation::validate_event(link3, title, description, date13);
    }
    catch(ValidError& ve){
        assert(true);
    }
}

void Testing::run_tests() {

    test_array();
    test_domain();
    test_repo();
    test_service();
    test_validation();
}

