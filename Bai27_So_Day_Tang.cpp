/*Huyền đang có một dãy số nguyên a = a1, a2, ..., an.
Cô muốn cắt a thành các đoạn con gồm các phần tử liên tiếp của a, sao cho mỗi đoạn đều là một dãy tăng.
Hãy giúp Huyền tính xem cô phải cắt a thành ít nhất bao nhiêu đoạn con thỏa mãn tính chất trên.
Dữ liệu vào:
Dòng đầu chứa số nguyên dương n (1 ≤ n ≤ 10^5).
Dòng tiếp theo chứa n số nguyên dương a1, a2, ..., an (0 ≤ ai ≤ 10^9).
Kết quả:
Ghi một số nguyên duy nhất là số ít nhất các đoạn con tăng của a.
Ví dụ:
Test case 1:
Input:
6
3 6 1 7 8 2
Output:
3
Test case 2:
Input:
5
1 2 3 4 5
Output:
1
Giải thích: Dãy a được cắt thành các đoạn con tăng là (3, 6), (1, 7, 8), (2).*/
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n ;
    cin >> n;
    vector<int> a(n+1);
    for(int i = 1 ; i <= n ; i++){
        cin >>a[i];
    }
    int count = 1;
    for(int i = 1 ; i < n ; i++){
        if(a[i+1] < a[i]) {
            count++;
        }
    }
    cout << count;
    return 0;
}
