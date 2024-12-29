/*Sắp xếp trộn*/
#include <bits/stdc++.h>
using namespace std;

int n;              // số phần tử của mảng
vector<int> a;      // mảng

// Hàm trộn hai phần đã sắp xếp
void merge(int l, int q, int r) {
    vector<int> temp(r - l + 1); // Mảng tạm để lưu kết quả trộn
    int i = l, j = q + 1, k = 0;

    // Trộn hai phần
    while (i <= q && j <= r) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }

    // Sao chép các phần tử còn lại
    while (i <= q) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];

    // Ghi lại kết quả từ mảng tạm vào mảng gốc
    for (int p = 0; p < k; p++) {
        a[l + p] = temp[p];
    }
}
// Hàm sắp xếp trộn
void mergeSort(int l, int r) {
    if (l < r) {
        int q = l + (r - l) / 2;
        mergeSort(l, q);
        mergeSort(q + 1, r);
        merge(l, q, r);
    }
}

int main() {
    cin >> n;
    a.resize(n); // Khởi tạo kích thước của vector

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    mergeSort(0, n - 1); // Chỉ số bắt đầu từ 0

    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}
