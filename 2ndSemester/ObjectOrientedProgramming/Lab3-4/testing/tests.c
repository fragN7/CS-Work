//
// Created by Alen on 02/03/2022.
//

#include "tests.h"


void test_array()
{
    Array* test_array = create_array(1, &destroy_array, &copy_array);
    destroy_array(test_array);

    Array* test_array1 = NULL;
    destroy_array(test_array1);
}

void test_service()
{
    Array* test_array = create_array(1, &destroy_offer, &copy_offer);
    Offer* test_offer = create_offer("seaside", "dest", "11/11/1151", 43);
    add(test_offer, test_array);

    assert(delete_offer(test_array, "destin", "11/11/1111") == -1);
    assert(delete_offer(test_array, "dest", "11/11/1151") == 1);

    Offer* test_offer1 = create_offer("seaside", "dest", "11/11/1151", 43);
    add(test_offer1, test_array);

    assert(update_offer(test_array, "mountain", "dest", "11/11/1151", 40) == 1);
    assert(update_offer(test_array, "mountain", "dest", "11/11/1111", 40) == -1);

    destroy_offer(test_offer);
    destroy_offer(test_offer1);
    destroy_array(test_array);

    Array* test_service_repo = create_array(1, &destroy_offer, &copy_offer);
    populate_array(test_service_repo);
    populate_array(test_service_repo);
    assert(test_service_repo->size == 20);

    sort_offers_price_asc(test_service_repo);
    sort_offers_price_desc(test_service_repo);
    sort_offers_destination(test_service_repo);

    destroy_array(test_service_repo);
}

void test_repo()
{
    Array* test_repo = create_array(1, &destroy_offer, &copy_offer);

    Offer* test_offer = create_offer("seaside", "dest", "11/11/1111", 43);
    add(test_offer, test_repo);

    Offer* test_offer1 = create_offer("mountain", "destin", "11/11/1211", 43);
    add(test_offer1, test_repo);

    assert(delete("dest", "11/11/1121", test_repo) == -1);
    assert(delete("dest", "11/11/1111", test_repo) == 1);

    Offer* test_offer2 = create_offer("city break", "rams", "11/12/2314", 54);
    add(test_offer2, test_repo);
    update(test_offer2, test_repo, 1);

    destroy_offer(test_offer);
    destroy_offer(test_offer1);
    destroy_offer(test_offer2);
    destroy_array(test_repo);
}

void test_domain()
{
    Offer* test_offer = create_offer("seaside", "dest", "11/11/1111", 43);

    assert(strcmp(get_type(test_offer), "seaside") == 0);
    assert(get_price(test_offer) == 43);

    char test_offer_string[41];
    to_str(test_offer, test_offer_string);
    assert(strcmp(test_offer_string, "seaside dest 11/11/1111 43\n") == 0);

    destroy_offer(test_offer);
    test_offer = NULL;
}

void test_validation()
{
    bool type, departure_date;

    type = validate_type("seaside");
    assert(type == true);

    type = validate_type("mountain");
    assert(type == true);

    type = validate_type("city break");
    assert(type == true);

    type = validate_type("home");
    assert(type == false);

    type = validate_type("jordan");
    assert(type == false);

    departure_date = validate_departure_date("12/12/2002");
    assert(departure_date == true);

    departure_date = validate_departure_date("abc def geh///");
    assert(departure_date == false);

    departure_date = validate_departure_date("12/12/200/");
    assert(departure_date == false);

    departure_date = validate_departure_date("a/bc/2002");
    assert(departure_date == false);

    departure_date = validate_departure_date("1/bc/2002");
    assert(departure_date == false);

    departure_date = validate_departure_date("1/12/a002");
    assert(departure_date == false);

    departure_date = validate_departure_date("29/2/2021");
    assert(departure_date == false);

    departure_date = validate_departure_date("0/1/2021");
    assert(departure_date == false);

    departure_date = validate_departure_date("50/3/2021");
    assert(departure_date == false);

    departure_date = validate_departure_date("31/4/2021");
    assert(departure_date == false);

    departure_date = validate_departure_date("30/2/2020");
    assert(departure_date == false);

    departure_date = validate_departure_date("30/13/2020");
    assert(departure_date == false);

    departure_date = validate_departure_date("0/2/1223");
    assert(departure_date == false);

    departure_date = validate_departure_date("30/2/2020");
    assert(departure_date == false);

    int price;

    price = validate_price("34");
    assert(price == 34);

    price = validate_price("ab");
    assert(price == -1);

    price = validate_price("12.1");
    assert(price == -1);

    price = validate_price("321a");
    assert(price == -1);

    char date[21], other_date[21];

    strcpy(date, "12/11/2001");
    strcpy(other_date, "13/11/2000");
    assert(validate_after_date(date, other_date) == false);

    strcpy(date, "12/11/2001");
    strcpy(other_date, "13/11/2002");
    assert(validate_after_date(date, other_date) == true);

    strcpy(date, "12/12/2000");
    strcpy(other_date, "13/11/2000");
    assert(validate_after_date(date, other_date) == false);

    strcpy(date, "12/11/2000");
    strcpy(other_date, "13/12/2000");
    assert(validate_after_date(date, other_date) == true);

    strcpy(date, "13/11/2001");
    strcpy(other_date, "11/11/2001");
    assert(validate_after_date(date, other_date) == false);

    strcpy(date, "13/11/2001");
    strcpy(other_date, "14/11/2001");
    assert(validate_after_date(date, other_date) == true);

    strcpy(date, "12/11/2001");
    strcpy(other_date, "12/11/2001");
    assert(validate_after_date(date, other_date) == false);

    strcpy(date, "12/11/2001");
    strcpy(other_date, "13/11/2001");
    assert(validate_after_date(date, other_date) == true);
}

void run_tests()
{
    test_array();
    test_domain();
    test_service();
    test_repo();
    test_validation();
}