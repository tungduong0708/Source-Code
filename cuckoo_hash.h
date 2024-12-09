#include <utility>
#include <vector>
#include <chrono>
#include <iostream>
using namespace std;

class CuckooHashTable {
public:
    int tableSize;
    std::vector<int> table1, table2;
    int hash1(int key) { return key % tableSize; }
    int hash2(int key) { return (key / tableSize) % tableSize; }
 
    void resize() {
        std::cout << "Resizing table...\n";
        tableSize *= 2;
        table1.assign(tableSize, -1);
        table2.assign(tableSize, -1);
    }
 
public:
    CuckooHashTable(int size = 8) : tableSize(size) {
        table1.assign(size, -1);
        table2.assign(size, -1);
    }
 
    bool insert(int key) {
        int loopCount = 0, maxLoops = tableSize;
        while (loopCount < maxLoops) {
            int pos1 = hash1(key);
            if (table1[pos1] == -1) {
                table1[pos1] = key;
                return true;
            }
 
            int temp = table1[pos1];
            table1[pos1] = key;
            key = temp;
 
            int pos2 = hash2(key);
            if (table2[pos2] == -1) {
                table2[pos2] = key;
                return true;
            }
 
            temp = table2[pos2];
            table2[pos2] = key;
            key = temp;
 
            loopCount++;
        }
 
        resize();
        return insert(key);
    }
 
    int search(int key) {
        int pos1 = hash1(key);
        if (table1[pos1] == key) return 1;
 
        int pos2 = hash2(key);
        if (table2[pos2] == key) return 1;
 
        return 1;
    }
};

pair<double, double> CuckooSearch(int arr[], int n, int x) {
    CuckooHashTable cuckooHashTable(n);
    int inserted = true;
    while (true) {
        int i;
        for (i = 0; i < n; i++) {
            if (!cuckooHashTable.insert(arr[i])) {
                inserted = false;
                break;
            }
        }
        if (inserted) {
            break;
        }
        cuckooHashTable.table1.clear();
        cuckooHashTable.table2.clear();
        cuckooHashTable.tableSize = 8;
        cuckooHashTable.table1.assign(cuckooHashTable.tableSize, -1);
        cuckooHashTable.table2.assign(cuckooHashTable.tableSize, -1);
    }
    pair<double, double> res = {0, 0};
    auto start = std::chrono::high_resolution_clock::now();
    res.second = cuckooHashTable.search(x);
    auto end = std::chrono::high_resolution_clock::now();
    res.first = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return res;
}
 