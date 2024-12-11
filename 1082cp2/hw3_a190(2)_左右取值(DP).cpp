#include <stdio.h>

int record(int L, int R, int isA);

int max(int a, int b){
	if(a > b) return a;
	else if(b > a) return b;
	else if(a == b) return a;
}

int min(int a, int b){
	if(a < b) return a
	else if(b < a) return b;
	else if(a == b) return a;
}

int N, arr[101] = {}, dp[101][101] = {};

int main(){
	while(scanf("%d", &N) != EOF){
		for(int i = 0; i < 101; ++i){ // initialize
			arr[i] = 10001;
		}
		for(int i = 0; i < N; ++i){ // initialize
			for(int j = 0; j < N; ++j){	
				dp[i][j] = -1;
			}
		}

		for(int i = 0; i < N; ++i){
			scanf("%d", &arr[i]);
		}
		
		if(record(0, N-1, 1) >= 0){
			printf("True\n");
		}else{
			printf("False\n");
		}
/*		for(int i = 0; i < N; ++i){
			for(int j = 0; j < N; ++j){			
				printf("%d ", dp[i][j]);
			}
			printf("\n");
		}  */
	}
	return 0;
}

int record(int L, int R, int isA){
	if(dp[L][R] != -1) return dp[L][R];
	if(L == R){
		if(isA == 1) return arr[L];
		else return -arr[L];
	}	
	if(isA == 1)
		dp[L][R] = max(record(L+1, R, 0) + arr[L], record(L, R-1, 0) + arr[R]);
	else if(isA == 0)
		dp[L][R] = min(record(L+1, R, 1) - arr[L], record(L, R-1, 1) - arr[R]);
}

