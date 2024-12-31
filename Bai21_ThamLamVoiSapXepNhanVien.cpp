/*Có N nhân viên 1,2,…, N cần được xếp ca trực làm việc cho các ngày 1,  2, …, D.
Mỗi ngày được chia thành 4 kíp: sáng, trưa, chiều, đêm. Biết rằng:
Mỗi ngày, một nhân viên chỉ làm nhiều nhất 1 ca
Ngày hôm trước làm ca đêm thì hôm sau được nghỉ
Mỗi ca trong mỗi ngày có ít nhất A nhân viên và nhiều nhất B nhân viên
F(i): danh sách các ngày nghỉ phép của nhân viên i
Xây dựng phương án xếp ca trực cho N nhân viên sao cho
Số ca đêm nhiều nhất phân cho 1 nhân viên nào đó là nhỏ nhất
Một lời giải được biểu diễn dưới dạng ma trận X[1..N][1..D], trong đó x[i][d] là ca làm việc được sắp xếp cho nhân viên i vào ngày d (giá trị 1 nghĩa là ca sáng, giá trị 2 nghĩa là ca chiều, giá trị 3 nghĩa là ca tối, giá trị 4 nghĩa là ca đêm, giá trị 0 nghĩa là ngày nghỉ).
Dữ liệu đầu vào:
Dòng 1: chứa 4 số nguyên dương N, D, A, B (1 ≤ N ≤ 500, 1 ≤ D ≤ 200, 1 ≤ A ≤ B ≤ 500).
Dòng i+1 (với i = 1, 2, ..., N): chứa một danh sách các số nguyên dương là các ngày nghỉ của nhân viên i (các ngày được đánh số từ 1 đến D), kết thúc bằng -1.
Dữ liệu đầu ra:
Dòng i (với i = 1, 2, ..., N): ghi hàng thứ i của ma trận lời giải X.
Example
Input
8 6 1 3
1  -1
3 -1
4 -1
5 -1
2 4  -1
-1
-1
3 -1
Output
0 1 3 1 4 0
4 0 0 1 2 2
2 4 0 0 2 2
3 1 4 0 0 4
1 0 2 0 1 1
3 2 1 2 3 3
2 3 2 4 0 3
1 3 0 3 1 1*/
#include <bits/stdc++.h>
using namespace std;

int n, d, a, b;
vector<vector<bool>> coTheNghi;
vector<vector<int>> x, x_best;
vector<vector<int>> nvtrongca;
vector<int> soCaDem;
vector<int> r;
int f = 0;
int min_f = d + 2;
int max_loop = 10;
int loop = 0;
bool check(int nv, int ngay, int ca) {
    if (coTheNghi[nv][ngay]) {
        if (ca != 0) return false;
    }
    if (ngay > 1) {
        if (x[nv][ngay - 1] == 4) {
            if (ca != 0) return false;
        }
    }
    if (ca != 0 && nvtrongca[ngay][ca] + 1 > b) return false;
    if (ca == 4 && soCaDem[nv] + 1 >= min_f) return false;
    return true;
}

bool checkNgay(int ngay) {
    for (int ca = 1; ca <= 4; ca++) {
        if (nvtrongca[ngay][ca] < a || nvtrongca[ngay][ca] > b) return false;
    }
    return true;
}

void capNhatLoiGiai() {
    if (f < min_f) {
        min_f = f;
        x_best = x;
        loop ++;
    }
}

void sapXep() {
    // Sort employees by the number of night shifts assigned
    sort(r.begin() + 1, r.end(), [](int a, int b) {
        return soCaDem[a] < soCaDem[b];
    });
}

void thu(int k, int ngay) {
    if (k > n) {
        if(loop >= max_loop) return ;
        if (checkNgay(ngay)) {
            if (ngay == d) {
                capNhatLoiGiai();
                return;
            }
            sapXep();
            thu(1, ngay + 1);
        }
        return;
    }
    int nv = r[k];
    for (int ca = 0; ca <= 4; ca++) {
        if (check(nv, ngay, ca)) {
            x[nv][ngay] = ca;
            int old_f = f;

            if (ca != 0) {
                nvtrongca[ngay][ca]++;
            }
            if (ca == 4) {
                soCaDem[nv]++;
                f = max(f, soCaDem[nv]);
            }

            thu(k + 1, ngay);

            if (ca != 0) {
                nvtrongca[ngay][ca]--;
            }
            if (ca == 4) {
                soCaDem[nv]--;
                f = old_f;
            }
        }
    }
}

int main() {
    cin >> n >> d >> a >> b;
    coTheNghi.resize(n + 1, vector<bool>(d + 1, false));
    x.resize(n + 1, vector<int>(d + 1, 0));
    x_best.resize(n + 1, vector<int>(d + 1, 0));
    nvtrongca.resize(d + 1, vector<int>(5, 0));
    soCaDem.resize(n + 1, 0);
    r.resize(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        while (true) {
            int temp;
            cin >> temp;
            if (temp == -1) break;
            coTheNghi[i][temp] = true;
        }
        r[i] = i;
    }

    thu(1, 1);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= d; j++) {
            cout << x_best[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}

