#ifndef LIBRARYITEMSCOLLECTION_H
#define LIBRARYITEMSCOLLECTION_H

#include "LibraryItems.h"
#include <vector>
#include <string>

using namespace std;

class LibraryItemsCollection {
private:
    vector<LibraryItems*> items;

public:
    LibraryItemsCollection();
    ~LibraryItemsCollection();

    // Generalized methods
    void AddItem();
    void EditItem();
    void DeleteItem();
    void PrintAllItems() const;
    void PrintItem();

    // Search methods
    LibraryItems* PromptForSearchMechanism();
    LibraryItems* FindItemByTitle(const string& title);
    LibraryItems* FindItemByID(int id);

    const vector<LibraryItems*>& getItems() const;
};

#endif // LIBRARYITEMSCOLLECTION_H
