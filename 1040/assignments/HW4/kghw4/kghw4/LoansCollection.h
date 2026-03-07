#ifndef LOANSCOLLECTION_H
#define LOANSCOLLECTION_H

#include <vector>
#include "Loans.h"
#include "PatronsCollection.h"
#include "LibraryItemsCollection.h"

// Manages a collection of Loans, facilitating operations such as checking out
// and checking in library items, listing overdue items
class LoansCollection {
public:
    // Checks out a library item for a patron
    void CheckOutItem(PatronsCollection& allPatrons, LibraryItemsCollection& allItems);

    // Checks in a library item from a patron
    void CheckInItem(PatronsCollection& allPatrons, LibraryItemsCollection& allItems);

    // Lists all overdue items
    void ListAllOverdueItems();

    // Lists all items checked out to a specific patron
    void ListItemsForPatron(PatronsCollection& allPatrons, LibraryItemsCollection& allItems);

    // Lists all items checked out to a patron by their ID
    void ListItemsForPatronByID(PatronsCollection& allPatrons, LibraryItemsCollection& allItems, int patronID);

    // Updates the loan status based on the current date
    void AutoUpdateLoanStatus();

    // Edits a loan, allowing for rechecks
    void EditLoan(PatronsCollection& allPatrons, LibraryItemsCollection& allItems);

    // Reports an item as lost
    void ReportLost(PatronsCollection& allPatrons, LibraryItemsCollection& allItems);

private:
    std::vector<Loans*> loansList; // Stores pointers to Loans
};

#endif // LOANSCOLLECTION_H
