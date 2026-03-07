#include "LibraryItemsCollection.h"
#include "Books.h"
#include "AudioCD.h"
#include "DVD.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <limits>
#include <typeinfo>
#include <cstring>

using namespace std;

LibraryItemsCollection::LibraryItemsCollection() {}

LibraryItemsCollection::~LibraryItemsCollection() {
    for (auto item : items) {
        delete item;
    }
}

const std::vector<LibraryItems*>& LibraryItemsCollection::getItems() const {
    return items;
}

void LibraryItemsCollection::AddItem() {
    int choice;
    cout << "Select the type of item to add:\n";
    cout << "1. Book\n";
    cout << "2. Audio CD\n";
    cout << "3. DVD\n";
    cout << "Enter choice: ";
    cin >> choice;
    while (cin.fail() || choice < 1 || choice > 3) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid choice. Please enter 1, 2, or 3: ";
        cin >> choice;
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer

    LibraryItems* newItem = nullptr;
    int libraryID = items.size(); // Assign next available ID
    float cost;
    int loanPeriod = 14; // Default loan period set to 14 days

    cout << "Enter Cost: ";
    while (!(cin >> cost) || cost < 0) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid cost. Please enter a positive number: ";
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer

    // Prompt user to accept default loan period or enter a custom one
    cout << "The default loan period is 14 days. Do you want to change it? (y/n): ";
    char changeLoanPeriod;
    cin >> changeLoanPeriod;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer

    if (changeLoanPeriod == 'y' || changeLoanPeriod == 'Y') {
        cout << "Enter Loan Period (in days): ";
        while (!(cin >> loanPeriod) || loanPeriod <= 0) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid loan period. Please enter a positive integer: ";
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
    }

    switch (choice) {
        case 1: {
            // Book
            string title, author;
            int isbn;

            cout << "Enter Title: ";
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);
            cout << "Enter ISBN Number: ";
            while (!(cin >> isbn) || isbn <= 0) {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Invalid ISBN. Please enter a positive integer: ";
            }
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            newItem = new Books(author, title, isbn, libraryID, cost, LibraryItems::IN, loanPeriod);
            break;
        }
        case 2: {
            // Audio CD
            string artist, title, genre;
            int numTracks;
            std::tm releaseDate = {};

            cout << "Enter Artist: ";
            getline(cin, artist);
            cout << "Enter Title: ";
            getline(cin, title);
            cout << "Enter Number of Tracks: ";
            while (!(cin >> numTracks) || numTracks <= 0) {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Invalid number of tracks. Please enter a positive integer: ";
            }
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
            cout << "Enter Release Date (YYYY-MM-DD): ";
            string dateStr;
            getline(cin, dateStr);
            std::istringstream ss(dateStr);
            ss >> std::get_time(&releaseDate, "%Y-%m-%d");
            if (ss.fail()) {
                cout << "Invalid date format. Using default date (1970-01-01).\n";
                memset(&releaseDate, 0, sizeof(std::tm));
                releaseDate.tm_year = 70; // Year since 1900
                releaseDate.tm_mon = 0;   // January
                releaseDate.tm_mday = 1;  // First
            }
            cout << "Enter Genre: ";
            getline(cin, genre);

            newItem = new AudioCD(artist, title, numTracks, releaseDate, genre,
                                  libraryID, cost, LibraryItems::IN, loanPeriod);
            break;
        }
        case 3: {
            // DVD
            string title, category, studio;
            int runTime;
            std::tm releaseDate = {};

            cout << "Enter Title: ";
            getline(cin, title);
            cout << "Enter Category: ";
            getline(cin, category);
            cout << "Enter Run Time (in minutes): ";
            while (!(cin >> runTime) || runTime <= 0) {
                cin.clear();
                cin.ignore(256, '\n');
                cout << "Invalid run time. Please enter a positive integer: ";
            }
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
            cout << "Enter Studio: ";
            getline(cin, studio);
            cout << "Enter Release Date (YYYY-MM-DD): ";
            string dateStr;
            getline(cin, dateStr);
            std::istringstream ss(dateStr);
            ss >> std::get_time(&releaseDate, "%Y-%m-%d");
            if (ss.fail()) {
                cout << "Invalid date format. Using default date (1970-01-01).\n";
                memset(&releaseDate, 0, sizeof(std::tm));
                releaseDate.tm_year = 70; // Year since 1900
                releaseDate.tm_mon = 0;   // January
                releaseDate.tm_mday = 1;  // First
            }

            newItem = new DVD(title, category, runTime, studio, releaseDate,
                              libraryID, cost, LibraryItems::IN, loanPeriod);
            break;
        }
    }

    if (newItem) {
        items.push_back(newItem);
        cout << "Item added successfully.\n";
    }
}


void LibraryItemsCollection::EditItem() {
    LibraryItems* item = PromptForSearchMechanism();
    if (!item) {
        cout << "Item not found.\n";
        return;
    }

    cout << "Editing Item ID: " << item->getLibraryID() << "\n";
    cout << "Select the attribute to edit:\n";

    int choice;
    if (typeid(*item) == typeid(Books)) {
        // Books-specific options
        cout << "1. Title\n";
        cout << "2. Author\n";
        cout << "3. ISBN\n";
        cout << "4. Cost\n";
        cout << "5. Loan Period\n";
        cout << "Enter choice: ";
        cin >> choice;
        while (cin.fail() || choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid choice. Please enter a number between 1 and 5: ";
            cin >> choice;
        }
        cin.ignore();
        Books* book = dynamic_cast<Books*>(item);
        switch (choice) {
            case 1: {
                string newTitle;
                cout << "Enter new title: ";
                getline(cin, newTitle);
                book->setTitle(newTitle);
                break;
            }
            case 2: {
                string newAuthor;
                cout << "Enter new author: ";
                getline(cin, newAuthor);
                book->setAuthor(newAuthor);
                break;
            }
            case 3: {
                int newISBN;
                cout << "Enter new ISBN: ";
                while (!(cin >> newISBN) || newISBN <= 0) {
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Invalid ISBN. Please enter a positive integer: ";
                }
                cin.ignore();
                book->setISBN(newISBN);
                break;
            }
            case 4: {
                float newCost;
                cout << "Enter new cost: ";
                while (!(cin >> newCost) || newCost < 0) {
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Invalid cost. Please enter a positive number: ";
                }
                cin.ignore();
                book->setCost(newCost);
                break;
            }
            case 5: {
                int newLoanPeriod;
                cout << "Enter new loan period (in days): ";
                while (!(cin >> newLoanPeriod) || newLoanPeriod <= 0) {
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Invalid loan period. Please enter a positive integer: ";
                }
                cin.ignore();
                book->setLoanPeriod(newLoanPeriod);
                break;
            }
        }
    } else if (typeid(*item) == typeid(AudioCD)) {
        // AudioCD-specific options
        // Implement similar to Books
    } else if (typeid(*item) == typeid(DVD)) {
        // DVD-specific options
        // Implement similar to Books
    } else {
        cout << "Unknown item type.\n";
    }

    cout << "Item updated successfully.\n";
}

void LibraryItemsCollection::DeleteItem() {
    LibraryItems* item = PromptForSearchMechanism();
    if (!item) {
        cout << "Item not found.\n";
        return;
    }

    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end()) {
        delete *it;
        items.erase(it);
        cout << "Item deleted successfully.\n";
    } else {
        cout << "Error deleting the item.\n";
    }
}

void LibraryItemsCollection::PrintAllItems() const {
    if (items.empty()) {
        cout << "No items in the collection.\n";
        return;
    }

    for (const auto& item : items) {
        item->displayItemInfo();
        cout << "--------------------------\n";
    }
}

void LibraryItemsCollection::PrintItem() {
    LibraryItems* item = PromptForSearchMechanism();
    if (item) {
        item->displayItemInfo();
    } else {
        cout << "Item not found.\n";
    }
}

LibraryItems* LibraryItemsCollection::PromptForSearchMechanism() {
    cout << "Search by (1) Title or (2) Library ID? ";
    int choice;
    cin >> choice;
    while (cin.fail() || (choice != 1 && choice != 2)) {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin >> choice;
    }
    cin.ignore();

    if (choice == 1) {
        string title;
        cout << "Enter title: ";
        getline(cin, title);
        return FindItemByTitle(title);
    } else if (choice == 2) {
        int id;
        cout << "Enter Library ID: ";
        while (!(cin >> id) || id < 0) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid Library ID. Please enter a non-negative integer: ";
        }
        cin.ignore();
        return FindItemByID(id);
    } else {
        cout << "Invalid choice.\n";
        return nullptr;
    }
}

LibraryItems* LibraryItemsCollection::FindItemByTitle(const string& title) {
    for (auto item : items) {
        if (item->getTitle() == title) {
            return item;
        }
    }
    return nullptr;
}

LibraryItems* LibraryItemsCollection::FindItemByID(int id) {
    for (auto item : items) {
        if (item->getLibraryID() == id) {
            return item;
        }
    }
    return nullptr;
}
