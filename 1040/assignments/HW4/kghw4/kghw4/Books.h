// Books.h

#ifndef BOOKS_H
#define BOOKS_H

#include "LibraryItems.h"
#include <string>

using namespace std;

class Books : public LibraryItems {
private:
    string author;
    string title;
    int isbn;
    string category;

public:
    // Constructor
    Books(const string& author, const string& title, int isbn, int libraryID, float cost,
          ItemStatus status = IN, int loanPeriod = 14);

    // Accessors
    string getAuthor() const;
    string getTitle() const override;
    int getISBN() const;
    string getCategory() const;

    // Mutators
    void setAuthor(const string& author);
    void setTitle(const string& title) override;
    void setISBN(int isbn);
    void setCategory(const string& category);

    // Overridden Function
    void displayItemInfo() const override;
};

#endif // BOOKS_H
