
#include <algorithm>
using namespace std;

int fibonacciSearch(int arr[], int n, int x) {
    int cnt = 0;
    int fib1 = 0;
    int fib2 = 1;
    int fib = fib1 + fib2;
    while(fib < n) {
        fib1 = fib2;
        fib2 = fib;
        fib = fib1 + fib2;
        cnt++;
    }
    int offset = -1;
    while(fib > 1) {
        cnt++;
        int i = min(offset + fib1, n - 1);
        if(arr[i] < x) {
            fib = fib2;
            fib2 = fib1;
            fib1 = fib - fib2;
            offset = i;
        } else if(arr[i] > x) {
            fib = fib1;
            fib2 = fib2 - fib1;
            fib1 = fib - fib2;
        } else {
            return cnt;
        }
    }
    if(fib1 && arr[offset + 1] == x) {
        // return offset + 1;
        return cnt;
    }
    // return -1;
    return cnt;
}