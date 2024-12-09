
#include <memory>
#include <chrono>
#include <utility>

using namespace std;

class BinaryPrefixTree {
private:
    struct TrieNode {
        bool isEnd;
        shared_ptr<TrieNode> children[2];
        TrieNode() : isEnd(false) {}
    };
    shared_ptr<TrieNode> root;
 
public:
    BinaryPrefixTree() {
        root = make_shared<TrieNode>();
    }
 
    void insert(int word) {
        shared_ptr<TrieNode> cur = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (word >> i) & 1;
            if (cur->children[bit] == nullptr) {
                cur->children[bit] = make_shared<TrieNode>();
            }
            cur = cur->children[bit];
        }
        cur->isEnd = true;
    }
 
    int search(int word) {
        shared_ptr<TrieNode> cur = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (word >> i) & 1;
            if (cur->children[bit] == nullptr) {
                return 31 - i + 1;
            }
            cur = cur->children[bit];
        }
        return 32;
    }
 
    bool deleteWord(int word) {
        return deleteWordHelper(word, 0, root);
    }
 
    bool deleteWordHelper(int word, int i, shared_ptr<TrieNode> cur) {
        if (cur == nullptr) {
            return false;
        }
        if (i == 32) {
            if (!cur->isEnd) {
                return false;
            }
            cur->isEnd = false;
            return cur->children[0] == nullptr && cur->children[1] == nullptr;
        }
        int bit = (word >> (31 - i)) & 1;
        if (deleteWordHelper(word, i + 1, cur->children[bit])) {
            cur->children[bit] = nullptr;
            return cur->children[0] == nullptr && cur->children[1] == nullptr;
        }
        return false;
    }
};
 
pair<double,double> BinaryPrefixTreeSearch(int *arr, int n, int x) {
    BinaryPrefixTree tree;
    for (int i = 0; i < n; i++) {
        tree.insert(arr[i]);
    }
 
    pair<double, double> res = make_pair(0, 0);
    auto start = std::chrono::high_resolution_clock::now();
    res.second = tree.search(x);
    auto end = std::chrono::high_resolution_clock::now();
    res.first = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return res;
}