#include "LoansCollection.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <sstream>

std::tm getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    return tm;
}

std::string tmToString(const std::tm& date) {
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &date);
    return std::string(buffer);
}

int calculateDaysDifference(const std::tm& dueDate, const std::tm& currentDate) {
    std::time_t due_time = std::mktime(const_cast<std::tm*>(&dueDate));
    std::time_t current_time = std::mktime(const_cast<std::tm*>(&currentDate));
    const double secondsPerDay = 60 * 60 * 24;
    return static_cast<int>(std::difftime(current_time, due_time) / secondsPerDay);
}

void LoansCollection::CheckOutItem(PatronsCollection& allPatrons, LibraryItemsCollection& allItems) {
    Patron* patron = allPatrons.PromptForSearchMechanism();
    if (!patron) {
        std::cout << "Patron not found.\n";
        return;
    }

    if (patron->getNumBooks() >= 6) {
        std::cout << "Patron has reached the maximum number of checked out items.\n";
        return;
    }

    if (patron->getFineBalance() > 0) {
        std::cout << "Patron has outstanding fines. Cannot check out items.\n";
        return;
    }

    LibraryItems* item = allItems.PromptForSearchMechanism();
    if (!item) {
        std::cout << "Item not found.\n";
        return;
    }

    if (item->getStatus() != LibraryItems::IN) {
        std::cout << "Item is not available.\n";
        return;
    }

    // Calculate due date based on loan period
    std::tm dueDate = getCurrentDate();
    dueDate.tm_mday += item->getLoanPeriod();
    mktime(&dueDate);

    // Create new loan
    Loans* loan = new Loans(item->getLibraryID(), patron->getPatronID(), dueDate);

    loansList.push_back(loan);

    item->setStatus(LibraryItems::OUT);
    patron->setNumBooks(patron->getNumBooks() + 1);

    std::cout << "Item checked out successfully. Due date: " << tmToString(dueDate) << "\n";
}

void LoansCollection::CheckInItem(PatronsCollection& allPatrons, LibraryItemsCollection& allItems) {
    Patron* patron = allPatrons.PromptForSearchMechanism();
    if (!patron) {
        std::cout << "Patron not found.\n";
        return;
    }

    LibraryItems* item = allItems.PromptForSearchMechanism();
    if (!item) {
        std::cout << "Item not found.\n";
        return;
    }

    auto it = std::find_if(loansList.begin(), loansList.end(), [&](Loans* loan) {
        return loan->getPatronID() == patron->getPatronID() && loan->getLibraryID() == item->getLibraryID();
    });

    if (it != loansList.end()) {
        // Check for overdue and apply fines if necessary
        std::tm dueDate = (*it)->getDueDate();
        std::tm today = getCurrentDate();
        int daysOverdue = calculateDaysDifference(dueDate, today);

        if (daysOverdue > 0) {
            float fineAmount = daysOverdue * 0.50f; // Assume $0.50 per day overdue
            patron->setFineBalance(patron->getFineBalance() + fineAmount);
            std::cout << "Item is overdue by " << daysOverdue << " days. Fine of $" << fineAmount << " applied.\n";
        }

        delete *it;
        loansList.erase(it);

        item->setStatus(LibraryItems::IN);
        patron->setNumBooks(patron->getNumBooks() - 1);

        std::cout << "Item checked in successfully.\n";
    } else {
        std::cout << "Loan record not found.\n";
    }
}

void LoansCollection::ListAllOverdueItems() {
    std::tm today = getCurrentDate();
    bool found = false;

    std::cout << "\n--- Overdue Items ---\n";
    for (auto* loan : loansList) {
        std::tm dueDate = loan->getDueDate();
        int daysOverdue = calculateDaysDifference(dueDate, today);

        if (daysOverdue > 0) {
            found = true;
            std::cout << "Loan ID: " << loan->getLoanID()
                      << ", Library Item ID: " << loan->getLibraryID()
                      << ", Patron ID: " << loan->getPatronID()
                      << ", Due Date: " << tmToString(dueDate)
                      << ", Days Overdue: " << daysOverdue << "\n";
        }
    }

    if (!found) {
        std::cout << "No overdue items found.\n";
    }
}

void LoansCollection::ListItemsForPatron(PatronsCollection& allPatrons, LibraryItemsCollection& allItems) {
    Patron* patron = allPatrons.PromptForSearchMechanism();
    if (!patron) {
        std::cout << "Patron not found.\n";
        return;
    }

    std::cout << "\nItems checked out by " << patron->getName() << ":\n";
    bool found = false;

    for (auto* loan : loansList) {
        if (loan->getPatronID() == patron->getPatronID()) {
            LibraryItems* item = allItems.FindItemByID(loan->getLibraryID());
            if (item) {
                std::cout << " - Item ID: " << item->getLibraryID()
                          << ", Due Date: " << tmToString(loan->getDueDate()) << "\n";
                found = true;
            }
        }
    }

    if (!found) {
        std::cout << "No items currently checked out by this patron.\n";
    }
}

void LoansCollection::ListItemsForPatronByID(PatronsCollection& allPatrons, LibraryItemsCollection& allItems, int patronID) {
    Patron* patron = allPatrons.FindPatronByID(patronID);
    if (!patron) {
        std::cout << "Patron not found.\n";
        return;
    }

    std::cout << "\nItems checked out by " << patron->getName() << " (ID: " << patronID << "):\n";
    bool found = false;

    for (auto* loan : loansList) {
        if (loan->getPatronID() == patronID) {
            LibraryItems* item = allItems.FindItemByID(loan->getLibraryID());
            if (item) {
                std::cout << " - Item ID: " << item->getLibraryID()
                          << ", Due Date: " << tmToString(loan->getDueDate()) << "\n";
                found = true;
            }
        }
    }

    if (!found) {
        std::cout << "No items currently checked out by this patron.\n";
    }
}

void LoansCollection::AutoUpdateLoanStatus() {
    std::tm today = getCurrentDate();
    for (auto* loan : loansList) {
        std::tm dueDate = loan->getDueDate();
        int daysOverdue = calculateDaysDifference(dueDate, today);

        if (daysOverdue > 0) {
            loan->setStatus(Loans::OVERDUE);
        }
    }
}

void LoansCollection::EditLoan(PatronsCollection& allPatrons, LibraryItemsCollection& allItems) {
    std::cout << "\n--- Editing a Loan Record ---\n";
    Patron* patron = allPatrons.PromptForSearchMechanism();
    if (!patron) {
        std::cout << "Patron not found.\n";
        return;
    }

    LibraryItems* item = allItems.PromptForSearchMechanism();
    if (!item) {
        std::cout << "Item not found.\n";
        return;
    }

    auto it = std::find_if(loansList.begin(), loansList.end(), [&](Loans* loan) {
        return loan->getPatronID() == patron->getPatronID() && loan->getLibraryID() == item->getLibraryID();
    });

    if (it == loansList.end()) {
        std::cout << "No active loan found for this item and patron combination.\n";
        return;
    }

    // Allow extending the due date
    int additionalDays;
    std::cout << "Enter number of additional days to extend the due date: ";
    while (!(std::cin >> additionalDays) || additionalDays <= 0) {
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cout << "Invalid input. Please enter a positive integer: ";
    }
    std::cin.ignore();

    std::tm newDueDate = (*it)->getDueDate();
    newDueDate.tm_mday += additionalDays;
    mktime(&newDueDate);
    (*it)->setDueDate(newDueDate);

    std::cout << "Loan record updated. New due date: " << tmToString(newDueDate) << ".\n";
}

void LoansCollection::ReportLost(PatronsCollection& allPatrons, LibraryItemsCollection& allItems) {
    std::cout << "\n--- Reporting an Item as Lost ---\n";
    Patron* patron = allPatrons.PromptForSearchMechanism();
    if (!patron) {
        std::cout << "Patron not found.\n";
        return;
    }

    LibraryItems* item = allItems.PromptForSearchMechanism();
    if (!item) {
        std::cout << "Item not found.\n";
        return;
    }

    auto it = std::find_if(loansList.begin(), loansList.end(), [&](Loans* loan) {
        return loan->getLibraryID() == item->getLibraryID();
    });

    if (it != loansList.end()) {
        item->setStatus(LibraryItems::LOST);
        float lostItemCost = item->getCost();
        patron->setFineBalance(patron->getFineBalance() + lostItemCost);
        std::cout << "Item marked as lost. A fine of $" << lostItemCost << " has been added to the patron's account.\n";
    } else {
        std::cout << "Loan record for the item not found.\n";
    }
}
