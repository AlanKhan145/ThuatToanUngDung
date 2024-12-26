#include<bits/stdc++.h>
using namespace std;
int main(){
    int n ;
    cin >> n ;
    int a[n] ;
    for(int i = 0 ; i < n ; i++ ){
        cin >> a[i];
    }
    int q ;
    cin >> q ;
    int s=0;
    int l = 0;
    int count = 0 ;
    for (int r = 1 ; r < n ; r++){
        s=s+a[r];
        while(s>q){
            s = s - a[l];
            l = l + 1 ;
        }
        count ++;
    }
    cout<<count ;
    return 0 ;
}

