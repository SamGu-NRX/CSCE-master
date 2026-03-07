#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Book struct
struct Book {
    string title;
    string author;
    int year;
    double price;
    Book* next;
};

// Global linked lists
Book* mainList = nullptr;
Book* rentList = nullptr;
int totalBooks = 0;

// Function prototypes
void init();
void displayMenu();
void buyBook();
void sellBook();
void rentBook();
void returnBook();
void displayBooks(Book* head, const string& listName);
Book* searchBook(Book* head, const string& title);
void deleteBook(Book*& head, const string& title);
void addBook(Book*& head, const string& title, const string& author, int year, double price);
void moveBook(Book*& fromList, Book*& toList, const string& title);
string trim(const string& str);
void cleanup();

int main() {
    init();

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1:
                buyBook();
                break;
            case 2:
                sellBook();
                break;
            case 3:
                rentBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                displayBooks(mainList, "Available Books");
                break;
            case 6:
                displayBooks(rentList, "Rented Books");
                break;
            case 7:
                cout << "\nThank you for using the Library Management System!\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while(choice != 7);

    cleanup();
    return 0;
}

// Trim whitespace from string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

// Initialize library from file
void init() {
    ifstream file("real_books_inventory.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open real_books_inventory.txt\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string title, author, yearStr, priceStr;

        // Parse CSV: Title, Author, Year, Price
        if (!getline(ss, title, ',')) continue;
        if (!getline(ss, author, ',')) continue;
        if (!getline(ss, yearStr, ',')) continue;
        if (!getline(ss, priceStr, ',')) {
            getline(ss, priceStr);
        }

        // Clean whitespace
        title = trim(title);
        author = trim(author);
        yearStr = trim(yearStr);
        priceStr = trim(priceStr);

        // Remove dollar sign if present
        if (!priceStr.empty() && priceStr[0] == '$') {
            priceStr = priceStr.substr(1);
        }

        if (title.empty() || author.empty() || yearStr.empty() || priceStr.empty()) {
            continue;
        }

        try {
            int year = stoi(yearStr);
            double price = stod(priceStr);
            addBook(mainList, title, author, year, price);
            totalBooks++;
        } catch (...) {
            continue;
        }
    }

    file.close();
    cout << "Library initialized with " << totalBooks << " books.\n";
}

// Display menu
void displayMenu() {
    cout << "\n========== Library Management System ==========\n";
    cout << "1. Buy a Book\n";
    cout << "2. Sell a Book\n";
    cout << "3. Rent a Book\n";
    cout << "4. Return a Book\n";
    cout << "5. Display Available Books\n";
    cout << "6. Display Rented Books\n";
    cout << "7. Exit\n";
    cout << "===============================================\n";
}

// Buy a book - delete from mainList
void buyBook() {
    string title;
    cout << "\nEnter the title of the book to buy: ";
    getline(cin, title);

    Book* book = searchBook(mainList, title);
    if (book == nullptr) {
        cout << "Book not available in inventory.\n";
        return;
    }

    cout << "Book found: " << book->title << " by " << book->author
         << " ($" << book->price << ")\n";
    deleteBook(mainList, title);
    totalBooks--;
    cout << "Book purchased successfully!\n";
}

// Sell a book - add to mainList
void sellBook() {
    string title, author, yearStr, priceStr;

    cout << "\nEnter book details:\n";
    cout << "Title: ";
    getline(cin, title);

    // Check for duplicate
    if (searchBook(mainList, title) != nullptr) {
        cout << "This book already exists in inventory.\n";
        return;
    }

    cout << "Author: ";
    getline(cin, author);
    cout << "Year: ";
    getline(cin, yearStr);
    cout << "Price: ";
    getline(cin, priceStr);

    int year = stoi(yearStr);
    double price = stod(priceStr);

    addBook(mainList, title, author, year, price);
    totalBooks++;
    cout << "Book added to inventory successfully!\n";
}

// Rent a book - move from mainList to rentList
void rentBook() {
    string title;
    cout << "\nEnter the title of the book to rent: ";
    getline(cin, title);

    Book* book = searchBook(mainList, title);
    if (book == nullptr) {
        cout << "Book not available for rent.\n";
        return;
    }

    cout << "Book found: " << book->title << " by " << book->author
         << " ($" << book->price << ")\n";
    moveBook(mainList, rentList, title);
    cout << "Book rented successfully!\n";
}

// Return a book - move from rentList to mainList
void returnBook() {
    string title;
    cout << "\nEnter the title of the book to return: ";
    getline(cin, title);

    Book* book = searchBook(rentList, title);
    if (book == nullptr) {
        cout << "This book is not in the rented list.\n";
        return;
    }

    cout << "Book found: " << book->title << " by " << book->author << "\n";
    moveBook(rentList, mainList, title);
    cout << "Book returned successfully!\n";
}

// Display all books in a list
void displayBooks(Book* head, const string& listName) {
    cout << "\n========== " << listName << " ==========\n";
    if (head == nullptr) {
        cout << "No books in this list.\n";
        return;
    }

    Book* current = head;
    int count = 1;
    while (current != nullptr) {
        cout << count++ << ". " << current->title << " by " << current->author
             << " (" << current->year << ") - $" << current->price << "\n";
        current = current->next;
    }
}

// Search for a book by title
Book* searchBook(Book* head, const string& title) {
    Book* current = head;
    while (current != nullptr) {
        if (current->title == title) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Delete a book from list
void deleteBook(Book*& head, const string& title) {
    if (head == nullptr) return;

    // If head node matches
    if (head->title == title) {
        Book* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    // Search for the node
    Book* current = head;
    while (current->next != nullptr && current->next->title != title) {
        current = current->next;
    }

    if (current->next != nullptr) {
        Book* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

// Add a book to list
void addBook(Book*& head, const string& title, const string& author, int year, double price) {
    Book* newBook = new Book;
    newBook->title = title;
    newBook->author = author;
    newBook->year = year;
    newBook->price = price;
    newBook->next = nullptr;

    if (head == nullptr) {
        head = newBook;
    } else {
        Book* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newBook;
    }
}

// Move book from one list to another
void moveBook(Book*& fromList, Book*& toList, const string& title) {
    Book* book = searchBook(fromList, title);
    if (book == nullptr) return;

    // Store book data
    string bookTitle = book->title;
    string bookAuthor = book->author;
    int bookYear = book->year;
    double bookPrice = book->price;

    // Delete from source
    deleteBook(fromList, title);

    // Add to destination
    addBook(toList, bookTitle, bookAuthor, bookYear, bookPrice);
}

// Cleanup memory
void cleanup() {
    Book* current = mainList;
    while (current != nullptr) {
        Book* temp = current;
        current = current->next;
        delete temp;
    }

    current = rentList;
    while (current != nullptr) {
        Book* temp = current;
        current = current->next;
        delete temp;
    }
}
