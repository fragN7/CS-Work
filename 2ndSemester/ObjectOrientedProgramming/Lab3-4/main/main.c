//
// Created by Alen on 02/03/2022.
//

#include "../ui/ui.h"
#include "../testing/tests.h"

/// Run tests, create the repo for the offer, create the repo for arrays, run the main UI function and destroy both arrays
/// \return 0
int main()
{
    run_tests();
    Array* offer_repo = create_array(1, &destroy_offer, &copy_offer);
    Array* undo_redo_repo = create_array(1, &destroy_array, &copy_array);
    run(offer_repo, undo_redo_repo);
    destroy_array(offer_repo);
    destroy_array(undo_redo_repo);
    return 0;
}
