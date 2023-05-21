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

    Array <Event> dynamic_array(1);
    Event_Repo event_repo(dynamic_array);
    Event_Validation event_validator;
    Event_Service event_service(event_repo, event_validator);

    Array <Event> user_dynamic_array(1);
    Event_Repo user_event_repo(user_dynamic_array);
    Event_Service user_event_service(user_event_repo, event_validator);

    UserInterface ui(event_service, user_event_service);
    ui.run();

    return 0;
}