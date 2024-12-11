#include <iostream>
using namespace std;

int n, arr[10000 + 5], dp[10000][10000];

int rec(int i, int j, bool isA){ // rec(left, right, if>0) 
 if(i==j){
     if(isA) return arr[i];
     else return -arr[i];
 }else if(dp[i][j]!=-1){
  return dp[i][j];
 }else if(isA){
  dp[i][j] = max(rec(i+1, j, 0)+arr[i], rec(i, j-1, 0)+arr[j]) // A拿，加較多的 
     return dp[i][j];
 }else if(!isA){
  dp[i][j] = min(rec(i+1, j, 1)-arr[i], rec(i, j-1, 1)-arr[j]) // B拿，減較少的 
     return dp[i][j];
 }
 return 0;
}

int main() {
 
 memset(arr, 0, sizeof(arr));
 
 while(cin >> n){
  for(int i=0; i<n; i++)
   for(int j=0; j<n; j++)
    dp[i][j] = -1;
  for(int i=0; i<n; i++){
   cin >> arr[i];
  }
  if(rec(0, n-1, true) >= 0)
      cout << "True\n";
  else
      cout << "False\n";
 }
 
}
