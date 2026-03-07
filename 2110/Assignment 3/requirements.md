# Texas City Navigation System – Project Requirements

## Overview

You will implement a **Texas city navigation system** using **graph traversal**.
A directed graph of Texas cities is provided in `graph.txt`.

Your tasks involve determining city connections by implementing **either BFS or DFS**, depending on which is more appropriate for each requirement.

**You MUST select BFS or DFS for each task and justify your choice with comments in your code.**

---

## Provided Files

| File        | Purpose                                              |
| ----------- | ---------------------------------------------------- |
| `main.cpp`  | Starter code — data loading is fully implemented     |
| `graph.txt` | Texas city graph using adjacency list representation |

---

## Tasks

### **Task 1 – Route Discovery**

**Goal:**
Given two cities entered by the user, determine **if a route exists** and display the traversal order.

**Example input:**

```
Enter start city: El_Paso
Enter destination city: Houston
```

**Example output:**

```
Visited: El_Paso -> DFW -> Houston
Route Found!
```

**Requirements:**

* Choose **BFS or DFS**.
* Add a **comment explaining why** your choice is appropriate
  (e.g., *BFS finds shortest path in terms of number of edges*).

---

### **Task 2 – Reachability**

**Goal:**
Ask the user for a starting city and list **all reachable cities**.

**Example input/output:**

```
Enter start city: Austin
Reachable cities:
Houston
OKC
```

**Requirements:**

* Choose **BFS or DFS**.
* Justify the choice in comments
  (e.g., *DFS explores deeper connections before backtracking*).

---

## Submission Requirements

Submit the following:

| Required File | Notes                  |
| ------------- | ---------------------- |
| `kg0909.cpp`    | Your completed program |
| `graph.txt`   | Provided graph         |

---

## Grading Rubric (100 Points)

| Component                     | Points | Criteria                              |
| ----------------------------- | ------ | ------------------------------------- |
| Correct BFS/DFS use in Task 1 | 40     | Correct logic + valid justification   |
| Correct BFS/DFS use in Task 2 | 40     | Proper traversal + reasoning          |
| Code readability + comments   | 20     | Clean, formatted, meaningful comments |
