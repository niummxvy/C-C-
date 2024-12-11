#include <stdio.h>

int N, arr[101][101] = {}, dp[101][101] = {};
long long Max = 0, sum = 0;
void fill(int row);
int main(){
	scanf("%d", &N);
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j){		
			scanf("%d", &arr[i][j]);
		}
	}
	
	for(int i = 0; i < N; ++i){
		fill(i);
	}
	printf("%d\n", Max);
	Max = 0;
	
	return 0;
}

void fill(int row){
	for(int i = row; i < N; ++i){
		for(int k = 0; k < N; ++k){
			if(i == row){
				dp[i][k] = arr[i][k];
			}else{
				dp[i][k] = dp[i-1][k] + arr[i][k];
			}
			sum += dp[i][k];
			if(sum < 0) sum = 0;
			if(sum > Max) Max = sum;
		}
		sum = 0;
	}
}

