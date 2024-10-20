#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;
    int currentSize;
    int elementCount;
    static const double LOAD_FACTOR_THRESHOLD; // Make it a static constant

    int hashFunction(int key) {
        return key % currentSize;
    }

    bool isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

    int getNextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    void resize() {
        int newSize = getNextPrime(currentSize * 2);
        std::vector<int> newTable(newSize, -1);
        int oldSize = currentSize;

        currentSize = newSize;
        elementCount = 0;

        for (int i = 0; i < oldSize; i++) {
            if (table[i] != -1) {
                insert(table[i]);
            }
        }
        table.swap(newTable);
    }

public:
    HashTable(int size) {
        currentSize = getNextPrime(size);
        table.resize(currentSize, -1);
        elementCount = 0;
    }

    // Copy constructor
    HashTable(const HashTable& other) = default;

    // Move constructor
    HashTable(HashTable&& other) noexcept = default;

    // Copy assignment operator
    HashTable& operator=(const HashTable& other) = default;

    // Move assignment operator
    HashTable& operator=(HashTable&& other) noexcept = default;

    void insert(int key) {
        if (elementCount >= currentSize * LOAD_FACTOR_THRESHOLD) {
            resize();
        }

        int index = hashFunction(key);
        int i = 0;
        while (i < currentSize) {
            int newIndex = (index + i * i) % currentSize;
            if (table[newIndex] == -1) {
                table[newIndex] = key;
                elementCount++;
                return;
            } else if (table[newIndex] == key) {
                std::cout << "Duplicate key insertion is not allowed" << std::endl;
                return;
            }
            i++;
        }
        std::cout << "Max probing limit reached!" << std::endl;
    }

    void remove(int key) {
        int index = hashFunction(key);
        int i = 0;
        while (i < currentSize) {
            int newIndex = (index + i * i) % currentSize;
            if (table[newIndex] == -1) {
                std::cout << "Element not found" << std::endl;
                return;
            } else if (table[newIndex] == key) {
                table[newIndex] = -1;
                elementCount--;
                return;
            }
            i++;
        }
        std::cout << "Element not found" << std::endl;
    }

    int search(int key) {
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

    void printTable() {
        for (int i = 0; i < currentSize; i++) {
            if (table[i] == -1) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};

// Define the static constant
const double HashTable::LOAD_FACTOR_THRESHOLD = 0.8;

#endif
