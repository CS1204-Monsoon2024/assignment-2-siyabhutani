#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;
    int currentSize;
    int elementCount;
    const double LOAD_FACTOR_THRESHOLD = 0.8;

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

int main() {
    HashTable ht(7);

    ht.printTable(); // Initial empty table

    ht.insert(1);
    ht.printTable(); // Should show 1 in the appropriate index

    ht.insert(4);
    ht.printTable(); // Should show 1 and 4

    ht.remove(2); // Element not found
    ht.insert(1); // Duplicate key insertion is not allowed

    ht.insert(2);
    ht.printTable(); // Should show 1, 2, 4

    ht.insert(17);
    ht.printTable(); // Should show 1, 2, 4, 17

    ht.remove(4);
    ht.printTable(); // Should show 1, 2, 17

    return 0;
}
