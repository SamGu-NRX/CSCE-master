#include "Library.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Library::Library() : mainList(nullptr), rentList(nullptr), totalBooks(0) {}

Library::~Library() {
    clearList(mainList);
    clearList(rentList);
}

void Library::clearList(Book*& head) {
    Book* current = head;
    while (current != nullptr) {
        Book* temp = current;
        current = current->getNext();
        delete temp;
    }
    head = nullptr;
}

string Library::trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

void Library::init() {
    ifstream file("real_books_inventory.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open real_books_inventory.txt\n";
        return;
    }

    string line;
    int lineNum = 0;
    while (getline(file, line)) {
        lineNum++;
        if (line.empty() || line.find_first_not_of(" \t\r\n") == string::npos) {
            continue;
        }

        stringstream ss(line);
        string title, author, yearStr, priceStr;

        if (!getline(ss, title, ',')) continue;
        if (!getline(ss, author, ',')) continue;
        if (!getline(ss, yearStr, ',')) continue;
        if (!getline(ss, priceStr, ',')) {
            getline(ss, priceStr);
        }

        title = trim(title);
        author = trim(author);
        yearStr = trim(yearStr);
        priceStr = trim(priceStr);

        // Remove dollar sign from price if present
        if (!priceStr.empty() && priceStr[0] == '$') {
            priceStr = priceStr.substr(1);
        }

        if (title.empty() || author.empty() || yearStr.empty() || priceStr.empty()) {
            cout << "Warning: Skipping line " << lineNum << " due to missing fields\n";
            continue;
        }

        try {
            int year = stoi(yearStr);
            double price = stod(priceStr);

            Book* newBook = new Book(title, author, year, price);
            addBook(mainList, newBook);
            totalBooks++;
        } catch (const exception& e) {
            cout << "Warning: Skipping line " << lineNum << " - " << e.what() << "\n";
            cout << "Line content: " << line << "\n";
        }
    }

    file.close();
    cout << "Library initialized with " << totalBooks << " books.\n";
}

void Library::displayMenu() {
    cout << "\n========== Library Management System ==========\n";
    cout << "1. Buy a Book\n";
    cout << "2. Sell a Book\n";
    cout << "3. Rent a Book\n";
    cout << "4. Return a Book\n";
    cout << "5. Display Available Books\n";
    cout << "6. Display Rented Books\n";
    cout << "7. Exit\n";
    cout << "===============================================\n";
}

void Library::buyBook() {
    string title;
    cout << "\nEnter the title of the book to buy: ";
    getline(cin, title);

    Book* book = searchBook(mainList, title);
    if (book == nullptr) {
        cout << "Book not available in inventory.\n";
        return;
    }

    cout << "Book found: ";
    book->display();
    cout << "\n";

    deleteBook(mainList, title);
    totalBooks--;
    cout << "Book purchased successfully!\n";
}

void Library::sellBook() {
    string title, author, yearStr, priceStr;
    int year;
    double price;

    cout << "\nEnter book details:\n";
    cout << "Title: ";
    getline(cin, title);

    if (searchBook(mainList, title) != nullptr) {
        cout << "This book already exists in inventory.\n";
        return;
    }

    cout << "Author: ";
    getline(cin, author);
    cout << "Year: ";
    getline(cin, yearStr);
    year = stoi(yearStr);
    cout << "Price: ";
    getline(cin, priceStr);
    price = stod(priceStr);

    Book* newBook = new Book(title, author, year, price);
    addBook(mainList, newBook);
    totalBooks++;
    cout << "Book added to inventory successfully!\n";
}

void Library::rentBook() {
    string title;
    cout << "\nEnter the title of the book to rent: ";
    getline(cin, title);

    Book* book = searchBook(mainList, title);
    if (book == nullptr) {
        cout << "Book not available for rent.\n";
        return;
    }

    cout << "Book found: ";
    book->display();
    cout << "\n";

    moveBook(mainList, rentList, title);
    cout << "Book rented successfully!\n";
}

void Library::returnBook() {
    string title;
    cout << "\nEnter the title of the book to return: ";
    getline(cin, title);

    Book* book = searchBook(rentList, title);
    if (book == nullptr) {
        cout << "This book is not in the rented list.\n";
        return;
    }

    cout << "Book found: ";
    book->display();
    cout << "\n";

    moveBook(rentList, mainList, title);
    cout << "Book returned successfully!\n";
}

void Library::displayBooks(Book* head, const string& listName) {
    cout << "\n========== " << listName << " ==========\n";
    if (head == nullptr) {
        cout << "No books in this list.\n";
        return;
    }

    Book* current = head;
    int count = 1;
    while (current != nullptr) {
        cout << count++ << ". ";
        current->display();
        cout << "\n";
        current = current->getNext();
    }
}

Book* Library::searchBook(Book* head, const string& title) {
    Book* current = head;
    while (current != nullptr) {
        if (current->getTitle() == title) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

void Library::deleteBook(Book*& head, const string& title) {
    if (head == nullptr) return;

    if (head->getTitle() == title) {
        Book* temp = head;
        head = head->getNext();
        delete temp;
        return;
    }

    Book* current = head;
    while (current->getNext() != nullptr && current->getNext()->getTitle() != title) {
        current = current->getNext();
    }

    if (current->getNext() != nullptr) {
        Book* temp = current->getNext();
        current->setNext(current->getNext()->getNext());
        delete temp;
    }
}

void Library::addBook(Book*& head, Book* newBook) {
    if (head == nullptr) {
        head = newBook;
    } else {
        Book* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(newBook);
    }
}

void Library::moveBook(Book*& fromList, Book*& toList, const string& title) {
    Book* book = searchBook(fromList, title);
    if (book == nullptr) return;

    // Create new book with same data
    Book* newBook = new Book(book->getTitle(), book->getAuthor(),
                             book->getYear(), book->getPrice());

    // Delete from source list
    deleteBook(fromList, title);

    // Add to destination list
    addBook(toList, newBook);
}

void Library::run() {
    init();

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1:
                buyBook();
                break;
            case 2:
                sellBook();
                break;
            case 3:
                rentBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                displayBooks(mainList, "Available Books");
                break;
            case 6:
                displayBooks(rentList, "Rented Books");
                break;
            case 7:
                cout << "\nThank you for using the Library Management System!\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while(choice != 7);
}

Book* Library::getMainList() const {
    return mainList;
}

Book* Library::getRentList() const {
    return rentList;
}
