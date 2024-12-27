/* Bài toán cắt vật liệu 2D
   Một tấm phôi kim loại hình chữ nhật có chiều dài H và chiều rộng W cần được cắt thành n miếng hình chữ nhật.
   Miếng thứ i có chiều dài h[i] và chiều rộng w[i]. Hãy tìm cách cắt sao cho thỏa mãn yêu cầu.
   Test case:
2 5 5
2 2
2 3
*/
#include <iostream>
#include <vector>

using namespace std;

int n, H, W;
vector<int> h;
vector<int> w;
vector<vector<bool>> marked(100,vector<bool>(100,false));

bool check(int i1, int j1, int i2, int j2) {
    if (i1 < 0 || i1 >= H || i2 < 0 || i2 >= H || j1 < 0 || j1 >= W || j2 < 0 || j2 >= W)
        return false;
    for (int i = i1; i <= i2; i++) {
        for (int j = j1; j <= j2; j++) {
            if (marked[i][j]) return false;
        }
    }
    return true;
}

void thu(int k) {
    if (k == n) {
        // In kết quả nếu cắt thành công
        for (int h1 = 0; h1 < H; h1++) {
            for (int w1 = 0; w1 < W; w1++) {
                cout << marked[h1][w1] << " ";
            }
            cout << endl;
        }
        cout << endl;
        return;
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            // Cần thử cả hai cách cắt: theo chiều dài x rộng hoặc chiều rộng x dài
            for (int t = 0; t <= 1; t++) {
                int i1, i2, j1, j2;
                if (t == 0) {
                    i1 = i;
                    i2 = i + h[k] - 1;
                    j1 = j;
                    j2 = j + w[k] - 1;
                } else {
                    i1 = i;
                    i2 = i + w[k] - 1;
                    j1 = j;
                    j2 = j + h[k] - 1;
                }

                // Kiểm tra nếu vị trí có thể cắt
                if (check(i1, j1, i2, j2)) {
                    // Đánh dấu các ô đã cắt
                    for (int i = i1; i <= i2; i++) {
                        for (int j = j1; j <= j2; j++) {
                            marked[i][j] = true;
                        }
                    }

                    // Tiếp tục cắt các miếng tiếp theo
                    thu(k + 1);

                    // Hủy đánh dấu các ô đã cắt
                    for (int i = i1; i <= i2; i++) {
                        for (int j = j1; j <= j2; j++) {
                            marked[i][j] = false;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    cin >> n >> H >> W;
    h.resize(n);
    w.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    thu(0);
    return 0;
}


