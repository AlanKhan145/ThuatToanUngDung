/*Nhà Kho (Warehouse)
Mô tả bài toán
Một chiếc xe tải được lên kế hoạch để đến một số ga trong số N ga, được đánh số từ 1, 2, ..., N, nằm trên một đường thẳng.
Mỗi ga i (với i từ 1 đến N) có:
ai: Số lượng hàng hóa tại ga đó.
ti: Thời gian bốc hàng tại ga đó.
Quy tắc:
Lộ trình của xe tải là một dãy các ga x1 < x2 < ... < xk (với 1 ≤ xj ≤ N).
Do hạn chế kỹ thuật:
Khoảng cách giữa hai ga liên tiếp mà xe tải ghé qua, xi và xi+1, phải nhỏ hơn hoặc bằng D.
Tổng thời gian bốc hàng không được vượt quá T.
Nhiệm vụ:
Tìm lộ trình cho xe tải sao cho tổng lượng hàng hóa mà xe tải thu gom là lớn nhất.
Đầu vào:
Dòng 1: N T D (1 ≤ N ≤ 1000, 1 ≤ T ≤ 100, 1 ≤ D ≤ 10).
Dòng 2: a1, a2, ..., aN (1 ≤ ai ≤ 10): Lượng hàng hóa tại các ga.
Dòng 3: t1, t2, ..., tN (1 ≤ ti ≤ 10): Thời gian bốc hàng tại các ga.
Đầu ra:
Một số nguyên: Tổng lượng hàng hóa lớn nhất mà xe tải thu gom được.
Ví dụ:
Đầu vào:
6 6 2
6 8 5 10 11 6
1 2 2 3 3 2
Đầu ra:
24
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, T, D;
    cin >> N >> T >> D;

    vector<int> a(N + 1), t(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= N; i++) {
        cin >> t[i];
    }

    // dp[i][j]: Tổng hàng hóa lớn nhất khi đến ga i tại thời gian j
    vector<vector<int>> dp(N + 1, vector<int>(T + 1, 0));
    int res = 0;
    for(int ga = 1 ; ga <= N ; ga++){
        dp[ga][t[ga]] = a[ga];
    }
    for(int ga = 1 ; ga <= N ; ga++){
        for(int tg = t[ga]+1 ; tg <= T ; tg++ ){
            for(int k = max(1,ga-D) ; k < ga ; k++){
                dp[ga][tg] = max(dp[ga][tg],dp[k][tg-t[ga]] + a[ga]);
            }
            res = max(res,dp[ga][tg]);
        }
    }
    cout << res <<endl;
    return 0;
}
