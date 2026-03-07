# Assignment: Library Management System Using Linked Lists in C++

## Objective

Design and implement a **Library Management System** using linked lists in C++.
Students will simulate a book inventory system that supports operations like **buying, selling, renting, and returning books**.

## Provided file

Download the initial book inventory file here: `real_books_inventory.txt`.
This file contains 50 books with the following format: `Title, Author, Year of Publication, Price`.

---

## Requirements

### 1. Initialization

* Create an `init()` function to read the `real_books_inventory.txt` file.
* Store each book as a node in a **singly linked list**.
* Keep a count of total books available.

### 2. Data Structures

* Use a `Book` **struct** with fields:

  * `title`
  * `author`
  * `year`
  * `price`
  * `next` pointer
* Maintain two linked lists:

  * `mainList` — for available books
  * `rentList` — for rented books

### 3. Menu Operations

Create a **Menu** which will provide the following options to the Customer:

* **Buy a Book**: Search and delete from `mainList`. Handle situation when book is not available.
* **Sell a Book**: Add a new node to `mainList` about the sold book.
* **Rent a Book**: Move node from `mainList` to `rentList`.
* **Return a Book**: Move node from `rentList` back to `mainList`.

### 4. Error Handling

* Ensure proper checks for book existence before operations.
* Prevent duplicate entries when selling.

### 5. Code Structure

* Use **modular functions** for each operation.
* Maintain clean and readable code with **meaningful comments**.

---

## Submission

Now that you have completed this assignment, it’s time to turn in your results. Submit them to Canvas for the **Assignment 1: Linked List** dropbox. You should submit the following files:

* `EUID.cpp` (EUID → Individual student’s EUID)

---

## Grading Rubric (100 Points)

|                         Criteria | Points |
| -------------------------------: | -----: |
|         Initialization from file |     10 |
| Linked list creation & structure |     15 |
|            Menu-driven interface |     10 |
|                    Buy operation |     10 |
|                   Sell operation |     10 |
|                   Rent operation |     10 |
|                 Return operation |     10 |
|                   Error handling |     10 |
|    Code readability & modularity |     15 |

---

Source / original file:
