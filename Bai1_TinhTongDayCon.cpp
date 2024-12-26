#include<bits/stdc++.h>
using namespace std;

int main(){
    int n ;
    cin >> n ;
    int a[n+1];
    int s[n+1];
    s[0]=0;
    for( int i = 1 ; i <= n ; i++ ){
        cin >> a[i];
        s[i] = s[i-1] + a[i];
    }
    int i , j ;
    cin >> i >> j ;
    int res = s[j] - s[i-1] ;
    cout << res ;


}
