# Implementation Comparison

## Simple Version vs OOP Version

### Simple Version (`library_system.cpp`)

**Pros:**

- ✓ Matches assignment requirements exactly
- ✓ Single file (341 lines) - easy to submit as `EUID.cpp`
- ✓ Uses `Book` struct as specified
- ✓ Straightforward, easy to understand
- ✓ All functionality in one place

**Structure:**

- Book struct (not class)
- Global variables for lists
- Modular functions
- No encapsulation needed

**Best for:**

- Assignment submission
- Learning linked lists
- Simple requirements

---

### OOP Version (Multi-file)

**Pros:**

- ✓ Professional code organization
- ✓ Proper encapsulation
- ✓ Reusable components
- ✓ Comprehensive test suite (18 tests)
- ✓ Better for large projects

**Structure:**

- Book class with private members
- Library class managing operations
- Separate header files
- Google Test integration

**Best for:**

- Portfolio projects
- Team development
- Scalable systems

---

## Recommendation

**For this assignment**: Use `library_system.cpp`

- It's what the requirements ask for
- Single file submission
- Uses struct (not class)
- Simpler and clearer

**For learning/portfolio**: Use the OOP version

- Better software engineering practices
- Includes automated testing
- More maintainable

---

## Key Differences

| Feature              | Simple  | OOP      |
| -------------------- | ------- | -------- |
| Files                | 1       | 5        |
| Lines of code        | 341     | 353      |
| Book type            | struct  | class    |
| Encapsulation        | No      | Yes      |
| Tests                | No      | 18 tests |
| Complexity           | Low     | Medium   |
| Matches requirements | Exactly | Enhanced |
