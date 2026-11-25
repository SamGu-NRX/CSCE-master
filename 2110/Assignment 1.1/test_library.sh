#!/bin/bash

echo "Testing Library Management System"
echo "=================================="
echo ""

# Test 1: Display available books
echo "Test 1: Display available books (option 5, then 7 to exit)"
echo -e "5\n7" | ./library_management

echo ""
echo "=================================="
echo ""

# Test 2: Rent a book
echo "Test 2: Rent a book, then display rented books"
echo "Renting: To Kill a Mockingbird"
echo -e "3\nTo Kill a Mockingbird\n6\n7" | ./library_management

echo ""
echo "=================================="
echo ""

# Test 3: Try to buy a non-existent book
echo "Test 3: Try to buy a non-existent book"
echo -e "1\nNonexistent Book\n7" | ./library_management

echo ""
echo "=================================="
echo ""

# Test 4: Sell a new book
echo "Test 4: Sell a new book"
echo -e "2\nTest Book Title\nTest Author\n2024\n29.99\n5\n7" | ./library_management | tail -20

echo ""
echo "All tests completed!"
