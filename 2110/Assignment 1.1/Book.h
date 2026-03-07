#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

class Book {
private:
    string title;
    string author;
    int year;
    double price;
    Book* next;

public:
    Book(const string& title, const string& author, int year, double price);

    // Getters
    string getTitle() const;
    string getAuthor() const;
    int getYear() const;
    double getPrice() const;
    Book* getNext() const;

    // Setter for next pointer
    void setNext(Book* nextBook);

    // Display book info
    void display() const;
};

#endif
