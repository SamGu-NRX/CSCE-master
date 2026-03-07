// LibraryItems.cpp

#include "LibraryItems.h"

// Constructor
LibraryItems::LibraryItems(int libraryID, float cost, ItemStatus status, int loanPeriod)
    : libraryID(libraryID), cost(cost), status(status), loanPeriod(loanPeriod) {
}

// Destructor
LibraryItems::~LibraryItems() {
}

// Accessors
int LibraryItems::getLibraryID() const {
    return libraryID;
}

float LibraryItems::getCost() const {
    return cost;
}

LibraryItems::ItemStatus LibraryItems::getStatus() const {
    return status;
}

int LibraryItems::getLoanPeriod() const {
    return loanPeriod;
}

// Mutators
void LibraryItems::setLibraryID(int id) {
    libraryID = id;
}

void LibraryItems::setCost(float c) {
    cost = c;
}

void LibraryItems::setStatus(ItemStatus s) {
    status = s;
}

void LibraryItems::setLoanPeriod(int period) {
    loanPeriod = period;
}

// Note: Pure virtual functions are not implemented here
