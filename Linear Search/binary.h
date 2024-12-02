#include <iostream>
using namespace std;

int binarySearch(int arr[], int n, int x) {
    int cnt = 0;
    int l = 0, r = n - 1;
    while (l <= r) {
        cnt++;
        int m = (l + r) >> 1;
        if (arr[m] == x) {
            return cnt;
        }
        if (arr[m] < x) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    // return -1;
    return cnt;
}