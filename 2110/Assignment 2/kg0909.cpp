// CSCE 2110.003
// Kai Gu (kg0909, 11797431)
// Nov 7, 2025
// TA: Yongshuo Liu

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
        Patient* newPatient = new Patient(id, name);
        if (isEmpty()) {
            head = tail = newPatient;
        } else {
            tail->next = newPatient;
            tail = newPatient;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. No patient to serve.\n";
            return;
        }
        Patient* temp = head;
        cout << "Serving patient: " << temp->id << " " << temp->name << endl;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;
    }

    Patient* front() {
        return head;
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
        Patient* newPatient = new Patient(id, name);
        newPatient->next = topNode;
        topNode = newPatient;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Skip list is empty. No patient to process.\n";
            return;
        }
        Patient* temp = topNode;
        cout << "Processing skipped patient: " << temp->id << " " << temp->name << endl;
        topNode = topNode->next;
        delete temp;
    }

    Patient* top() {
        return topNode;
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
        int index = hashFunction(id);
        Patient* newPatient = new Patient(id, name);
        newPatient->next = table[index];
        table[index] = newPatient;
    }

    Patient* search(int id) {
        int index = hashFunction(id);
        Patient* current = table[index];
        while (current != nullptr) {
            if (current->id == id) {
                return current;
            }
            current = current->next;
        }
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
                waitList.dequeue();
                break;
            case 2: {
                if (waitList.isEmpty()) {
                    cout << "Queue is empty. No patient to skip.\n";
                } else {
                    Patient* p = waitList.front();
                    cout << "Skipping patient: " << p->id << " " << p->name << endl;
                    skipList.push(p->id, p->name);
                    waitList.dequeue();
                }
                break;
            }
            case 3:
                skipList.pop();
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
            case 5: {
                if (waitList.isEmpty()) {
                    cout << "Queue is empty. No patient in line.\n";
                } else {
                    Patient* p = waitList.front();
                    cout << "Next patient in line: " << p->id << " " << p->name << endl;
                }
                break;
            }
            case 6: {
                if (skipList.isEmpty()) {
                    cout << "Skip list is empty. No skipped patients.\n";
                } else {
                    Patient* p = skipList.top();
                    cout << "Most recently skipped patient: " << p->id << " " << p->name << endl;
                }
                break;
            }
            case 0:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}
