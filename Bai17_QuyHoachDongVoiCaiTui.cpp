/*Quy hoạch động với bài toán cái túi*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;

    vector<int> d(n+1, 0);  // Mảng chứa các giá trị của các đồng xu
    for(int i = 1; i <= n; i++) {
        cin >> d[i];  // Nhập các giá trị đồng xu
    }

    int k;
    cin >> k;  // Tổng giá trị cần đạt được

    vector<int> p(k+1, INT_MAX);  // Mảng lưu số lượng đồng xu tối thiểu cần thiết cho mỗi giá trị
    p[0] = 0;  // 0 đồng xu để tạo ra giá trị 0

    for(int i = 1; i <= k; i++) {
        for(int coin = 1; coin <= n; coin++) {
            if(i >= d[coin] && p[i - d[coin]] != INT_MAX) {  // Chỉ cập nhật nếu có cách hợp lệ
                p[i] = min(p[i], p[i - d[coin]] + 1);  // Cập nhật số đồng xu tối thiểu
            }
        }
    }

    if(p[k] == INT_MAX) {
        cout << -1 << endl;  // Nếu không thể đạt được giá trị k
    } else {
        cout << p[k] << endl;  // Số đồng xu tối thiểu
    }

    return 0;
}
