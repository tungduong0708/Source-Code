
 
int exponentialSearch(int arr[], int n, int x) {
    int cnt = 0;
    if(arr[0] == x) {
        // return 0;
        return cnt;
    }
    int i = 1;
    while(i < n && arr[i] <= x) {
        cnt++;
        i = i * 2;
    }
    int l = i/2, r = i;
    while (l <= r) {
        cnt++;
        int m = l + (r - l) / 2;
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