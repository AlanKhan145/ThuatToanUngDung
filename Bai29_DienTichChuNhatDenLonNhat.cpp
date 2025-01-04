//C++
/*Một hình chữ nhật kích thước n x m được chia thành các ô vuông con 1 x 1 với 2 màu đen hoặc trắng. Hình chữ nhật được biểu diễn bởi ma trận A(n x m) trong đó A(i, j) = 1 có nghĩa ô hàng i, cột j là ô đen và A(i, j) = 0 có nghĩa ô vuông hàng i cột j là ô trắng.
Hãy xác định hình chữ nhật con của bảng đã cho bao gồm toàn ô đen và có diện tích lớn nhất.
Dữ liệu
· Dòng 1: chứa số nguyên dương n và m (1 <= n,m <= 1000)
· Dòng i+1 (i = 1,…, n): chứa hàng thứ i của ma trận A
Kết quả
· Ghi ra diện tích của hình chữ nhật lớn nhất tìm được
Ví dụ
Dữ liệu
4 4
0 1 1 1
1 1 1 0
1 1 0 0
1 1 1 0
Kết quả
6*/
#include<bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n , m ;
    cin >> n >> m;
    vector<vector<int>>A(n+1,vector<int>(m+1));
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= m ; j++){
            cin >>A[i][j];
        }
    }
    int dai_tam;
    int cao_tam;
    int max_s = 0;
    vector<int>cotlientiep(m+1,0);
    for(int hang = 1 ; hang <= n ; hang++){
        for(int cot = 1 ; cot <= m ; cot ++){
            if(A[hang][cot] == 0) cotlientiep[cot] = 0;
            else cotlientiep[cot] ++;
        }
        for(int cot_sau = 1 ; cot_sau <= m ; cot_sau++){
            if(A[hang][cot_sau] == 1){
                dai_tam = 1;
                cao_tam = cotlientiep[cot_sau];
                max_s = max(max_s,dai_tam*cao_tam);
                for(int cot_truoc = cot_sau - 1 ; cot_truoc > 0 ; cot_truoc--){
                   if(A[hang][cot_truoc] == 0) break;
                   dai_tam++;
                   cao_tam = min(cao_tam,cotlientiep[cot_truoc]);
                   max_s = max(max_s,dai_tam*cao_tam);
                }
            }
        }
    }
    cout<<max_s;
    return 0;
}
