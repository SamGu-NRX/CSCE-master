#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include <string>

using namespace std;

class Library {
private:
    Book* mainList;
    Book* rentList;
    int totalBooks;

    // Helper functions
    string trim(const string& str);
    Book* searchBook(Book* head, const string& title);
    void deleteBook(Book*& head, const string& title);
    void addBook(Book*& head, Book* newBook);
    void moveBook(Book*& fromList, Book*& toList, const string& title);
    void clearList(Book*& head);

public:
    Library();
    ~Library();

    // Core operations
    void init();
    void buyBook();
    void sellBook();
    void rentBook();
    void returnBook();
    void displayBooks(Book* head, const string& listName);

    // Menu and main loop
    void displayMenu();
    void run();

    // Getters for lists (for display)
    Book* getMainList() const;
    Book* getRentList() const;
};

#endif
