// DVD.cpp

#include "DVD.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Constructor
DVD::DVD(const string& title, const string& category, int runTime, const string& studio, const std::tm& releaseDate,
         int libraryID, float cost, ItemStatus status, int loanPeriod)
    : LibraryItems(libraryID, cost, status, loanPeriod), title(title), category(category), runTime(runTime), studio(studio), releaseDate(releaseDate) {
}

// Accessors
string DVD::getTitle() const {
    return title;
}

string DVD::getCategory() const {
    return category;
}

int DVD::getRunTime() const {
    return runTime;
}

string DVD::getStudio() const {
    return studio;
}

std::tm DVD::getReleaseDate() const {
    return releaseDate;
}

// Mutators
void DVD::setTitle(const string& newTitle) {
    title = newTitle;
}

void DVD::setCategory(const string& newCategory) {
    category = newCategory;
}

void DVD::setRunTime(int newRunTime) {
    runTime = newRunTime;
}

void DVD::setStudio(const string& newStudio) {
    studio = newStudio;
}

void DVD::setReleaseDate(const std::tm& newReleaseDate) {
    releaseDate = newReleaseDate;
}

// Overridden Function
void DVD::displayItemInfo() const {
    std::cout << "DVD ID: " << getLibraryID() << "\n"
              << "Title: " << title << "\n"
              << "Category: " << category << "\n"
              << "Run Time: " << runTime << " minutes\n"
              << "Studio: " << studio << "\n"
              << "Release Date: " << std::put_time(&releaseDate, "%Y-%m-%d") << "\n"
              << "Cost: $" << getCost() << "\n"
              << "Loan Period: " << getLoanPeriod() << " days\n"
              << "Status: " << (getStatus() == IN ? "IN" : (getStatus() == OUT ? "OUT" : "LOST")) << "\n";
}
