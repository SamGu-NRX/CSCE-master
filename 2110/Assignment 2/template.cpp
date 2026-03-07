#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Patient {
    int id;
    string name;
    Patient* next;
    Patient(int i, string n) : id(i), name(n), next(nullptr) {}
};

// =================== QUEUE (waitList) ===================
class Queue {
private:
    Patient* head;
    Patient* tail;
public:
    Queue() : head(nullptr), tail(nullptr) {}

    bool isEmpty() { return head == nullptr; }

    void enqueue(int id, string name) {
        // TODO: Insert new Patient to end of queue (linked list)
    }

    void dequeue() {
        // TODO: Remove head patient safely
    }

    Patient* front() {
        // TODO: return head pointer
        return nullptr;
    }
};

// =================== STACK (skipList) ===================
class Stack {
private:
    Patient* topNode;
public:
    Stack() : topNode(nullptr) {}

    bool isEmpty() { return topNode == nullptr; }

    void push(int id, string name) {
        // TODO: Insert new Patient to top of stack (linked list)
    }

    void pop() {
        // TODO: Remove top patient safely
    }

    Patient* top() {
        // TODO: return topNode
        return nullptr;
    }
};

// =================== HASH TABLE (lookupTable) ===================
const int TABLE_SIZE = 31; // small prime number for hashing

class HashTable {
private:
    Patient* table[TABLE_SIZE];
public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = nullptr;
    }

    int hashFunction(int id) {
        return id % TABLE_SIZE;
    }

    void insert(int id, string name) {
        // TODO: Insert patient into hash table using chaining
    }

    Patient* search(int id) {
        // TODO: search linked list in chosen bucket
        return nullptr;
    }
};

// =================== Initialization (Fully Implemented) ===================
void init(Queue &waitList, HashTable &lookupTable) {
    ifstream file("patients.txt");
    if (!file) {
        cout << "Error: patients.txt not found.\n";
        return;
    }

    int id;
    string name;

    while (file >> id >> name) {
        waitList.enqueue(id, name);
        lookupTable.insert(id, name);
    }

    cout << "Patient data loaded successfully.\n";
}

// =================== MENU ===================
void menu() {
    cout << "\n===== Hospital Patient Management System =====\n";
    cout << "1. Serve next patient\n";
    cout << "2. Skip current patient\n";
    cout << "3. Process returning skipped patient\n";
    cout << "4. Search patient by ID\n";
    cout << "5. View next patient in line\n";
    cout << "6. View most recently skipped patient\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Queue waitList;
    Stack skipList;
    HashTable lookupTable;

    init(waitList, lookupTable);

    int choice;
    while (true) {
        menu();
        cin >> choice;

        switch(choice) {
            case 1:
                // TODO: Queue.dequeue()
                break;
            case 2:
                // TODO: move Queue.front() -> Stack.push() -> Queue.dequeue()
                break;
            case 3:
                // TODO: Stack.pop() (serve returned patient)
                break;
            case 4: {
                cout << "Enter patient ID: ";
                int id;
                cin >> id;
                Patient* p = lookupTable.search(id);
                if (p) cout << p->id << " " << p->name << endl;
                else cout << "Patient not found.\n";
                break;
            }
            case 5:
                // TODO: Display Queue.front()
                break;
            case 6:
                // TODO: Display Stack.top()
                break;
            case 0:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}
