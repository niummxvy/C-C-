#include <stdio.h>
int N, k, arr[21] = {} sum = 0, c = 0, dp[21][21] = {};
int res(int A, int B, int who){
	if(who == 1)
		dp[A][B] = max(res(A, B, 0), res(A, B, 0));
	else if(who == 0)
		dp[A][B] = min(res(A, B, 1), res(A, B, 1));
}




int main(){
	
	scanf("%d", &N);
	for(int i = 0; i < N; ++i) arr[i] = i + 1;
	scanf("%d", &k);
	if(res(, , 1) >= 0) printf("True\n");
	
	
	return 0;
}
