#include <bits/stdc++.h>
using namespace std;

int n;
int M;
vector<vector<int>> state;
vector<bool> used;

bool is_valid(int row, int col) {
    int sum;
    bool full;

    // Check row
    sum = 0;
    full = true;
    
    for (int j = 0; j < n; j++) {
        if (state[row][j] == 0) full = false;
        sum += state[row][j];
    }
    if (full && sum != M) return false;
    if (!full && sum > M) return false;

    // Check column
    sum = 0;
    full = true;
    for (int i = 0; i < n; i++) {
        if (state[i][col] == 0) full = false;
        sum += state[i][col];
    }
    if (full && sum != M) return false;
    if (!full && sum > M) return false;

    // Check main diagonal
    if (row == col) {
        sum = 0;
        full = true;
        for (int i = 0; i < n; i++) {
            if (state[i][i] == 0) full = false;
            sum += state[i][i];
        }
        if (full && sum != M) return false;
        if (!full && sum > M) return false;
    }

    // Check anti-diagonal
    if (row + col == n - 1) {
        sum = 0;
        full = true;
        for (int i = 0; i < n; i++) {
            if (state[i][n - 1 - i] == 0) full = false;
            sum += state[i][n - 1 - i];
        }
        if (full && sum != M) return false;
        if (!full && sum > M) return false;
    }

    return true;
}

bool expand(int index) {
    if (index == n * n) {
        return true;
    }

    int row = index / n;
    int col = index % n;

    for (int num = 1; num <= n * n; num++) {
        
        if (used[num]) {
            continue;
        }

        state[row][col] = num;
        used[num] = true;

        if (is_valid(row, col)) {
            if (expand(index + 1)) {
                return true;
            }
        }

        state[row][col] = 0;
        used[num] = false;
    }

    return false;
}


int main() {
    cout << "Enter order n of magic square: ";
    cin >> n;

    M = n * (n * n + 1) / 2;
    state.resize(n, vector<int>(n, 0));
    used.resize(n * n + 1, false);

    if (expand(0)) {
        cout << "Magic Square of order " << n << ":\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << state[i][j] << "  ";
            }
            cout << "\n";
        }
    } else {
        cout << "No solution found!\n";
    }
    return 0;
}
