int jumpSearch(int arr[], int n, int x) {
    int cnt = 0;
    int step = sqrt(n);
    int prev = 0;
    while (arr[std::min(step, n) - 1] < x) {
        cnt++;
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            // return -1;
            return cnt;
        }
    }
    for (int i = prev; i < std::min(step, n); i++) {
        cnt++;
        if (arr[i] == x) {
            return cnt;
            // return i;
        }
    }
    // return -1;
    return cnt;
}

int twoLevelJumpSearch(int arr[], int n, int x) {
    int n1 = std::pow((n * n), 2.0 / 3.0);
    int n2 = std::pow((n * n), 1.0 / 3.0);
    int step1 = n1;
    int step2 = n2;
    int prev1 = 0, prev2 = 0;

    while (arr[std::min(step1, n) - 1] < x) {
        prev1 = step1;
        step1 += n1;
        if (prev1 >= n) {
            return -1;
        }
    }

    while (arr[std::min(prev1 + step2, n) - 1] < x) {
        prev2 = prev1 + step2;
        step2 += n2;
        if (prev2 >= n) {
            return -1;
        }
    }

    for (int i = prev2; i < std::min(prev2 + step2, n); i++) {
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;

}

int variableJumpSearch(int arr[], int n, int x) {
    int step = 1;
    int prev = 0;

    while (arr[std::min(step, n) - 1] < x) {
        prev = step;
        step *= 2;
        if (prev >= n) {
            return -1;
        }
    }

    for (int i = prev; i < std::min(step, n); i++) {
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;
}

int twoLevelVariableJumpSearch(int arr[], int n, int x) {
    int step = 1; 
    int prev = 0;

    while (step < n && arr[std::min(step, n) - 1] < x) {
        prev = step;
        step += std::sqrt(2 * (n - prev)); 
        if (prev >= n) {
            return -1; 
        }
    }

    for (int i = prev; i < std::min(step, n); i++) {
        if (arr[i] == x) {
            return i; 
        }
    }

    return -1; 
}