// hashTable.cpp
// Kai Gu, kg0909, 12/4/2025, CSCE 2100.003 Exam 2
// Linear probing hash table implementation.

#ifndef HASHTABLE_H
#define HASHTABLE_H

// can be whatever, I have it set to the minimum value 10
const int TABLE_SIZE = 10;

class HashTable {
   private:
      int table[TABLE_SIZE];
      bool occupied[TABLE_SIZE];
      bool deleted[TABLE_SIZE];
   public:
      HashTable();
      int hash(int key);
      int linearProbe(int key, int i);
      void insert(int key);
      void remove(int key);
      void print();
      bool search(int key);
      int doubleHash(int key, int i);
};

#endif
