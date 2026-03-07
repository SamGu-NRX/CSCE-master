# Library Management System Tests

This directory contains the Google Test suite for the Library Management System.

## Test Framework

- **GoogleTest v1.17.0** - Located at `../googletest-v1.17.0`
- **C++ Standard**: C++17 (required by GoogleTest v1.17.0)

## Test Structure

### BookTest Fixture

Tests for the Book class functionality:

- Constructor initialization
- Getter methods
- Next pointer management
- Display output formatting

### LibraryTest Fixture

Tests for the Library class functionality:

- File initialization and loading
- Book search operations
- List management (mainList and rentList)
- Edge cases (empty lines, price formats)
- Data integrity
- Memory management

## Running Tests

From the project root directory:

```bash
make test
```

This will:

1. Build the GoogleTest library
2. Compile the test suite
3. Execute all tests
4. Display results

## Test Coverage

The test suite covers:

- ✓ Book class encapsulation
- ✓ Library initialization from file
- ✓ CSV parsing with various formats
- ✓ Price handling (with/without $ sign)
- ✓ Linked list operations
- ✓ Memory management
- ✓ Error handling
- ✓ Data integrity

## Adding New Tests

To add new tests, edit `library_test.cpp` and follow the GoogleTest patterns:

```cpp
TEST_F(LibraryTest, YourTestName) {
    // Arrange
    library->init();

    // Act
    // ... perform operations

    // Assert
    EXPECT_EQ(expected, actual);
}
```

## Build Artifacts

Test executable: `run_tests`

Clean build artifacts:

```bash
make clean
```
