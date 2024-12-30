/*Đoạn con có tổng dài nhất*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n + 1), s(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    // Khởi tạo giá trị ban đầu cho s[1]
    s[1] = a[1];
    int max_sum = a[1];
    for (int i = 2; i <= n; i++) {
        s[i] = max(s[i - 1] + a[i], a[i]);
        max_sum = max(max_sum, s[i]);
    }

    cout << max_sum << endl;
    return 0;
}
