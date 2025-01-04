/*Quy hoạch động dãy con tăng dài nhất*/
#include<bits/stdc++.h>
using namespace std;
int main(){
  int n ;
  cin>> n ;
  vector<int> a(n+1);
  for(int i = 1 ; i <= n ; i++ ){
    cin >> a[i];
  }
  vector<int>d(n+1,1);
  d[1] = 1 ;
  int max_kc = 1;
  for(int i = 2 ; i <= n ; i++){
    for(int k = i - 1 ; k >= 1 ; k--){
      if(a[k]<a[i]){
        d[i] = max(d[i],d[k]+1);
      }
    }
    max_kc = max(max_kc,d[i]);
  }
  cout << max_kc<<endl;
  return 0;
}
