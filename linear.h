
int linearSearch(int arr[], int n, int x) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt++;
        if (arr[i] == x) {
            return cnt;
        }
    }
    return cnt;
}