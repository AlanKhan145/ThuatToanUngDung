#include <bits/stdc++.h>
using namespace std;

int K; // Số xe tải
int N; // Số điểm giao hàng
int Q; // Số thùng hàng tối đa mà mỗi xe tải có thể chở
vector<int> d; // d[i]: Số thùng hàng của điểm giao hàng i
vector<vector<int>> c; // c[i][j]: Ma trận khoảng cách từ điểm i đến điểm j
vector<int> y; // y[k]: Điểm giao hàng đầu tiên của xe k
vector<int> x; // x[s]: Điểm giao hàng thứ s trong lộ trình
vector<bool> visited; // visited[v]: Điểm giao hàng v đã được giao hay chưa
vector<int> load; // Tải trọng hiện tại của xe
double f = 0; // Tổng quãng đường của lộ trình hiện tại
double f_min = INT_MAX; // Tổng quãng đường nhỏ nhất (tốt nhất) tìm được
int segments = 0; // Số đoạn đường đã đi
int nbR = 0; // Tổng số điểm giao hàng
int Cmin = INT_MAX; // Chi phí nhỏ nhất giữa hai điểm bất kỳ

// Hàm cập nhật lộ trình tốt nhất
void updateBest() {
    if (f < f_min) {
        f_min = f;
    }
}

// Hàm kiểm tra tính khả thi khi chọn điểm v cho xe k
bool checkX(int v, int k) {
    if (v > 0 && visited[v]) return false; // Điểm v đã được chọn
    if (load[k] + d[v] > Q) return false; // Vượt quá tải trọng
    return true; // Hợp lệ
}
rt
// Hàm thử giá trị cho x[s], xác định lộ trình xe k
void TRY_X(int s, int k) {
    if (s == 0) { // Nếu quay về điểm xuất phát
        if (k < K) {
            TRY_X(y[k + 1], k + 1); // Tiếp tục thử cho xe tiếp theo
        }
        return;
    }
    for (int v = 0; v <= N; v++) {
        if (checkX(v, k)) { // Kiểm tra tính khả thi của điểm v
            x[s] = v;
            visited[v] = true;
            f += c[s][v]; // Cập nhật quãng đường
            load[k] += d[v]; // Cập nhật tải trọng
            segments++;

            if (v > 0) {
                if (f + (N + nbR - segments) * Cmin < f_min) {
                    TRY_X(v, k); // Tiếp tục thử cho điểm tiếp theo
                }
            } else {
                if (k == K) {
                    if (segments == N + nbR) updateBest(); // Cập nhật lộ trình tốt nhất
                } else {
                    if (f + (N + nbR - segments) * Cmin < f_min) {
                        TRY_X(y[k + 1], k + 1); // Chuyển sang xe tiếp theo
                    }
                }
            }

            // Quay lui
            visited[v] = false;
            f -= c[s][v];
            load[k] -= d[v];
            segments--;
        }
    }
}

// Hàm kiểm tra tính khả thi khi chọn điểm v cho điểm đầu tiên của xe k
bool checkY(int v, int k) {
    if (v == 0) return true; // Điểm quay về kho
    if (load[k] + d[v] > Q) return false; // Vượt quá tải trọng
    if (visited[v]) return false; // Điểm đã được giao
    return true; // Hợp lệ
}

// Hàm thử giá trị cho điểm đầu tiên y[k] của xe k
void TRY_Y(int k) {
    int s = 0;
    if (y[k - 1] > 0) s = y[k - 1] + 1;

    for (int v = s; v <= N; v++) {
        if (checkY(v, k)) { // Kiểm tra tính khả thi của điểm v
            y[k] = v;
            if (v > 0) segments++;
            visited[v] = true;
            f += c[0][v]; // Cập nhật quãng đường
            load[k] += d[v]; // Cập nhật tải trọng

            if (k < K) {
                TRY_Y(k + 1); // Thử cho xe tiếp theo
            } else {
                nbR = segments;
                TRY_X(y[1], 1); // Thử lộ trình cho xe đầu tiên
            }

            // Quay lui
            load[k] -= d[v];
            visited[v] = false;
            f -= c[0][v];
            if (v > 0) segments--;
        }
    }
}

// Hàm giải bài toán
void solve() {
    f = 0;
    f_min = INT_MAX;
    y.assign(K + 1, 0);
    x.assign(N + 1, 0);
    visited.assign(N + 1, false);
    load.assign(K + 1, 0);

    // Tìm chi phí nhỏ nhất
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            if (i != j) Cmin = min(Cmin, c[i][j]);
        }
    }

    TRY_Y(1); // Thử giá trị cho xe đầu tiên
    cout << f_min; // Xuất ra tổng quãng đường tối thiểu
}

int main() {
    cin >> K >> N >> Q;

    d.resize(N + 1);
    c.resize(N + 1, vector<int>(N + 1));

    for (int i = 1; i <= N; i++) {
        cin >> d[i];
    }

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            cin >> c[i][j];
        }
    }

    solve(); // Gọi hàm giải bài toán
    return 0;
}

