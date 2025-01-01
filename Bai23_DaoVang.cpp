//C++
/*Khai thác vàng
Mô tả bài toán
Vương quốc ALPHA có n nhà kho chứa vàng nằm trên một đường thẳng và được đánh số từ 1, 2, ..., n.
Nhà kho thứ i chứa số lượng vàng là a[i] (với a[i] là số nguyên không âm) và nằm tại tọa độ i (với i = 1, ..., n).
Nhà vua ALPHA tổ chức một cuộc thi cho các thợ săn vàng, yêu cầu họ tìm một tập con các nhà kho sao cho
tổng số lượng vàng trong tập con là lớn nhất.
Với điều kiện khoảng cách giữa hai nhà kho được chọn phải lớn hơn hoặc bằng L1 và nhỏ hơn hoặc bằng L2.
Dữ liệu vào (Input)
Dòng đầu tiên chứa ba số nguyên n, L1, L2 (1 ≤ n ≤ 1.000.000, 1 ≤ L1 ≤ L2 ≤ n).
Dòng thứ hai chứa n số nguyên a[1], a[2], ..., a[n] (số lượng vàng ở các nhà kho).
Dữ liệu ra (Output)
Một số nguyên duy nhất biểu diễn tổng số vàng lớn nhất mà các thợ săn có thể chọn từ các nhà kho theo điều kiện.
Ví dụ
Dữ liệu vào
6 2 3
3 5 9 6 7 4
Dữ liệu ra
19*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, l1, l2;
    cin >> n >> l1 >> l2;

    vector<int> a(n + 1, 0);
    vector<int> dp(n + 1, 0);
    vector<int> max_dp(n+1,0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        dp[i] = a[i];
    }
    int temp = dp[1];
    // Xử lý cho các phần tử trong khoảng [l1 + 1, l2]
    for (int i = l1 + 1; i <= l2; i++) {
        dp[i] = temp + a[i];
        if(temp < dp[i-l1+1]){
            temp = dp[i-l1+1];
        }
    }

    // Xử lý cho các phần tử trong khoảng [l2 + 1, n]
    for (int i = l2 + 1; i <= n; i++) {
        dp[i] = temp + a[i];
        if(temp < dp[i-l1+1]){
            temp = dp[i-l1+1];
        }
        else if(temp == dp[i-l2]){
            temp = *max_element(dp.begin() + i - l2 + 1, dp.begin() + i - l1 + 1);
        }
    }

    cout << *max_element(dp.begin() + 1 , dp.begin() + n + 1);
    return 0;
}
