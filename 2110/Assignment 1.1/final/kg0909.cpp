// CSCE 2110.003
// Kai Gu (kg0909, 11797431)
// Nov 7, 2025
// TA: Yongshuo Liu

// P.S. I used try-catch since I am more familiar with it (JS).

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Book struct
struct Book {
    string title;
    string author;
    int year;
    double price;
    Book* next;
};

// Global lists
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
void cleanup();
string sanitizePriceString(const string& rawPrice);
bool bookExistsAnywhere(const string& title);

// -----DIVIDER-----

int main() {
    init();
    cout << "Welcome to the Library Management System. \n";
    int choice;
    do {
        displayMenu();
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

// Helper: Trim whitespace from both ends of string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

// Helper: Remove currency symbols and spacing from price strings
string sanitizePriceString(const string& rawPrice) {
    string cleaned;
    // nice trick
    for (char c : rawPrice) {
        if ((c >= '0' && c <= '9') || c == '.' || c == '-') {
            cleaned += c;
        }
    }
    return cleaned;
}

// Helper: Detect if a book title exists in any list
bool bookExistsAnywhere(const string& title) {
    return searchBook(mainList, title) != nullptr || searchBook(rentList, title) != nullptr;
}

// Initialize library from file
void init() {
    ifstream file("real_books_inventory.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open real_books_inventory.txt\n";
        return;
    }

    string line;
    int lineNum = 0;
    while (getline(file, line)) {
        lineNum++;
        if (line.empty() || line.find_first_not_of(" \t\r\n") == string::npos) {
            continue; // Skip empty lines
        }

        stringstream ss(line);
        string title, author, yearStr, priceStr;

        // File format: Title, Author, Year, Price
        if (!getline(ss, title, ',')) continue;
        if (!getline(ss, author, ',')) continue;
        if (!getline(ss, yearStr, ',')) continue;
        if (!getline(ss, priceStr, ',')) {
            getline(ss, priceStr); // Last field does not have comma
        }

        // Trim whitespace
        title = trim(title);
        author = trim(author);
        yearStr = trim(yearStr);
        priceStr = trim(priceStr);

        // Guardrail: Skip if any field is empty (prolly smth went wrong)
        if (title.empty() || author.empty() || yearStr.empty() || priceStr.empty()) {
            cout << "Warning: Skipping line " << lineNum << " due to missing fields\n";
            continue;
        }

        try {
            // reference: https://en.cppreference.com/w/cpp/string/basic_string/stol
            int year = stoi(yearStr);
            string cleanPrice = sanitizePriceString(priceStr);
            if (cleanPrice.empty()) {
                throw invalid_argument("price contains no digits");
            }
            double price = stod(cleanPrice);

            addBook(mainList, title, author, year, price);
            totalBooks++;
        } catch (const exception& e) {
            cout << "Warning: Skipping line " << lineNum << " - " << e.what() << "\n";
            cout << "Line content: " << line << "\n";
        }
    }

    file.close();
    cout << "Library initialized with " << totalBooks << " books.\n";
}

// Display menu
void displayMenu() {
    cout << "Below are the options. Type integer between 1 and 7 to choose.\n";
    cout << "1. Buy a Book\n";
    cout << "2. Sell a Book\n";
    cout << "3. Rent a Book\n";
    cout << "4. Return a Book\n";
    cout << "5. Display Available Books\n";
    cout << "6. Display Rented Books\n";
    cout << "7. Exit\n";
}

// Buy a book (remove from mainList)
void buyBook() {
    string title;
    cout << "\nEnter the title of the book to buy: ";
    getline(cin, title);
    title = trim(title);
    if (title.empty()) {
        cout << "Title cannot be empty.\n";
        return;
    }

    Book* book = searchBook(mainList, title);
    if (book == nullptr) {
        cout << "Book not available in inventory.\n";
        return;
    }

    cout << "Book found: " << book->title << " by " << book->author
         << " ($" << book->price << ")\n";
    deleteBook(mainList, title);
    if (totalBooks > 0) {
        totalBooks--;
    }
    cout << "Book purchased\n";
}

// Sell a book (add to mainList)
void sellBook() {
    string title, author, yearStr, priceStr;
    int year;
    double price;

    cout << "\nEnter book details:\n";
    cout << "Title: ";
    getline(cin, title);
    title = trim(title);
    if (title.empty()) {
        cout << "Title cannot be empty.\n";
        return;
    }

    // Guardrail: Check for duplicate in both lists
    if (bookExistsAnywhere(title)) {
        cout << "This book already exists\n";
        return;
    }

    cout << "Author: ";
    getline(cin, author);
    author = trim(author);
    if (author.empty()) {
        cout << "Author cannot be empty.\n";
        return;
    }

    cout << "Year: ";
    getline(cin, yearStr);
    yearStr = trim(yearStr);
    try {
        year = stoi(yearStr);
    } catch (const exception&) {
        cout << "Invalid year entered.\n";
        return;
    }

    cout << "Price: ";
    getline(cin, priceStr);
    priceStr = trim(priceStr);

    try {
        string cleanPrice = sanitizePriceString(priceStr);
        if (cleanPrice.empty()) {
            throw invalid_argument("price contains no digits");
        }
        price = stod(cleanPrice);
    } catch (const exception&) {
        cout << "Invalid price entered.\n";
        return;
    }

    // Price guardrail
    if (price < 0) {
        cout << "Price must be non-negative.\n";
        return;
    }

    addBook(mainList, title, author, year, price);
    totalBooks++;
    cout << "Book added to inventory successfully!\n";
}

// Rent a book (move from mainList to rentList)
void rentBook() {
    string title;
    cout << "\nEnter the title of the book to rent: ";
    getline(cin, title);
    title = trim(title);

    if (title.empty()) {
        cout << "Title cannot be empty.\n";
        return;
    }

    Book* book = searchBook(mainList, title);
    if (book == nullptr) {
        cout << "Book not available for rent.\n";
        return;
    }

    cout << "Book found: " << book->title << " by " << book->author
         << " ($" << book->price << ")\n";
    moveBook(mainList, rentList, title);
    if (totalBooks > 0) {
        totalBooks--;
    }
    cout << "Book rented!\n";
}

// Return a book (move from rentList to mainList)
void returnBook() {
    string title;
    cout << "\nEnter the title of the book to return: ";
    getline(cin, title);
    title = trim(title);

    if (title.empty()) {
        cout << "Title cannot be empty.\n";
        return;
    }

    Book* book = searchBook(rentList, title);
    if (book == nullptr) {
        cout << "This book is not in the rented list.\n";
        return;
    }

    cout << "Book found: " << book->title << " by " << book->author << "\n";
    moveBook(rentList, mainList, title);
    totalBooks++;
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

    // edge case: If head node is to be deleted
    if (head->title == title) {
        Book* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    // Search for the node to delete
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

    // Store book details
    string bookTitle = book->title;
    string bookAuthor = book->author;
    int bookYear = book->year;
    double bookPrice = book->price;

    // Delete from source list
    deleteBook(fromList, title);

    // Add to destination list
    addBook(toList, bookTitle, bookAuthor, bookYear, bookPrice);
}

// Helper: Cleanup memory
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
