// reference:  https://leetcode.com/problems/can-i-win/discuss/95320/Clean-C++-beat-98.4-DFS-with-early-termination-check-(detailed-explanation)

#include <stdio.h>


// m[key]: memorized game result when pool state = key
// 0: un-computed; 1: I win; -1: I lose
int mem[1<<20] = {};

int canIWin(int n, int k){
    int sum = n*(n+1)/2; // sum of entire choosable pool
    
    // Total is too large, nobody can win
    if (sum < k) return 0;
    
    // Total happens to match sum, whoever picks at odd times wins
    else if (sum == k) return n%2;
    
    // Non-trivial case: do recursive
    // Initial total: T
    // Initial game state: m = 0 (all numbers are not picked)
    else return recursive(n, k, 0);
}

  // recursive to check if I can win
  // k: current game state
  // T: remaining total to reach
int recursive(int n, int k, int m) {
    // memorized
    if (mem[m] != 0) return mem[m] > 0;
    
    // total is already reached by opponent, so I lose
    if (k <= 0) return 0;

    // try all currently available numbers
    for (int i = 0; i < n; ++i){
    	// i = 0
    	// 1<< 0 => 1 & m => 0 => !0 => 1     m|1 => 1
    	// 1<< 0 => 1 & m(1) => 1 => !1 => 0

    	// recursive() => 1 =>!1 => 0 / =>0 =>!0 =1
      // if (i+1) is available to pick and my opponent can't win after I picked, I win!
      if ( !( m & (1<<i) ) && !recursive(n, k-i-1, m|(1<<i))) {
        mem[m] = 1;
        return 1;
      } 
    }
    // Otherwise, I will lose
    // printf("%d %d %d\n", n,k,m);
    mem[m] = -1;
    return 0;      
}

int main(){
	int n,k,ans;
	scanf("%d\n%d\n",&n,&k);
	ans = canIWin(n,k);
	ans ? printf("True\n") : printf("False\n");
	return 0;
}
  
  