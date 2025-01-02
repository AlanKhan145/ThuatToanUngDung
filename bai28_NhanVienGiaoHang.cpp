/*Có N khách hàng 1, 2, ..., N cần được bảo trì mạng internet. Các yêu cầu được mô tả như sau:
Khách hàng i ở địa điểm i (với i = 1, ..., N).
Việc bảo trì cho khách hàng i kéo dài d(i) đơn vị thời gian.
Có K nhân viên kỹ thuật xuất phát từ trụ sở công ty (điểm 0) và thời điểm bắt đầu làm việc là t0 = 0.
Thời gian di chuyển giữa địa điểm i và j là t(i, j).
Yêu cầu:
Lập kế hoạch phân công nhân viên thực hiện bảo trì sao cho thời gian làm việc nhiều nhất (gồm thời gian di chuyển và bảo trì) của một nhân viên là nhỏ nhất.
Định dạng đầu vào
Dòng 1: chứa hai số nguyên N và K (1 ≤ N ≤ 1000, 1 ≤ K ≤ 100).
Dòng 2: chứa d(1), d(2), ..., d(N) (1 ≤ d(i) ≤ 1000) - thời gian bảo trì của từng khách hàng.
Từ dòng thứ 3 trở đi: ma trận t với (N+1) hàng, mỗi hàng có (N+1) cột, đại diện thời gian di chuyển giữa các địa điểm.
Định dạng đầu ra
Dòng 1: chứa số K.
Với mỗi nhân viên k (k = 1, ..., K):
Dòng 2k: chứa một số nguyên dương Lk - số điểm nhân viên k đi qua, bao gồm cả điểm xuất phát và quay lại trụ sở.
Dòng 2k+1: chứa danh sách r[0], r[1], ..., r[Lk], trong đó r[0] = r[Lk] = 0 (trụ sở).
Ví dụ
Input
5 2
60 80 70 10 90
0 50 100 60 40 80
50 0 50 40 20 60
100 50 0 50 70 40
60 40 50 0 60 20
40 20 70 60 0 80
80 60 40 20 80 0
Output
2
5
0 5 3 4 0
4
0 2 1 0
Giải thích
Có 5 khách hàng và 2 nhân viên kỹ thuật.
Nhân viên 1 được phân công đi qua các địa điểm: 0 → 5 → 3 → 4 → 0.
Nhân viên 2 được phân công đi qua các địa điểm: 0 → 2 → 1 → 0.
Mỗi nhân viên bắt đầu và kết thúc tại trụ sở (điểm 0).*/
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int n, K; // n: số lượng khách hàng, K: số lượng nhân viên
vector<int> d; // Thời gian bảo trì của từng khách hàng
vector<int> y, x; // y: lộ trình của các nhân viên, x: lưu trữ vị trí khách hàng của các nhân viên
vector<vector<int>> t; // Ma trận thời gian di chuyển giữa các địa điểm
vector<bool> visited; // Mảng đánh dấu khách hàng đã được thăm hay chưa
int f = 0; // Thời gian làm việc tối đa hiện tại của một nhân viên
int f_min = INT_MAX; // Thời gian làm việc tối đa nhỏ nhất
int nbR = 0; // Số lượng khách hàng đã được phục vụ
int segments = 0; // Số phân đoạn lộ trình của nhân viên
int tmin = INT_MAX; // Thời gian di chuyển nhỏ nhất giữa các địa điểm
vector<int> x_best, y_best; // Lưu trữ kết quả tối ưu của các lộ trình
vector<int> load; // Tổng thời gian làm việc của mỗi nhân viên

/* Kiểm tra tính hợp lệ khi thử giá trị cho y[k] */
bool check(int v, int k) {
    if (v == 0) return true; // Nếu v = 0 (là điểm kho), thì không có vấn đề gì
    if (visited[v]) return false; // Kiểm tra nếu khách hàng v đã được thăm
    return true;
}

/* Cập nhật kết quả tối ưu nếu f nhỏ hơn f_min */
void updateBest() {
    if (f < f_min) {
        f_min = f;
        x_best = x;
        y_best = y;
    }
}

/* Thử giá trị cho x[s]  */
void TRY_X(int s, int k) {
    if (s == 0) {
        if (k < K) {
            TRY_X(y[k + 1], k + 1);
        }
        return;
    }
    for (int v = 0; v <= n; v++) {
        if (check(v, k)) { // Kiểm tra tính hợp lệ của khách hàng v cho xe tải k
            x[s] = v; // Lưu vị trí của khách hàng v trong lộ trình của xe tải k
            visited[v] = true; // Đánh dấu khách hàng v đã được thăm
            load[k] += t[s][v] + d[v]; // Cộng vào tổng quãng đường
            int temp = f;
            f = max(f, load[k]); // Cập nhật thời gian làm việc tối đa của nhân viên
            segments++;

            if (v > 0) { // Nếu khách hàng không phải kho, tiếp tục tính toán
                if (f < f_min) { // Kiểm tra liệu có thể tối ưu thêm không
                    TRY_X(v, k);
                }
            } else {
                if (k == nbR) {
                    if (segments == n + nbR) {
                        updateBest(); // Cập nhật kết quả nếu tất cả khách hàng đã được phục vụ
                    }
                } else {
                    if (f < f_min) {
                        TRY_X(y[k + 1], k + 1); // Tiến hành thử với lộ trình của xe tải tiếp theo
                    }
                }
            }

            visited[v] = false; // Quay lại trạng thái ban đầu
            load[k] -= t[s][v] + d[v]; // Quay lại trạng thái ban đầu
            f = temp;
            segments--;
        }
    }
}

/* Thử giá trị cho y[k] (lộ trình giao hàng từ kho đến khách hàng) */
void TRY_Y(int k) {
    int s = 0;
    if (y[k - 1] > 0) s = y[k - 1] + 1;
    for (int v = s; v <= n; v++) {
        if (check(v, k)) { // Kiểm tra tính hợp lệ của khách hàng v
            y[k] = v;
            if (v > 0) {
                segments++;
            }
            visited[v] = true;
            load[k] = t[0][v] + d[v]; // Cộng thời gian di chuyển và bảo trì cho nhân viên

            if (k < K) {
                TRY_Y(k + 1); // Tiếp tục thử cho xe tải tiếp theo
            } else {
                nbR = segments; // Đánh dấu số lượng khách hàng đã được phục vụ
                TRY_X(y[1], 1); // Tiến hành thử với lộ trình của các xe tải
            }

            visited[v] = false;
            load[k] = 0;
            if (v > 0) {
                segments--;
            }
        }
    }
}

/* Giải quyết bài toán tìm lộ trình tối ưu */
void solve() {
    f = 0;
    f_min = INT_MAX;
    visited.assign(n + 1, false); // Khởi tạo mảng visited với giá trị false
    x.resize(n + 1, 0); // Khởi tạo vector x với giá trị ban đầu là 0
    y.resize(K + 1, 0); // Khởi tạo vector y với giá trị ban đầu là 0

    // Tìm thời gian di chuyển nhỏ nhất trong ma trận t
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i != j && t[i][j] > 0) {
                tmin = min(tmin, t[i][j]); // Tìm thời gian di chuyển nhỏ nhất
            }
        }
    }

    TRY_Y(1); // Bắt đầu tìm kiếm lộ trình tối ưu từ xe tải đầu tiên

    if (f_min != INT_MAX) {
        cout << K << endl; // In ra số lượng nhân viên
        for (int k = 1; k <= K; k++) {
            vector<int> route; // Lưu trữ lộ trình của nhân viên k
            route.push_back(0); // Bắt đầu từ kho
            int cur = y_best[k];
            while (cur != 0) { // Duyệt qua các điểm trong lộ trình
                route.push_back(cur);
                cur = x_best[cur];
            }
            route.push_back(0); // Quay lại kho
            cout << route.size() << endl; // In ra số lượng điểm trong lộ trình
            for (int v : route) {
                cout << v << " "; // In ra các điểm trong lộ trình
            }
            cout << endl;
        }
    } else {
        cout << "-1" << endl; // Nếu không tìm được lộ trình hợp lệ
    }
}

int main() {
    // Đọc dữ liệu đầu vào
    cin >> n >> K;
    d.resize(n + 1, 0); // Khởi tạo mảng d (thời gian bảo trì của khách hàng)
    load.resize(K + 1, 0);  // Sửa lại kích thước của load
    for (int i = 1; i <= n; i++) {
        cin >> d[i]; // Đọc thời gian bảo trì cho từng khách hàng
    }
    t.resize(n + 1, vector<int>(n + 1)); // Khởi tạo ma trận t (thời gian di chuyển)
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cin >> t[i][j]; // Đọc thời gian di chuyển giữa các địa điểm
        }
    }
    solve(); // Giải quyết bài toán
    return 0;
}

