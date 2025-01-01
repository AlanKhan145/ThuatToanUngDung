/*Có M kệ hàng trong một kho lớn, được đánh số từ 1 đến M, trong đó kệ j nằm ở vị trí j trong kho (j = 1, ..., M).
Có N loại sản phẩm, được đánh số từ 1 đến N. Số lượng sản phẩm i trên kệ j là Q[i][j].
Nhân viên kho bắt đầu từ cửa kho (điểm 0) và muốn ghé thăm một số kệ (mỗi kệ chỉ được ghé thăm tối đa một lần)
rồi quay lại cửa kho để lấy các sản phẩm theo đơn hàng của khách,
trong đó tổng số lượng sản phẩm i mà nhân viên cần lấy là q[i] (i = 1, 2, ..., N).
Khoảng cách di chuyển từ điểm i đến điểm j là d(i, j) (0 ≤ i, j ≤ M).
Hãy tìm thứ tự các kệ cần ghé thăm sao cho tổng quãng đường di chuyển là nhỏ nhất.
Dữ liệu đầu vào:
Dòng 1: Hai số nguyên dương N và M (1 ≤ N ≤ 50, 1 ≤ M ≤ 1000).
Dòng 2 đến dòng N + 1: Mỗi dòng chứa hàng thứ i của ma trận Q.
Dòng N + 2 đến dòng N + M + 2: Mỗi dòng chứa hàng thứ i của ma trận khoảng cách d.
Dòng N + M + 3: Chứa q[1], q[2], ..., q[N].
Dữ liệu đầu ra:
Dòng 1: Một số nguyên dương n, là số lượng kệ cần ghé thăm.
Dòng 2: n số nguyên dương x1, x2, ..., xn, là thứ tự các kệ cần ghé thăm.
Ví dụ:
Đầu vào:
6 5
3 2 2 4 2
4 3 7 3 5
6 7 2 5 4
2 3 3 2 1
2 5 7 6 1
7 2 1 6 5
0 16 10 13 13 19
16 0 8 3 19 5
10 8 0 7 23 11
13 3 7 0 16 6
13 19 23 16 0 22
19 5 11 6 22 0
8 7 4 8 11 13
Đầu ra:
4
2 3 1 5
Giải thích:
Lộ trình của nhân viên kho là: 0 → 2 → 3 → 1 → 5 → 0.*/
#include <bits/stdc++.h>
using namespace std;

int n; // Số loại sản phẩm
int m; // Số kệ hàng
vector<vector<int>> Q; // Ma trận số lượng sản phẩm
vector<vector<int>> d; // Ma trận khoảng cách
vector<int> q; // Số lượng sản phẩm cần lấy
vector<int> x; // Thứ tự các kệ cần ghé thăm
vector<bool> visited; // Đánh dấu kệ đã ghé thăm
vector<int> sosp; // Số sản phẩm đã lấy
vector<int> x_best; // Thứ tự kệ tốt nhất
int f = 0; // Quãng đường hiện tại
int min_f = INT_MAX; // Quãng đường nhỏ nhất
int max_loop = 1;
int loop = 0;
// Kiểm tra đã lấy đủ tất cả các sản phẩm chưa
bool check_end() {
    for (int sp = 1; sp <= n; sp++) {
        if (sosp[sp] < q[sp]) return false;
    }
    return true;
}

// Kiểm tra xem có thể ghé thăm kệ i tại bước k không
bool check(int k, int i) {
    if(visited[i]) return false;
    if(f >= min_f) return false;
    return true;
}

// Cập nhật thứ tự kệ tốt nhất nếu tìm được lộ trình tối ưu
void update_best() {
    if (f < min_f) {
        x_best = x;
        min_f = f;
        loop ++;
    }
}

// Hàm thử các phương án
void thu(int k) {
    if(loop == max_loop) return;
    for (int i = 1; i <= m; i++) {
        if (check(k, i)) {
            x[k] = i;
            visited[i] = true;

            // Cập nhật số sản phẩm đã lấy
            for (int sp = 1; sp <= n; sp++) {
                sosp[sp] += Q[sp][i];
            }

            // Cập nhật quãng đường
            f += d[x[k - 1]][x[k]];

            if (check_end()) {
                f += d[x[k]][0]; // Quay lại cửa kho
                update_best();
                f -= d[x[k]][0];
            } else if (k < m && f < min_f) {
                thu(k + 1);
            }

            // Hoàn tác (backtrack)
            visited[i] = false;
            for (int sp = 1; sp <= n; sp++) {
                sosp[sp] -= Q[sp][i];
            }
            f -= d[x[k - 1]][x[k]];
        }
    }
}

int main() {
    // Nhập dữ liệu
    cin >> n >> m;
    Q.resize(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> Q[i][j];
        }
    }

    d.resize(m + 1, vector<int>(m + 1));
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= m; j++) {
            cin >> d[i][j];
        }
    }

    q.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> q[i];
    }

    // Khởi tạo
    x.resize(m + 1, 0);
    visited.resize(m + 1, false);
    sosp.resize(n + 1, 0);

    // Bắt đầu thử từ kệ đầu tiên
    thu(1);

    // Xuất kết quả
    int k = 0 ;
    for (int i = 1; i < x_best.size(); i++) {
        if (x_best[i] == 0) break;
        k++;
    }
    cout << min_f << endl;
    cout << k << endl;
    for (int i = 1; i < x_best.size(); i++) {
        if (x_best[i] == 0) break;

        cout << x_best[i] << " ";
    }
    cout << endl;

    return 0;
}
