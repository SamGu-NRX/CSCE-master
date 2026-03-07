# Assignment: Hospital Patient Management System Using Queue, Stack, and Hash Table (C++)

## Objective

Design and implement a **Hospital Patient Management System** using linked lists and a manually implemented hash table.

This system simulates the patient flow in a hospital pharmacy where:

- Patients wait in line to receive medication (**Queue → FIFO**)
- Patients may be temporarily skipped due to missing documentation or payment issues (**Stack → LIFO**)
- Hospital staff must be able to **quickly look up** any patient by their **ID number** (**Hash Table → O(1) Search**)

This assignment reinforces understanding of **dynamic memory, linked lists, and hash-based indexing**, without relying on STL containers.

---

## Provided Files

You will be given the following files:

- `template.cpp` — Starter code that includes data structures and menu framework with `// TODO` sections to be completed
- `patients.txt` — Contains the initial list of patients loaded into the system

(Original distribution included links to download these files.)

File table:

| File Name     | Description                                      |
|---------------|--------------------------------------------------|
| patients.txt  | Contains the initial list of patients to load    |
| template.cpp  | Starter code; contains TODO sections to complete |

---

## Requirements

### 1. Initialization

- Implement an `init()` function that reads `patients.txt`.
- For each record in `patients.txt`:
  - Insert the patient into the Queue (`waitList`).
  - Insert the patient into the Hash Table (`lookupTable`).
- Keep track of the number of patients in the queue.

### 2. Data Structures

Define:

```cpp
struct Patient {
  int id;
  string name;
  Patient* next;
};
```

You must manually implement the following ADTs (do NOT use the STL containers listed below):

- Queue (`waitList`): FIFO — patients waiting to pick up medication — implemented as a linked list with head & tail pointers.
- Stack (`skipList`): LIFO — patients who were skipped and will return — implemented as a linked list with a top pointer.
- Hash Table (`lookupTable`): O(1) search — fast lookup of patient by ID — manual implementation (chaining or open addressing).

Implementation table:

| Structure                       | ADT Behavior | Purpose                                       | Implementation                     |
|---------------------------------|--------------|-----------------------------------------------|------------------------------------|
| Queue (`waitList`)              | FIFO         | Patients waiting to pick up medication        | Linked list (head & tail)          |
| Stack (`skipList`)              | LIFO         | Patients who were skipped and will return     | Linked list (top pointer)          |
| Hash Table (`lookupTable`)      | O(1) search  | Fast lookup of patient by ID                  | Manual implementation (chaining or open addressing) |

You may NOT use:

- `std::queue`
- `std::stack`
- `std::list`
- `std::vector`
- `std::unordered_map`
- `std::map`

---

## Menu Operations

Your program must display the following menu:

```text
===== Hospital Patient Management System =====
1. Serve next patient
2. Skip current patient (move to skip list)
3. Process returning skipped patient
4. Search patient by ID (using hash table)
5. View next patient in line
6. View most recently skipped patient
0. Exit
```

Options detail:

| Option | Description                                 | Data Structure Used |
|--------|---------------------------------------------|---------------------|
| 1      | Remove and display the front of the queue   | Queue               |
| 2      | Move the front of the queue into the stack  | Queue → Stack       |
| 3      | Pop from stack and serve immediately        | Stack               |
| 4      | Look up and display patient info by ID      | Hash Table          |
| 5      | Display the next patient without removal    | Queue               |
| 6      | Display most recently skipped patient       | Stack               |
| 0      | Exit                                        | —                   |

---

## Error Handling

- Prevent serving from an empty queue — show a clear message.
- Prevent restoring from an empty stack — show a clear message.
- If a patient ID is not found during a lookup, print a clear "not found" message.

---

## What to Submit

Submit to Canvas → Assignment: Hospital Patient System (Linked Lists & Hash Table)

Upload:
- `kg0909.cpp`

---

## Grading Rubric (100 Points)

| Component                        | Weight | Evaluation Criteria                                           |
|----------------------------------|--------|---------------------------------------------------------------|
| Stack Implementation (LIFO)      | 30%    | Correct push/pop/top logic, proper memory handling           |
| Queue Implementation (FIFO)      | 30%    | Correct enqueue/dequeue/front logic, pointer correctness     |
| Hash Table Implementation        | 40%    | Must be manually implemented; supports insert/search; no STL hashing allowed |


