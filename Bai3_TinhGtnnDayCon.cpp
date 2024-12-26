#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int m = log2(n);
    vector<vector<int>> M(n, vector<int>(m + 1));
    for (int i = 0; i < n; i++) {
        M[i][0] = i;
    }

    for (int k = 1; k <= m; k++) {
        for (int i = 0; i + (1 << k) <= n; i++) {
            int l = M[i][k - 1];
            int r = M[i + (1 << (k - 1))][k - 1];
            if (a[l] < a[r])
                M[i][k] = l;
            else
                M[i][k] = r;
        }
    }

    int i, j;
    cin >> i >> j;
    int k = log2(j - i + 1);
    int l = M[i][k];
    int r = M[j - (1 << k) + 1][k];
    int result = (a[l] < a[r]) ? l : r;

    cout << result;
    return 0;
}

