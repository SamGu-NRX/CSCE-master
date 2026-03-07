// Books.cpp

#include "Books.h"
#include <iostream>

using namespace std;

// Constructor
Books::Books(const string& author, const string& title, int isbn, int libraryID, float cost,
             ItemStatus status, int loanPeriod)
    : LibraryItems(libraryID, cost, status, loanPeriod), author(author), title(title), isbn(isbn) {
}

// Accessors
string Books::getAuthor() const {
    return author;
}

string Books::getTitle() const {
    return title;
}

int Books::getISBN() const {
    return isbn;
}

string Books::getCategory() const {
    return category;
}

// Mutators
void Books::setAuthor(const string& newAuthor) {
    author = newAuthor;
}

void Books::setTitle(const string& newTitle) {
    title = newTitle;
}

void Books::setISBN(int newISBN) {
    isbn = newISBN;
}

void Books::setCategory(const string& newCategory) {
    category = newCategory;
}

// Overridden Function
void Books::displayItemInfo() const {
    cout << "Book ID: " << getLibraryID() << "\n"
              << "Title: " << title << "\n"
              << "Author: " << author << "\n"
              << "ISBN: " << isbn << "\n"
              << "Cost: $" << getCost() << "\n"
              << "Loan Period: " << getLoanPeriod() << " days\n"
              << "Status: " << (getStatus() == IN ? "IN" : (getStatus() == OUT ? "OUT" : "LOST")) << "\n";
}
