#include <gtest/gtest.h>
#include "../Book.h"
#include "../Library.h"
#include <fstream>
#include <sstream>

using namespace std;

// Test fixture for Book class
class BookTest : public ::testing::Test {
protected:
    Book* book;

    void SetUp() override {
        book = new Book("Test Book", "Test Author", 2024, 29.99);
    }

    void TearDown() override {
        delete book;
    }
};

// Test fixture for Library class
class LibraryTest : public ::testing::Test {
protected:
    Library* library;

    void SetUp() override {
        library = new Library();
        createTestInventoryFile();
    }

    void TearDown() override {
        delete library;
        remove("real_books_inventory.txt");
    }

    void createTestInventoryFile() {
        ofstream file("real_books_inventory.txt");
        file << "To Kill a Mockingbird, Harper Lee, 1960, $20.17\n";
        file << "1984, George Orwell, 1949, $29.31\n";
        file << "The Great Gatsby, F. Scott Fitzgerald, 1925, $43.16\n";
        file.close();
    }
};

// Book class tests
TEST_F(BookTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(book->getTitle(), "Test Book");
    EXPECT_EQ(book->getAuthor(), "Test Author");
    EXPECT_EQ(book->getYear(), 2024);
    EXPECT_DOUBLE_EQ(book->getPrice(), 29.99);
    EXPECT_EQ(book->getNext(), nullptr);
}

TEST_F(BookTest, GettersReturnCorrectValues) {
    EXPECT_EQ(book->getTitle(), "Test Book");
    EXPECT_EQ(book->getAuthor(), "Test Author");
    EXPECT_EQ(book->getYear(), 2024);
    EXPECT_DOUBLE_EQ(book->getPrice(), 29.99);
}

TEST_F(BookTest, SetNextUpdatesPointer) {
    Book* nextBook = new Book("Next Book", "Next Author", 2025, 19.99);
    book->setNext(nextBook);
    EXPECT_EQ(book->getNext(), nextBook);
    delete nextBook;
}

TEST_F(BookTest, DisplayOutputsCorrectFormat) {
    testing::internal::CaptureStdout();
    book->display();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Test Book"), string::npos);
    EXPECT_NE(output.find("Test Author"), string::npos);
    EXPECT_NE(output.find("2024"), string::npos);
    EXPECT_NE(output.find("29.99"), string::npos);
}

// Library initialization tests
TEST_F(LibraryTest, InitializationLoadsBooks) {
    library->init();
    EXPECT_NE(library->getMainList(), nullptr);
}

TEST_F(LibraryTest, InitializationLoadsCorrectNumberOfBooks) {
    library->init();
    Book* current = library->getMainList();
    int count = 0;
    while (current != nullptr) {
        count++;
        current = current->getNext();
    }
    EXPECT_EQ(count, 3);
}

TEST_F(LibraryTest, InitializationHandlesMissingFile) {
    remove("real_books_inventory.txt");
    testing::internal::CaptureStdout();
    library->init();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Error"), string::npos);
}

// Library search functionality tests
TEST_F(LibraryTest, SearchFindsExistingBook) {
    library->init();
    Book* current = library->getMainList();
    bool found = false;
    while (current != nullptr) {
        if (current->getTitle() == "1984") {
            found = true;
            break;
        }
        current = current->getNext();
    }
    EXPECT_TRUE(found);
}

TEST_F(LibraryTest, SearchDoesNotFindNonexistentBook) {
    library->init();
    Book* current = library->getMainList();
    bool found = false;
    while (current != nullptr) {
        if (current->getTitle() == "Nonexistent Book") {
            found = true;
            break;
        }
        current = current->getNext();
    }
    EXPECT_FALSE(found);
}

// Library list management tests
TEST_F(LibraryTest, RentListInitiallyEmpty) {
    library->init();
    EXPECT_EQ(library->getRentList(), nullptr);
}

TEST_F(LibraryTest, MainListNotEmptyAfterInit) {
    library->init();
    EXPECT_NE(library->getMainList(), nullptr);
}

// Edge case tests
TEST_F(LibraryTest, HandlesEmptyLines) {
    ofstream file("real_books_inventory.txt");
    file << "Book One, Author One, 2020, $10.00\n";
    file << "\n";
    file << "Book Two, Author Two, 2021, $15.00\n";
    file.close();

    library->init();
    Book* current = library->getMainList();
    int count = 0;
    while (current != nullptr) {
        count++;
        current = current->getNext();
    }
    EXPECT_EQ(count, 2);
}

TEST_F(LibraryTest, HandlesPriceWithoutDollarSign) {
    ofstream file("real_books_inventory.txt");
    file << "Test Book, Test Author, 2020, 25.50\n";
    file.close();

    library->init();
    Book* book = library->getMainList();
    ASSERT_NE(book, nullptr);
    EXPECT_DOUBLE_EQ(book->getPrice(), 25.50);
}

TEST_F(LibraryTest, HandlesPriceWithDollarSign) {
    ofstream file("real_books_inventory.txt");
    file << "Test Book, Test Author, 2020, $25.50\n";
    file.close();

    library->init();
    Book* book = library->getMainList();
    ASSERT_NE(book, nullptr);
    EXPECT_DOUBLE_EQ(book->getPrice(), 25.50);
}

// Book data integrity tests
TEST_F(LibraryTest, BooksRetainCorrectData) {
    library->init();
    Book* book = library->getMainList();
    ASSERT_NE(book, nullptr);
    EXPECT_EQ(book->getTitle(), "To Kill a Mockingbird");
    EXPECT_EQ(book->getAuthor(), "Harper Lee");
    EXPECT_EQ(book->getYear(), 1960);
    EXPECT_DOUBLE_EQ(book->getPrice(), 20.17);
}

TEST_F(LibraryTest, LinkedListMaintainsOrder) {
    library->init();
    Book* current = library->getMainList();
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->getTitle(), "To Kill a Mockingbird");

    current = current->getNext();
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->getTitle(), "1984");

    current = current->getNext();
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->getTitle(), "The Great Gatsby");
}

// Memory management tests
TEST_F(BookTest, NextPointerInitializedToNull) {
    EXPECT_EQ(book->getNext(), nullptr);
}

TEST_F(LibraryTest, DestructorCleansUpMemory) {
    Library* tempLibrary = new Library();
    tempLibrary->init();
    delete tempLibrary;
    // If this doesn't crash, memory was cleaned up properly
    SUCCEED();
}
