#include <stdio.h>

int main(){
	int N;
	while(scanf("%d", &N)){
		if(N <= 0) break;
		int mat[101][101] = {}, sum[2][101] = {};
		for(int i = 0; i < N; ++i){
			for(int j = 0; j < N; ++j){
				scanf("%d", &mat[i][j]);
			}
		}
		 
		for(int i = 0; i < N; ++i){
			for(int j = 0; j < N; ++j){
				sum[0][i] += mat[i][j];
				sum[1][i] += mat[j][i];
			}
		}
		
		int odd_row = 0, odd_col = 0, x, y;
		for(int i = 0; i < 2; ++i){
			for(int j = 0; j < N; ++j){
				if(sum[i][j] % 2 != 0 && i == 0) ++odd_row;	
				if(sum[i][j] % 2 != 0 && i == 1) ++odd_col;	
			}
		}
		if(odd_row == 0 && odd_col == 0) printf("OK\n");
		else if(odd_row == 1 && odd_col == 1){
			for(int i = 0; i < 2; ++i){
				for(int j = 0; j < N; ++j){
					if(sum[i][j] % 2 != 0 && i == 0) x = j+1;
					if(sum[i][j] % 2 != 0 && i == 1) y = j+1;
				}
			}
			printf("Change bit (%d,%d)\n", x, y);
		}
		else printf("Corrupt\n");
	}
	return 0;
} 
