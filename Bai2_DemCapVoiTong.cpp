#include<bits/stdc++.h>
using namespace std ;
int main(){
    int n;
    cin >> n ;
    int a[n+1];
    for( int i = 0 ; i < n ; i ++ ){
        cin >> a[i+1];
    }
    int q;
    cin >> q ;
    int count = 0 ;
    int l = 1 ;
    int r = n ;
    while(l < r ){
        if(a[l]+a[r]==q){
            count ++;
            l++;
            r--;
        }
        else if(a[l]+a[r]<q){
            l++;
        }
        else {
            r--;
        }
    }
    cout << count ;
    return 0;
}



