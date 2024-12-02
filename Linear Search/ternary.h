
int TernarySearch(int arr[], int n, int x) {
    int cnt = 0;
    int low = 0, high = n - 1;

    while (high >= low) {
        cnt++;
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        // Check if x is at mid1 or mid2
        if (arr[mid1] == x) return cnt;
        if (arr[mid2] == x) return cnt;

        // Narrow the search space
        if (x < arr[mid1]) {
            high = mid1 - 1; // Search in the left third
        } else if (x > arr[mid2]) {
            low = mid2 + 1; // Search in the right third
        } else {
            low = mid1 + 1; // Search in the middle third
            high = mid2 - 1;
        }
    }

    return cnt;
}