#ifndef LOANS_H
#define LOANS_H

#include <string>
#include <ctime>

class Loans {
public:
    enum LoanStatus { NORMAL, OVERDUE };

    // Constructor
    Loans(int libraryID, int patronID, const std::tm& dueDate);

    // Getters
    int getLoanID() const;
    int getLibraryID() const;
    int getPatronID() const;
    std::tm getDueDate() const;
    LoanStatus getStatus() const;

    // Setters
    void setLoanID(int id);
    void setLibraryID(int id);
    void setPatronID(int id);
    void setDueDate(const std::tm& date);
    void setStatus(LoanStatus status);

private:
    static int nextLoanID; // Static member to track the next available loan ID
    int loanID;
    int libraryID;  // Changed from bookID to libraryID
    int patronID;
    std::tm dueDate;
    LoanStatus status;
};

#endif // LOANS_H
