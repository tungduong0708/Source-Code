int twoPointerSearch(int arr[], int n, int x) {
    int cnt = 0;
    int left = 0, right = n - 1;
    while (left <= right) {
        cnt++;
        if (arr[left] == x) {
            // return left;
            return cnt;
        }
        if (arr[right] == x) {
            // return right;
            return cnt;
        }
        left++;
        right--;
    }
    // return -1;
    return cnt;
}