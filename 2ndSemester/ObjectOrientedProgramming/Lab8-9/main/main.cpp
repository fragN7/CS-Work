//
// Created by Alen on 16/03/2022.
//

#include "../ui/Ui.h"
#include "../tests/tests.h"

/// Main function, run the tests and creating the repo's
/// \return 0
int main()
{
    Testing::run_tests();

    std::cout << "Please enter the type of repo CSV or HTML:\n";
    std::string html_csv;
    getline(std::cin, html_csv);

    Event_CSV_Repo csv_repo;
    Event_HTML_Repo html_repo;
    Event_Repo user_event_repo;

    Event_Repo* user_repo = &user_event_repo;

    Event_Repo old_admin_repo;
    Event_Repo* admin_repo = &old_admin_repo;

    Event_Validation event_validation;

    if(html_csv == "html")
        user_repo = &html_repo;
    else if(html_csv == "csv")
        user_repo = &csv_repo;

    Event_Service event_service(admin_repo, event_validation);
    Event_Service user_service(user_repo, event_validation);

    UserInterface ui(event_service, user_service);
    ui.run(html_csv);

    return 0;
}