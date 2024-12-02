#include <utility>
#include <vector>
#include <chrono>
#include <iostream>
using namespace std;


class HashingHasedSearch {
private:
    int hashTableSize;
    std::vector<vector<int> > hashTable;
public:
    HashingHasedSearch(int size = 0) {
        hashTableSize = size;
        hashTable.assign(size,vector<int>());
    }
 
    void insert(int key) {
        int index = key % hashTableSize;
        hashTable[index].push_back(key);
    }
 
    bool search(int key) {
        int index = key % hashTableSize;
        for(int i = 0; i < hashTable[index].size(); i++) {
            if(hashTable[index][i] == key) {
                return true;
            }
        }
        return false;
    }
 
    void remove(int key) {
        int index = key % hashTableSize;
        for(int i = 0; i < hashTable[index].size(); i++) {
            if(hashTable[index][i] == key) {
                hashTable[index].erase(hashTable[index].begin() + i);
                return;
            }
        }
    }
};

class HopscotchHashTable {
public:
    struct Bucket {
        int key; // key of the element
        bool occupied; // flag to check if the bucket is occupied
        unsigned neighborhood; // bitmap to perform neighborhood search
        Bucket() : key(0), occupied(false), neighborhood(0) {}
    };
        
    int size; 
    vector<Bucket> table; 
    int neighborhoodSize; 
    int hash(int key) {
        return key % size;
    }

    void updateBitmap(int homeIndex, int oldIndex, int newIndex) {
        int oldOffset = (oldIndex - homeIndex + size) % size;
        int newOffset = (newIndex - homeIndex + size) % size;

        table[homeIndex].neighborhood &= ~(1 << oldOffset); // Clear old offset
        table[homeIndex].neighborhood |= (1 << newOffset);  // Set new offset
    }
 
public:
    HopscotchHashTable(int size = 8, int neighborhoodSize = 4) {
        this->size = size;
        this->neighborhoodSize = neighborhoodSize;
        table.assign(size, Bucket());
    }
 
    int insert(int key) {
        int i = hash(key);
        if (!table[i].occupied) {
            table[i].key = key;
            table[i].occupied = true;
            return true;
        } else {
            int j = i + 1;
            int start = j;
            while (table[j].occupied) {
                j = (j + 1) % size;
                if (j == start) return 0;  // Table is full
            }

            while (true) {
                int offset = (j - i + size) % size;
                if (offset < neighborhoodSize) {
                    int localOffset = (j - i + size) % size;
                    table[i].neighborhood |= (1 << localOffset);
                    table[j].key = key;
                    table[j].occupied = true;
                    return 1;
                }

                bool moved = false;
                for (int step = 1; step < neighborhoodSize; step++) {
                    int index = (j - neighborhoodSize + step + size) % size;

                    int baseIndex = hash(table[index].key);
                    int distance = (j - baseIndex + size) % size;
                    if (distance < neighborhoodSize) {
                        updateBitmap(baseIndex, index, j);
                        table[j] = table[index];
                        table[index] = Bucket();
                        j = index;
                        moved = true;
                        break;
                    }
                }

                if (!moved) return -1;  // Rehash needed
            }
        }
        return false;
    }

 
    int search(int key) {
        int cnt = 0;
        int hashIndex = hash(key);
        for (int i = 0; i < neighborhoodSize; i++) {
            cnt++;
            if ((table[hashIndex].neighborhood & (1 << i)) && table[(hashIndex + i) % size].occupied && table[(hashIndex + i) % size].key == key) {
                return cnt;
            }
        }

        return cnt;
    }
 
    bool remove(int key) {
        int index = hash(key);
        int distance = 0;
        while(distance < neighborhoodSize) {
            if(table[index].occupied == true && table[index].key == key) {
                table[index].occupied = false;
                int homeIndex = hash(key);
                int distance = (index - homeIndex + size) % size;
                table[homeIndex].neighborhood &= ~(1 << distance);
                return true;
            }
            index = (index + 1) % size;
            distance++;
        }
        return false;
    }


};

pair<double, double> HopscotchSearch(int arr[], int n, int x) {
    HopscotchHashTable hashTable(n, 32);
    int inserted = true;
    while (true) {
        int i;
        for (i = 0; i < n; i++) {
            int res = hashTable.insert(arr[i]);
            if (res == -1) {
                hashTable.neighborhoodSize++;
                hashTable.table.assign(hashTable.size, HopscotchHashTable::Bucket());
                break;
            }
            else if (res == 0) {
                hashTable.size *= 2;
                hashTable.table.assign(hashTable.size, HopscotchHashTable::Bucket());
                break;
            }
        }
        if (i == n) {
            break;
        }
    }
    
    pair<double, double> res = {0, 0};
    auto start = std::chrono::high_resolution_clock::now();
    res.second = hashTable.search(x);
    auto end = std::chrono::high_resolution_clock::now();
    res.first = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return res;
}