/* Nhị phân hàm số mũ*/
#include<bits/stdc++.h>
int mu(int x , int n){
    if (n==0) return 1;
    if (n==1) return x;
    int y = mu(x,n/2);
    if (n%2==0) {
        return y*y;
    }else{
        return x*y*y;
    }
}
using namespace std;
int main(){
    int x;
    cin >> x;
    int n;
    cin >> n;
    cout << mu(x,n);
}
