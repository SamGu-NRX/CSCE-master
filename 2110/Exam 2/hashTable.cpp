// hashTable.cpp
// Kai Gu, kg0909, 12/4/2025, CSCE 2100.003 Exam 2
// Linear probing hash table implementation.

#include "hashTable.h"
#include <iostream>
using namespace std;

HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = 0;
        occupied[i] = false;
        deleted[i] = false;
    }
}

int HashTable::hash(int key) {
   return key % TABLE_SIZE;
}

int HashTable::linearProbe(int key, int i) {
   return (hash(key) + i) % TABLE_SIZE;
}

int HashTable::doubleHash(int key, int i) {
   int hash2 = 1 + (key % (TABLE_SIZE - 1));
   return (hash(key) + i * hash2) % TABLE_SIZE;
}

void HashTable::insert(int key) {
   for (int i = 0; i < TABLE_SIZE; i++) {
      int index = linearProbe(key, i);

      // Insert into an empty or deleted slot
      if (!occupied[index] || deleted[index]) {
         table[index] = key;
         occupied[index] = true;
         deleted[index] = false;
         cout << "Inserted key " << key << " at table " << index << endl;
         return;
      }
   }
   cout << "Table is full, insert rejected for key " << key << endl;
}

void HashTable::remove(int key) {
   for (int i = 0; i < TABLE_SIZE; i++) {
      int index = linearProbe(key, i);

      // never was there to begin with
      if (!occupied[index] && !deleted[index]) {
         break;
      }

      if (occupied[index] && !deleted[index] && table[index] == key) {
         deleted[index] = true;
         occupied[index] = false;
         cout << "Key " << key << " removed from table " << index << endl;
         return;
      }
   }
   cout << "Key doesn't exist, remove rejected for key " << key << endl;
}

void HashTable::print() {
   for (int i = 0; i < TABLE_SIZE; i++) {
      cout << "The hash table slot " << i << " has: ";
      if (occupied[i] && !deleted[i]) {
         cout << table[i];
      } else {
         cout << "The hash table slot " << i << " is empty";
      }
      cout << endl;
   }
}

bool HashTable::search(int key) {
   for (int i = 0; i < TABLE_SIZE; i++) {
      int index = linearProbe(key, i);

      if (!occupied[index] && !deleted[index]) {
         break;
      }

      if (occupied[index] && !deleted[index] && table[index] == key) {
         cout << "Key found at table " << index << endl;
         return true;
      }
   }
   cout << "Key doesn't exist" << endl;
   return false;
}
