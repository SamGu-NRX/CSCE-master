// LibraryItems.h

#ifndef LIBRARYITEMS_H
#define LIBRARYITEMS_H

#include <string>

class LibraryItems {
public:
    enum ItemStatus { IN, OUT, LOST };

protected:
    int libraryID;
    float cost;
    ItemStatus status;
    int loanPeriod; // in days

public:
    // Constructor and Destructor
    LibraryItems(int libraryID = 0, float cost = 0.0f, ItemStatus status = IN, int loanPeriod = 14);
    virtual ~LibraryItems();

    // Accessors
    int getLibraryID() const;
    float getCost() const;
    ItemStatus getStatus() const;
    int getLoanPeriod() const;

    // Mutators
    void setLibraryID(int id);
    void setCost(float c);
    void setStatus(ItemStatus s);
    void setLoanPeriod(int period);

    // Pure Virtual Functions for Title
    virtual std::string getTitle() const = 0;
    virtual void setTitle(const std::string& title) = 0;

    // Pure Virtual Function for Displaying Item Info
    virtual void displayItemInfo() const = 0;
};

#endif // LIBRARYITEMS_H
