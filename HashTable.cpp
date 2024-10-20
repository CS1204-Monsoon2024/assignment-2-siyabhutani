#include "HashTable.h"

// Include standard libraries
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double HashTable::LOAD_FACTOR_THRESHOLD = 0.8;

HashTable::HashTable(int size) {
    currentSize = getNextPrime(size);
    table.resize(currentSize, -1); // Initialize the table with -1
    elementCount = 0;
}

int HashTable::hashFunction(int key) {
    return key % currentSize;
}

bool HashTable::isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int HashTable::getNextPrime(int n) {
    while (!isPrime(n)) {
        n++;
    }
    return n;
}

void HashTable::resize() {
    int newSize = getNextPrime(currentSize * 2);
    vector<int> newTable(newSize, -1);
    int oldSize = currentSize;

    currentSize = newSize;
    elementCount = 0;

    // Rehash existing elements
    for (int i = 0; i < oldSize; i++) {
        if (table[i] != -1) {
            insert(table[i]);
        }
    }
    table.swap(newTable);
}

void HashTable::insert(int key) {
    // Check load factor
    if (elementCount >= currentSize * LOAD_FACTOR_THRESHOLD) {
        resize();
    }

    int index = hashFunction(key);
    int i = 0;
    while (i < currentSize) {
        int newIndex = (index + i * i) % currentSize;

        if (table[newIndex] == -1) { // If spot is empty
            table[newIndex] = key;
            elementCount++;
            return;
        } else if (table[newIndex] == key) { // Duplicate key check
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
        }
        i++;
    }
    cout << "Max probing limit reached!" << endl; // If probing fails
}

void HashTable::remove(int key) {
    int index = hashFunction(key);
    int i = 0;
    while (i < currentSize) {
        int newIndex = (index + i * i) % currentSize;
        if (table[newIndex] == -1) {
            cout << "Element not found" << endl;
            return;
        } else if (table[newIndex] == key) {
            table[newIndex] = -1; // Mark as deleted
            elementCount--;
            return;
        }
        i++;
    }
    cout << "Element not found" << endl; // Not found case
}

int HashTable::search(int key) {
    int index = hashFunction(key);
    int i = 0;
    while (i < currentSize) {
        int newIndex = (index + i * i) % currentSize;
        if (table[newIndex] == -1) {
            return -1;  // Not found
        } else if (table[newIndex] == key) {
            return newIndex;  // Found
        }
        i++;
    }
    return -1;  // Not found
}

void HashTable::printTable() {
    for (int i = 0; i < currentSize; i++) {
        if (table[i] == -1) {
            cout << "- ";
        } else {
            cout << table[i] << " ";
        }
    }
    cout << endl; // Ensure the last line ends with a newline
}
