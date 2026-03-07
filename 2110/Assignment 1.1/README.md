# Library Management System

A C++ implementation of a library management system using linked lists.

## Two Implementations

### 1. Simple Version (Recommended for Assignment)

**File**: `library_system.cpp`

- Single file implementation
- Uses `Book` struct as specified in requirements
- Modular functions
- Matches assignment requirements exactly

### 2. OOP Version (Advanced)

**Files**: `Book.h`, `Book.cpp`, `Library.h`, `Library.cpp`, `main.cpp`

- Multi-file with proper class encapsulation
- Book as a class with private members
- Library class managing operations
- Includes comprehensive Google Test suite

## Implementation Details

### Simple Version (`library_system.cpp`)

- **Book struct** with: title, author, year, price, next pointer
- **Global lists**: mainList (available), rentList (rented)
- **Modular functions** for each operation
- Single file for easy submission

### OOP Version (Multi-file)

- **Book class** with private members and public interface
- **Library class** managing both lists
- Proper encapsulation and separation of concerns

## Requirements

- **C++ Standard**: C++17
- **Compiler**: g++ with C++17 support
- **GoogleTest**: v1.17.0 (for OOP version testing only)

## Quick Start (Simple Version)

```bash
make              # Builds library_system
make run          # Runs the simple version
```

## OOP Version

```bash
make oop          # Builds library_management
make run-oop      # Runs the OOP version
make test         # Runs Google Test suite (OOP version only)
```

## Features

1. **Buy a Book** - Remove book from inventory
2. **Sell a Book** - Add new book to inventory (with duplicate checking)
3. **Rent a Book** - Move book from available to rented list
4. **Return a Book** - Move book from rented back to available list
5. **Display Available Books** - Show all books in main inventory
6. **Display Rented Books** - Show all currently rented books

## Data Structure

- Uses singly linked lists
- Two separate lists: `mainList` (available) and `rentList` (rented)
- Reads initial inventory from `real_books_inventory.txt`

## Clean Up

```bash
make clean
```
