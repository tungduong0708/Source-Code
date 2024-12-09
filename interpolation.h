
int interpolationSearch(int arr[], int n, int x) {
    int cnt = 0;
    if (x < arr[0] || x > arr[n-1]) {
        // return -1;
        return cnt;
    }
    int lo = 0, hi = n - 1;
    while (hi - lo >= 0) {
        cnt++;
        if (lo == hi) {
            if (arr[lo] == x) {
                // return lo;
                return cnt;
            }
            // return -1;
            return cnt;
        }
        int pos = lo + ((x - arr[lo])*(hi - lo))/(arr[hi] - arr[lo]);
        if (arr[pos] == x) {
            // return pos;
            return cnt;
        }
        if (arr[pos] < x) {
            lo = pos + 1;
        } else {
            hi = pos - 1;
        }
    }
    // return -1;
    return cnt;
}