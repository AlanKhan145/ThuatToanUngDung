/*Bài toán người đi du lịch
• Cho một đồ thị n đỉnh {0, 1, ..., n – 1} và giá trị trọng số Ci,j trên mỗi cặp đỉnh i, j.
Hãy tìm một chu trình đi qua tất cả các đỉnh của đồ thị, mỗi đỉnh đúng một lần sao cho tổng các
trọng số trên chu trình đó là nhỏ nnhất*/
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// Hàm TSP sử dụng quy hoạch động với bitmask
int TSP(int i, int S, int n, vector<vector<int>> &C, vector<vector<int>> &mem) {
    if (S == (1 << n) - 1) // Nếu đã đi qua tất cả các đỉnh
        return C[i][0]; // Quay về đỉnh xuất phát

    if (mem[i][S] != -1) // Nếu đã tính toán, trả về giá trị lưu trong mem
        return mem[i][S];

    int res = INF;
    for (int j = 0; j < n; j++) { // Thử tất cả các đỉnh
        if (S & (1 << j)) continue; // Nếu đỉnh j đã được thăm, bỏ qua
        res = min(res, C[i][j] + TSP(j, S | (1 << j), n, C, mem));
    }

    return mem[i][S] = res; // Lưu giá trị tối ưu
}

int main() {
    int n;
    cin >> n; // Số đỉnh của đồ thị
    vector<vector<int>> C(n, vector<int>(n)); // Trọng số giữa các đỉnh

    // Nhập trọng số đồ thị
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> C[i][j];
        }
    }

    vector<vector<int>> mem(n, vector<int>(1 << n, -1)); // Bảng nhớ

    // Bắt đầu từ đỉnh 0, trạng thái ban đầu chỉ có đỉnh 0 được thăm
    cout << TSP(0, 1, n, C, mem) << endl;

    return 0;
}
