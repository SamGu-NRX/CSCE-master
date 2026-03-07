// main.cpp
// Kai Gu, kg0909, 12/04/2025, CSCE 2100.003 Exam 2
// Linear probing hash table implementation.

#include "hashTable.h"
#include <iostream>
using namespace std;

int menu() {
   int choice;
   cout << "1. Insert" << endl;
   cout << "2. Remove" << endl;
   cout << "3. Search" << endl;
   cout << "4. Print" << endl;
   cout << "5. Exit" << endl;
   cin >> choice;
   return choice;
}

int main() {
   HashTable hashTable;
   unsigned int key;
   int choice;

   cout << "Hash table program. Use 1-5 to navigate." << endl;

   do {
      choice = menu();
      switch(choice) {
         case 1:
            cout << "Enter a key to insert: ";
            cin >> key;
            hashTable.insert(key);
            break;
         case 2:
            cout << "Enter a key to remove: ";
            cin >> key;
            hashTable.remove(key);
            break;
         case 3:
            cout << "Enter a key to search: ";
            cin >> key;
            hashTable.search(key);
            break;
         case 4:
            hashTable.print();
            break;
         case 5:
            cout << "Exiting program." << endl;
            break;
         default:
            cout << "Invalid choice" << endl;
            break;
      }
   } while(choice != 5);
}
