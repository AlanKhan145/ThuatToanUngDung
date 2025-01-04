/*Tập hợp con có khoảng cách tối đa (Max-Distance Sub-Sequence)
Mô tả bài toán
Cho N phần tử (2 ≤ N ≤ 100,000) nằm trên một đường thẳng tại các vị trí x1, x2, ..., xN (0 ≤ xi ≤ 1,000,000,000).
Khoảng cách của một tập hợp con các phần tử được định nghĩa là khoảng cách nhỏ nhất giữa hai phần tử bất kỳ trong tập hợp con đó.
Nhiệm vụ là tìm tập hợp con gồm đúng C phần tử từ N phần tử đã cho, sao cho khoảng cách nhỏ nhất giữa hai phần tử trong tập hợp con là lớn nhất.
Đầu vào
Dòng đầu tiên chứa số nguyên dương T (1 ≤ T ≤ 20), là số lượng bộ test.
Sau đó là T bộ test, mỗi bộ test gồm:
Dòng 1: Hai số nguyên N và C, cách nhau bởi một khoảng trắng.
Dòng 2: N số nguyên x1, x2, ..., xN (vị trí các phần tử).
Đầu ra
Với mỗi bộ test, in ra một số nguyên: khoảng cách lớn nhất của tập hợp con tìm được.
Ví dụ
Đầu vào
1
5 3
1 2 8 4 9
Đầu ra
3
Giải thích:
Chọn 3 phần tử tại các vị trí 1, 4 và 8. Trong trường hợp này:
Khoảng cách nhỏ nhất giữa hai phần tử bất kỳ trong tập hợp con là 3.
Đây là giá trị lớn nhất có thể đạt được.*/
#include<bits/stdc++.h>
using namespace std;

int n, c;
vector<int> a;

bool check(int d) {
    int count = 1;
    int last_position = a[1];

    for (int i = 2; i <= n; i++) {
        if (a[i] - last_position >= d) {
            count++;
            last_position = a[i];
        }
        if (count == c) return true;
    }
    return false;
}

int main() {
    int T;
    cin >> T;
    vector<int> res(T + 1, 0);

    for (int t = 1; t <= T; t++) {
        cin >> n >> c;
        a.resize(n + 1);

        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }

        sort(a.begin() + 1, a.begin() + n + 1);

        int l = 1;
        int r = a[n] - a[1];
        int ans = 0;

        while (l <= r) {
            int d = (l + r) / 2;
            if (check(d)) {
                ans = d;
                l = d + 1;
            } else {
                r = d - 1;
            }
        }

        res[t] = ans;
    }

    for (int i = 1; i <= T; i++) {
        cout << res[i] << endl;
    }

    return 0;
}
