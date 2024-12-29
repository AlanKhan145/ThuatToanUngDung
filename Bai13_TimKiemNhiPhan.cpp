/* Tìm kiếm nhị phân với dãy con tăng dần */
#include <bits/stdc++.h>
using namespace std;

// Hàm tìm kiếm nhị phân
int binarySearch(const vector<int>& a, int x, int i, int j) {
    while (i <= j) {
        int m = i + (j - i) / 2;
        if (a[m] == x) {
            return m; // Tìm thấy, trả về chỉ số
        } else if (a[m] > x) {
            j = m - 1; // Tìm trong nửa bên trái
        } else {
            i = m + 1; // Tìm trong nửa bên phải
        }
    }
    return -1; // Không tìm thấy
}

int main() {
    int n;
    cin >> n; // Nhập số phần tử của mảng

    vector<int> a(n); // Khởi tạo mảng với n phần tử: ";
    for (int i = 0; i < n; ++i) {
        cin >> a[i]; // Nhập giá trị cho mảng
    }

    int x; // Giá trị cần tìm kiếm trong mảng
    cin >> x;

    // Gọi hàm tìm kiếm nhị phân
    cout<<binarySearch(a, x, 0, n - 1) + 1 <<endl;

    return 0;
}

