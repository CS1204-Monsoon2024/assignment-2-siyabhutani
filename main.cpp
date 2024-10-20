#include "HashTable.h"

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
