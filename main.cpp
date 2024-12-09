#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>
#include <map>
#include <functional>
#include <list>
#include <memory>
#include <random>
#include "linear.h"
#include "binary.h"
#include "two_pointer.h"
#include "jump.h"
#include "interpolation.h"
#include "ternary.h"
#include "exponential.h"
#include "fibonacci.h"
#include "hopscotch_hash.h"
#include "cuckoo_hash.h"
#include "avl_tree.h"
#include "b_tree.h"
using namespace std;


void speedTest(string input, string output, vector<int> sizes) {
    std::map<std::string, std::function<int(int[], int, int)>> functions1;
    functions1["Linear Search"] = linearSearch;
    functions1["Two Pointer Search"] = twoPointerSearch;
    functions1["Binary Search"] = binarySearch;
    functions1["Ternary Search"] = TernarySearch;
    functions1["Fibonacci Search"] = fibonacciSearch;
    // functions1["Interpolation Search"] = interpolationSearch;
    functions1["Jump Search"] = jumpSearch;
    functions1["Exponential Search"] = exponentialSearch;

    std::map<std::string, std::function<pair<double, double>(int[], int, int)>> functions2;
    functions2["Hopscotch Hashing Search"] = HopscotchSearch;
    functions2["Cuckoo Hashing Search"] = CuckooSearch;
    functions2["AVL Tree Search"] = AVLTreeSearch;
    functions2["B Tree Search"] = BTreeSearch;

    std::ifstream fin(input);
    std::ofstream fout(output, std::ios::app);

    if (!fin.is_open() || !fout.is_open()) {
        std::cerr << "Error opening " << input << std::endl;
        return;
    }

    fout << "===============================================================================" << std::endl;
    fout << "Benchmark Results" << std::endl;
    fout << "===============================================================================" << std::endl;
    fout << "Test Case  |  Search Function       |  Execution Time (ns)  |  Avg Iterations" << std::endl;
    fout << "===============================================================================" << std::endl;

    for (auto size : sizes) {
        int n, numTests;
        fin >> n >> numTests;
        map<string, double> iters;
        map<string, double> times;
        for (int i = 0; i < numTests; i++) {
            int x;
            fin >> x;
            
            std::vector<int> arr(n);
            for (int i = 0; i < n; ++i) {
                fin >> arr[i]; 
            }
            do {
                if (x % 1000 == 0) cout << x << endl;
                for (const auto& func : functions1) {
                    // cout << "Running " << func.first << " on " << size << " elements..." << endl;
                    auto start = std::chrono::high_resolution_clock::now();
                    iters[func.first] += func.second(arr.data(), n, x);
                    auto end = std::chrono::high_resolution_clock::now();
                    times[func.first] += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                }
                for (const auto& func : functions2) {
                    // cout << "Running " << func.first << " on " << size << " elements..." << endl;
                    pair<double, double> res = func.second(arr.data(), n, x);
                    iters[func.first] += res.second;
                    times[func.first] += res.first;
                }
            } while (x++ < size);
        }
        numTests = size;
        for (auto& func : functions1) {
            fout <<  size << " elements |  " << func.first << "  |  " << times[func.first] / numTests << " ns" << "  |  " << iters[func.first] / numTests << "\n";
        }
        for (auto& func : functions2) {
            fout <<  size << " elements |  " << func.first << "  |  " << times[func.first] / numTests << " ns" << "  |  " << iters[func.first] / numTests << "\n";
        }
        fout << "---------------------------------------------------------------" << std::endl;
    }

    fout << std::endl;

    fin.close();
    fout.close();
}

void clearFile(const std::string& filename) {
    std::ofstream fout(filename, std::ios::out | std::ios::trunc);
    if (!fout.is_open()) {
        std::cerr << "Error opening the file to clear: " << filename << std::endl;
        return;
    }
    fout.close();
    std::cout << "File " << filename << " has been cleared." << std::endl;
}

void genTest(vector<int> sizes) {
    ofstream fout1("dataset/sorted_dataset.txt");
    ofstream fout2("dataset/unsorted_dataset.txt");
    if (!fout1.is_open()) {
        cerr << "Error opening the file sorted to write!" << endl;
        return;
    }
    if (!fout2.is_open()) {
        cerr << "Error opening the file unsorted to write!" << endl;
        return;
    }

    random_device rd;
    mt19937 gen(rd());

    for (int size : sizes) {
        vector<int> targets {1};
        fout1 << size << " " << targets.size() << "\n";
        fout2 << size << " " << targets.size() << "\n";
        for (int target : targets) {
            fout1 << target << "\n";
            fout2 << target << "\n";

            vector<int> arr(size);
            iota(arr.begin(), arr.end(), 1); 
            for (int i = 0; i < size; ++i) {
                fout1 << arr[i] << " ";
            }

            shuffle(arr.begin(), arr.end(), gen);
            for (int i = 0; i < size; ++i) {
                fout2 << arr[i] << " ";
            }
        }
        fout1 << "\n";
        fout2 << "\n";
    }

    fout1.close();
    fout2.close();
    cout << "Multiple test cases generated successfully in 'input.txt'.\n";
}

int main() {
    // clearFile("benchmark/sorted_benchmark.txt");
    clearFile("benchmark/unsorted_benchmark.txt");
    vector<int> sizes = {10, 100, 1000, 10000};
    // genTest(sizes);
  
    // speedTest("dataset/sorted_dataset.txt", "benchmark/sorted_benchmark.txt", sizes);
    std::cout << "Benchmarking complete. Results written to sorted_benchmark.txt." << std::endl;
    speedTest("dataset/unsorted_dataset.txt", "benchmark/unsorted_benchmark.txt", sizes);
    std::cout << "Benchmarking complete. Results written to unsorted_benchmark.txt." << std::endl;
    return 0;
}