// AudioCD.cpp

#include "AudioCD.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Constructor
AudioCD::AudioCD(const string& artist, const string& title, int numTracks, const std::tm& releaseDate, const string& genre,
                 int libraryID, float cost, ItemStatus status, int loanPeriod)
    : LibraryItems(libraryID, cost, status, loanPeriod), artist(artist), title(title), numTracks(numTracks), releaseDate(releaseDate), genre(genre) {
}

// Accessors
string AudioCD::getArtist() const {
    return artist;
}

string AudioCD::getTitle() const {
    return title;
}

int AudioCD::getNumTracks() const {
    return numTracks;
}

std::tm AudioCD::getReleaseDate() const {
    return releaseDate;
}

string AudioCD::getGenre() const {
    return genre;
}

// Mutators
void AudioCD::setArtist(const string& newArtist) {
    artist = newArtist;
}

void AudioCD::setTitle(const string& newTitle) {
    title = newTitle;
}

void AudioCD::setNumTracks(int newNumTracks) {
    numTracks = newNumTracks;
}

void AudioCD::setReleaseDate(const std::tm& newReleaseDate) {
    releaseDate = newReleaseDate;
}

void AudioCD::setGenre(const string& newGenre) {
    genre = newGenre;
}

// Overridden Function
void AudioCD::displayItemInfo() const {
    std::cout << "Audio CD ID: " << getLibraryID() << "\n"
              << "Artist: " << artist << "\n"
              << "Title: " << title << "\n"
              << "Number of Tracks: " << numTracks << "\n"
              << "Genre: " << genre << "\n"
              << "Release Date: " << std::put_time(&releaseDate, "%Y-%m-%d") << "\n"
              << "Cost: $" << getCost() << "\n"
              << "Loan Period: " << getLoanPeriod() << " days\n"
              << "Status: " << (getStatus() == IN ? "IN" : (getStatus() == OUT ? "OUT" : "LOST")) << "\n";
}
