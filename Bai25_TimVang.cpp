/*Truy tìm kho báu
Description
Trong thế giới huyền bí của vương quốc An Lạc, huyền thoại kể về một lời nguyền cổ xưa mà chỉ những kẻ dũng cảm nhất mới có thể phá vỡ. Vương quốc này có những kho báu bí ẩn, mỗi kho chứa một lượng vàng khổng lồ ciđược đặt tại các vị trí kỳ diệu có toạ độ (xi, yi). Những người đi tìm kho báu chỉ có thể bắt đầu hành trình từ cổng thành cổ tại (0,0) và theo một quy tắc đặc biệt: họ chỉ được phép di chuyển về phía mặt trời mọc - theo hướng không giảm của cả hai toạ độ x và y - để tìm đến các kho báu. Điều này nghĩa là từ kho báu tại (xi, yi), người ta chỉ có thể tiếp tục hành trình đến kho báu (xj, yj) nếu xi ≤ xj và yi ≤ yj.
Kẻ tìm kho báu phải sắp xếp một lộ trình khôn ngoan để thu thập được nhiều vàng nhất, nhưng cần phải nhớ rằng, lời nguyền sẽ chỉ cho phép họ đi theo hướng mặt trời mọc như đã mô tả.
Dữ liệu vào:
Dòng thứ nhất chứa số nguyên dương n là số lượng kho báu (1 ≤ n ≤ 10^3).
Trong n dòng tiếp theo, mỗi dòng chứa hai số nguyên dương xi, yi, ci (1 ≤ xi, yi, ci ≤ 10^9) là toạ độ và lượng vàng của kho báu thứ i, i = 1, 2, …, n.
Kết quả:
Ghi ra một số nguyên duy nhất là tổng lượng vàng lớn nhất có thể tìm được.
Dữ liệu vào
10
2 4 7
4 2 10
4 6 2
5 5 7
1 3 9
1 5 1
1 1 3
3 1 5
3 3 6
2 2 2
Kết quả:
26
Giải thích:
Đường đi tối ưu đi qua các kho báu có toạ độ lần lượt   là (1, 1), (1, 3), (2,4) và (5,5) có tổng lượng vàng là 3 + 9 + 7 + 7 = 26*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Cấu trúc để lưu thông tin về tọa độ và số vàng
struct Treasure {
    int x;           // Tọa độ x
    int y;           // Tọa độ y
    long long gold;  // Lượng vàng tại kho báu
};

// Hàm so sánh để sắp xếp các kho báu theo tọa độ (x, y)
bool compare(const Treasure &a, const Treasure &b) {
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

int main() {
    int n;
    cin >> n;

    vector<Treasure> treasures(n + 1); // Danh sách các kho báu
    for (int i = 1; i <= n; i++) {
        cin >> treasures[i].x >> treasures[i].y >> treasures[i].gold;
    }

    // Sắp xếp các kho báu theo tọa độ (x, y)
    sort(treasures.begin() + 1, treasures.end(), compare);

    // Khởi tạo mảng động `dp` để lưu trữ tổng vàng lớn nhất tại mỗi kho báu
    vector<long long> dp(n + 1, 0);

    // Cập nhật giá trị ban đầu
    for (int i = 1; i <= n; i++) {
        dp[i] = treasures[i].gold;
    }

    long long max_gold = 0; // Tổng lượng vàng lớn nhất có thể đạt được

    // Tính toán theo quy tắc di chuyển
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (treasures[j].y <= treasures[i].y) {
                dp[i] = max(dp[i], dp[j] + treasures[i].gold);
            }
        }
        max_gold = max(max_gold, dp[i]); // Cập nhật giá trị tối đa
    }

    // In kết quả
    cout << fixed << setprecision(0) << max_gold << endl;

    return 0;
}
