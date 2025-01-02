/*Count solutions to an integer linear equation
Description
Given a positive integer n and n positive integers a1, a2, ..., an.
Compute the number of positive integer solutions to the equation:
    a1X1+ a2X2+ . . . + anXn= M
Input
Dòng 1: n và M
Dòng 2: a1, a2, ..., an
Output
   Số nghiệm nguyên dương
Ví dụ
Input
3 5
1 1 1
Output
6*/
#include<bits/stdc++.h>
using namespace std;
int n;
int m;
vector<int> a ;
vector<int> x ;
int f = 0 ;
int dem = 0 ;
void thu(int k){
    for(int i = 1 ; i <= m ; i++){
        x[k] = i;
        f = f + x[k]*a[k];
        if(k == n ){
            if(f == m) dem++ ;
        }else if (f < m){
            thu(k+1);
        }
        f = f - x[k]*a[k];
    }
}
int main(){
    cin >> n >> m;
    a.resize(n+1);
    for(int i = 1 ; i <= n ; i++){
        cin >> a[i];
    }
    x.resize(n+1);
    thu(1);
    cout << dem ;
    return 0;
}
