/* Đoạn con có tổng lớn nhất */
#include <bits/stdc++.h>
using namespace std;

/* Hàm tìm tổng lớn nhất của đoạn con bên trái từ chỉ số m đến i */
int doanConTrai(vector<int> a, int i, int m) {
    int sum = 0;
    int max_sum = INT_MIN; // INT_MIN thay vì -INT_MAX để đảm bảo không bị lỗi
    for (int k = m; k >= i; k--) {
        sum += a[k]; // Cộng phần tử vào tổng
        max_sum = max(sum, max_sum); // Cập nhật tổng lớn nhất
    }
    return max_sum;
}

/* Hàm tìm tổng lớn nhất của đoạn con bên phải từ chỉ số m đến j */
int doanConPhai(vector<int> a, int m, int j) {
    int sum = 0;
    int max_sum = INT_MIN; // INT_MIN thay vì -INT_MAX để đảm bảo không bị lỗi
    for (int k = m; k <= j; k++) {
        sum += a[k]; // Cộng phần tử vào tổng
        max_sum = max(sum, max_sum); // Cập nhật tổng lớn nhất
    }
    return max_sum;
}

/* Hàm tìm tổng lớn nhất của đoạn con trong mảng a từ i đến j */
int doanCon(vector<int> a, int i, int j) {
    if (i == j) return a[i]; // Trường hợp cơ sở: mảng chỉ có 1 phần tử
    int m = (i + j) / 2; // Chia đôi đoạn
    int Wl = doanCon(a, i, m); // Tổng lớn nhất bên trái
    int Wr = doanCon(a, m + 1, j); // Tổng lớn nhất bên phải
    int Wm = doanConTrai(a, i, m) + doanConPhai(a, m + 1, j); // Tổng lớn nhất giao giữa trái và phải
    return max(Wm, max(Wl, Wr)); // Kết quả là giá trị lớn nhất trong ba trường hợp
}

int main() {
    int n;
    cin >> n; // Nhập số phần tử của mảng
    vector<int> a(n); // Khởi tạo mảng với n phần tử
    for (int i = 0; i < n; i++) {
        cin >> a[i]; // Nhập từng phần tử vào mảng
    }
    cout << doanCon(a, 0, n - 1) << endl; // Xuất kết quả tổng lớn nhất
}
