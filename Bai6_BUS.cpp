#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int n; // Số khách cần phục vụ
int K; // Số chỗ ngồi tối đa trên xe buýt
int d[201][201]; // Ma trận khoảng cách
int x[201]; // Lưu vị trí tại lượt thứ k
vector<bool> visited(201, false); // Lưu xe đã đi qua điểm đón chưa
int currentDistance = 0; // Tổng khoảng cách hiện tại
int passengerCount = 0; // Số khách hiện tại trên xe
int minDistance = INT_MAX; // Kết quả tổng quãng đường nhỏ nhất
int d_min = INT_MAX; // Khoảng cách nhỏ nhất giữa các điểm
int best_route[201];

bool isValid(int i, int k) {
    if (visited[i]) return false;
    if (i <= n) { // Điểm đón khách
        if (passengerCount + 1 > K) return false;
    } else { // Điểm trả khách
        if (!visited[i - n]) return false; // Chưa đón khách i mà đã trả khách
    }
    return true;
}

void solve(int k) {
    for (int i = 1; i <= 2 * n; i++) {
        if (isValid(i, k)) {
            x[k] = i;
            visited[i] = true;

            // Cập nhật trạng thái tạm thời
            int tempDistance = currentDistance;
            int tempPassengerCount = passengerCount;

            currentDistance += d[x[k - 1]][x[k]];
            if (i <= n) passengerCount++; // Đón khách
            else passengerCount--;       // Trả khách

            // Nếu đã hoàn thành lộ trình
            if (k == 2 * n) {
                int totalDistance = currentDistance + d[x[k]][0];
                if (totalDistance < minDistance) {
                    minDistance = totalDistance;
                    for (int m = 0; m <= 2 * n; m++) {
                        best_route[m] = x[m];
                    }
                }
            } else if (currentDistance + d_min * (2 * n + 1 - k) < minDistance) {
                solve(k + 1);
            }

            // Khôi phục trạng thái
            currentDistance = tempDistance;
            passengerCount = tempPassengerCount;
            visited[i] = false;
        }
    }
}

int main() {
    cin >> n >> K;
    x[0] = 0;
    for (int i = 0; i <= 2 * n; i++) {
        for (int j = 0; j <= 2 * n; j++) {
            cin >> d[i][j];
            if (i != j) {
                d_min = min(d_min, d[i][j]);
            }
        }
    }

    solve(1);

    cout << minDistance << endl;
    for (int i = 0; i <= 2 * n; i++) {
        cout << best_route[i] << " ";
    }
    return 0;
}

