/*LAB.02.04 - Bài toán Lộ trình Giao hàng với Xe tải Có hạn
Mô tả:
Một đội xe tải gồm K chiếc xe tải giống hệt nhau, mỗi xe có sức chứa Q.
Cần lập lịch giao các gói pepsi từ kho trung tâm (điểm 0) đến các khách hàng (1, 2, ..., n).
Mỗi khách hàng i yêu cầu d[i] gói.
Khoảng cách giữa các điểm i và j là c[i,j], với 0 ≤ i,j ≤ n.
Giải pháp giao hàng:
Một giải pháp giao hàng là một tập hợp các lộ trình:
Mỗi xe tải có một lộ trình riêng.
Lộ trình bắt đầu từ kho trung tâm, thăm một số khách hàng và quay lại kho.
Mỗi khách hàng được thăm đúng một lần trong lộ trình.
Tổng số gói yêu cầu của khách hàng mà mỗi xe tải phục vụ không vượt quá sức chứa của xe tải (Q).
Mục tiêu:
Tìm giải pháp có tổng quãng đường di chuyển tối thiểu.
Lưu ý:
Có thể có trường hợp một xe tải không thăm khách hàng nào (lộ trình rỗng).
Thứ tự các khách hàng trong lộ trình là quan trọng:
Ví dụ: lộ trình 0 → 1 → 2 → 3 → 0 và 0 → 3 → 2 → 1 → 0 là khác nhau.
Dữ liệu đầu vào:
Dòng 1: n, K, Q (2 ≤ n ≤ 12, 1 ≤ K ≤ 5, 1 ≤ Q ≤ 50).
Dòng 2: d[1], ..., d[n] (1 ≤ d[i] ≤ 10).
Dòng i+3 (i = 0,…,n): hàng thứ i của ma trận khoảng cách c (1 ≤ c[i,j] ≤ 30).
Dữ liệu đầu ra:
Tổng quãng đường di chuyển tối thiểu.
Ví dụ:
Dữ liệu đầu vào:
4 2 15
7 7 11 2
0 12 12 11 14
14 0 11 14 14
14 10 0 11 12
10 14 12 0 13
10 13 14 11 0
Dữ liệu đầu ra:
70*/
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int MAX_N = 12;
const int MAX_K = 5;
const int INF = INT_MAX;

int n, K, Q;
vector<int> d(MAX_N + 1), y(MAX_K + 1), x(MAX_N + 1);
vector<vector<int>> c(MAX_N + 1, vector<int>(MAX_N + 1));
vector<bool> visited(MAX_N + 1, false);
vector<int> load(MAX_K + 1, 0);
int f = 0, f_min = INF, nbR = 0, segments = 0;
int Cmin = INF; // Khoảng cách nhỏ nhất trong ma trận c
vector<int> x_best, y_best;

// Kiểm tra tính hợp lệ khi thử giá trị cho x[s]
bool checkX(int v, int k) {
    if (v > 0 && visited[v]) return false;
    if (load[k] + d[v] > Q) return false;
    return true;
}

// Kiểm tra tính hợp lệ khi thử giá trị cho y[k]
bool checkY(int v, int k) {
    if (v == 0) return true;
    if (load[k] + d[v] > Q) return false;
    if (visited[v]) return false;
    return true;
}

// Cập nhật kết quả tối ưu
void updateBest() {
    if (f < f_min) {
        f_min = f;
        x_best = x;
        y_best = y;
    }
}

// Thử giá trị cho x[s]
void TRY_X(int s, int k) {
    if (s == 0) {
        if (k < K) {
            TRY_X(y[k + 1], k + 1);
        }
        return;
    }

    for (int v = 0; v <= n; v++) {
        if (checkX(v, k)) {
            x[s] = v;
            visited[v] = true;
            f += c[s][v];
            load[k] += d[v];
            segments++;

            if (v > 0) {
                if (f + (n + nbR - segments) * Cmin < f_min) {
                    TRY_X(v, k);
                }
            } else {
                if (k == K) {
                    if (segments == n + nbR) {
                        updateBest();
                    }
                } else {
                    if (f + (n + nbR - segments) * Cmin < f_min) {
                        TRY_X(y[k + 1], k + 1);
                    }
                }
            }

            visited[v] = false;
            f -= c[s][v];
            load[k] -= d[v];
            segments--;
        }
    }
}

// Thử giá trị cho y[k]
void TRY_Y(int k) {
    int s = 0;
    if (y[k - 1] > 0) s = y[k - 1] + 1;

    for (int v = s; v <= n; v++) {
        if (checkY(v, k)) {
            y[k] = v;
            if (v > 0) {
                segments++;
            }
            visited[v] = true;
            f += c[0][v];
            load[k] += d[v];

            if (k < K) {
                TRY_Y(k + 1);
            } else {
                nbR = segments;
                TRY_X(y[1], 1);
            }

            load[k] -= d[v];
            visited[v] = false;
            f -= c[0][v];
            if (v > 0) {
                segments--;
            }
        }
    }
}

// Giải quyết bài toán
void solve() {
    f = 0;
    f_min = INF;
    y[0] = 0;
    Cmin = INF;

    for (int v = 1; v <= n; v++) {
        visited[v] = false;
        for (int i = 0; i <= n; i++) {
            if (c[v][i] < Cmin) {
                Cmin = c[v][i];
            }
        }
    }

    TRY_Y(1);
    if (f_min != INF) {
        cout << f_min << endl;
    } else {
        cout << "-1" << endl;
    }
}

int main() {
    // Đọc dữ liệu đầu vào
    cin >> n >> K >> Q;
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cin >> c[i][j];
        }
    }

    solve();
    return 0;
}


