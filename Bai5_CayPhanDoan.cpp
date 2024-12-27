#include <bits/stdc++.h>
using namespace std;

int a[100];
int maxVal[400];
int n;

void buildSegmentTree(int id, int l, int r) {
    if (l == r) {
        maxVal[id] = a[l];
    } else {
        int m = (l + r) / 2;
        buildSegmentTree(2 * id, l, m);
        buildSegmentTree(2 * id + 1, m + 1, r);
        maxVal[id] = max(maxVal[2 * id], maxVal[2 * id + 1]);
    }
}

int GetMaxFromNode(int id, int l, int r, int i, int j) {
    if (j < l || i > r) {
        return INT_MIN;
    }
    if (i <= l && r <= j) {
        return maxVal[id];
    }
    int m = (l + r) / 2;
    int maxLeft = GetMaxFromNode(2 * id, l, m, i, j);
    int maxRight = GetMaxFromNode(2 * id + 1, m + 1, r, i, j);
    return max(maxLeft, maxRight);
}

int GetMax(int i, int j) {
    return GetMaxFromNode(1, 1, n, i, j);
}

void UpdateFromNode(int id, int l, int r, int index, int value) {
    if (l == r) {
        maxVal[id] = value;
        return;
    }
    int m = (l + r) / 2;
    if (index <= m) {
        UpdateFromNode(2 * id, l, m, index, value);
    } else {
        UpdateFromNode(2 * id + 1, m + 1, r, index, value);
    }
    maxVal[id] = max(maxVal[2 * id], maxVal[2 * id + 1]);
}

void Update(int i, int v) {
    UpdateFromNode(1, 1, n, i, v);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    buildSegmentTree(1, 1, n);

    int i, j;
    cin >> i >> j;
    cout << GetMax(i, j) << endl;

    int index, value;
    cin >> index >> value;
    if (index >= 1 && index <= n) {
        Update(index, value);
        cout <<  GetMax(i, j) << endl;
    } else {
        cout <<  endl;
    }

    return 0;
}

