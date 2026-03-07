// DVD.h

#ifndef DVD_H
#define DVD_H

#include "LibraryItems.h"
#include <string>
#include <ctime>

using namespace std;

class DVD : public LibraryItems {
private:
    string title;
    string category;
    int runTime; // in minutes
    string studio;
    std::tm releaseDate;

public:
    // Constructor
    DVD(const string& title, const string& category, int runTime, const string& studio, const std::tm& releaseDate,
        int libraryID, float cost, ItemStatus status = IN, int loanPeriod = 7);

    // Accessors
    string getTitle() const override;
    string getCategory() const;
    int getRunTime() const;
    string getStudio() const;
    std::tm getReleaseDate() const;

    // Mutators
    void setTitle(const string& title) override;
    void setCategory(const string& category);
    void setRunTime(int runTime);
    void setStudio(const string& studio);
    void setReleaseDate(const std::tm& releaseDate);

    // Overridden Function
    void displayItemInfo() const override;
};

#endif // DVD_H
