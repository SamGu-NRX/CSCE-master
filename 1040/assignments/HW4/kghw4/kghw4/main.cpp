// main.cpp

#include <iostream>
#include <limits>
#include "PatronsCollection.h"
#include "LibraryItemsCollection.h"
#include "LoansCollection.h"

using namespace std;

void itemOptions(LibraryItemsCollection& items) {
    int choice;
    do {
        cout << "\n--- Library Item Options ---\n";
        cout << "1. Add Item\n";
        cout << "2. Edit Item\n";
        cout << "3. Delete Item\n";
        cout << "4. Print All Items\n";
        cout << "5. Return to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;
        while (cin.fail() || choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input. Please enter a number between 1 and 5: ";
            cin >> choice;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer

        switch (choice) {
            case 1:
                items.AddItem();
                break;
            case 2:
                items.EditItem();
                break;
            case 3:
                items.DeleteItem();
                break;
            case 4:
                items.PrintAllItems();
                break;
            case 5:
                cout << "Returning to Main Menu...\n";
                break;
        }
    } while (choice != 5);
}

void patronOptions(PatronsCollection& patrons) {
    int choice;
    do {
        cout << "\n--- Patron Options ---\n";
        cout << "1. Add Patron\n";
        cout << "2. Edit Patron\n";
        cout << "3. Delete Patron\n";
        cout << "4. Print All Patrons\n";
        cout << "5. Return to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer

        switch (choice) {
            case 1:
                patrons.AddPatron();
                break;
            case 2:
                patrons.EditPatron();
                break;
            case 3:
                patrons.DeletePatron();
                break;
            case 4:
                patrons.PrintAllPatrons();
                break;
            case 5:
                cout << "Returning to Main Menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

void loanOptions(LoansCollection& loans, PatronsCollection& patrons, LibraryItemsCollection& items) {
    int choice;
    do {
        cout << "\n--- Loan Options ---\n";
        cout << "1. Check Out Item\n";
        cout << "2. Check In Item\n";
        cout << "3. List All Overdue Items\n";
        cout << "4. List Items for a Patron\n";
        cout << "5. Edit Loan\n";
        cout << "6. Report Lost Item\n";
        cout << "7. Return to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;
        // Validate input
        while (cin.fail() || choice < 1 || choice > 7) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input. Please enter a number between 1 and 7: ";
            cin >> choice;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer

        switch (choice) {
            case 1:
                loans.CheckOutItem(patrons, items);
                break;
            case 2:
                loans.CheckInItem(patrons, items);
                break;
            case 3:
                loans.ListAllOverdueItems();
                break;
            case 4:
                loans.ListItemsForPatron(patrons, items);
                break;
            case 5:
                loans.EditLoan(patrons, items);
                break;
            case 6:
                loans.ReportLost(patrons, items);
                break;
            case 7:
                cout << "Returning to Main Menu...\n";
                break;
        }
    } while (choice != 7);
}


int main() {
    PatronsCollection patrons;
    LibraryItemsCollection items;
    LoansCollection loans;

    int choice;
    do {
        cout << "\n--- Library Management System ---\n";
        cout << "1. Patron Options\n";
        cout << "2. Item Options\n";
        cout << "3. Loan Options\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        while (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input. Please enter a number between 1 and 4: ";
            cin >> choice;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer

        switch (choice) {
            case 1:
                patronOptions(patrons);
                break;
            case 2:
                itemOptions(items);
                break;
            case 3:
                loanOptions(loans, patrons, items);
                break;
            case 4:
                cout << "Exiting Library Management System. Goodbye!\n";
                break;
        }
    } while (choice != 4);

    return 0;
}
