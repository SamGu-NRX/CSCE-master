#include "Loans.h"

int Loans::nextLoanID = 1; // Initialize static member

Loans::Loans(int libraryID, int patronID, const std::tm& dueDate)
    : loanID(nextLoanID++), libraryID(libraryID), patronID(patronID), dueDate(dueDate), status(NORMAL) {
}

// Getters
int Loans::getLoanID() const {
    return loanID;
}

int Loans::getLibraryID() const {
    return libraryID;
}

int Loans::getPatronID() const {
    return patronID;
}

std::tm Loans::getDueDate() const {
    return dueDate;
}

Loans::LoanStatus Loans::getStatus() const {
    return status;
}

// Setters
void Loans::setLoanID(int id) {
    loanID = id;
}

void Loans::setLibraryID(int id) {
    libraryID = id;
}

void Loans::setPatronID(int id) {
    patronID = id;
}

void Loans::setDueDate(const std::tm& date) {
    dueDate = date;
}

void Loans::setStatus(LoanStatus status) {
    this->status = status;
}
