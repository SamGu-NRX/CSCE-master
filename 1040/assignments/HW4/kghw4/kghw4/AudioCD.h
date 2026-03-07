// AudioCD.h

#ifndef AUDIOCD_H
#define AUDIOCD_H

#include "LibraryItems.h"
#include <string>
#include <ctime>

using namespace std;

class AudioCD : public LibraryItems {
private:
    string artist;
    string title;
    int numTracks;
    std::tm releaseDate;
    string genre;

public:
    // Constructor
    AudioCD(const string& artist, const string& title, int numTracks, const std::tm& releaseDate, const string& genre,
            int libraryID, float cost, ItemStatus status = IN, int loanPeriod = 7);

    // Accessors
    string getArtist() const;
    string getTitle() const override;
    int getNumTracks() const;
    std::tm getReleaseDate() const;
    string getGenre() const;

    // Mutators
    void setArtist(const string& artist);
    void setTitle(const string& title) override;
    void setNumTracks(int numTracks);
    void setReleaseDate(const std::tm& releaseDate);
    void setGenre(const string& genre);

    // Overridden Function
    void displayItemInfo() const override;
};

#endif // AUDIOCD_H
