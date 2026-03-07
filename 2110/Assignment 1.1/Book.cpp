#include "Book.h"
#include <iostream>

using namespace std;

Book::Book(const string& title, const string& author, int year, double price)
    : title(title), author(author), year(year), price(price), next(nullptr) {}

string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

int Book::getYear() const {
    return year;
}

double Book::getPrice() const {
    return price;
}

Book* Book::getNext() const {
    return next;
}

void Book::setNext(Book* nextBook) {
    next = nextBook;
}

void Book::display() const {
    cout << title << " by " << author << " (" << year << ") - $" << price;
}
