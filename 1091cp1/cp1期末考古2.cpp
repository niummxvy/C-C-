#include <stdio.h>

int main(){
	long long pascal[50][50] = {};
	int triangle[50][500] = {};
	for(int i = 0; i < 50; ++i) pascal[i][0] = 1;
	for(int i = 1; i < 50; ++i){
		for(int j = 1; j <= i; ++j){
			pascal[i][j] = pascal[i-1][j-1] + pascal[i-1][j];
		}
	}
/*	for(int i = 0; i < 50; ++i){
		for(int j = 0; j <= i; ++j){
			printf("%lld ", pascal[i][j]);
		}
		printf("\n");
	} */
	int rowSize[50] = {};
	for(int i = 0; i < 50; ++i){
		for(int j = 0; j <= i; ++j){
			long long divide = 1;
			while(pascal[i][j] / divide >= 10) divide *= 10;
			while(pascal[i][j] != 0){
				if(pascal[i][j] != 0 && pascal[i][j] / divide == 0) triangle[i][rowSize[i]++] = 0; // e.g. 203
				else triangle[i][rowSize[i]++] = (pascal[i][j] / divide);
				pascal[i][j] %= divide;
				divide /= 10;
				if(pascal[i][j] == 0 && divide == 1) triangle[i][rowSize[i]++] = 0; // e.g. 230, 100, 2030
			}
		}
	}
/*	for(int i = 0; i < 50; ++i){
		for(int j = 0; j < rowSize[i]; ++j){
			printf("%d", triangle[i][j]);
		}
		printf("\n");
	} */
	
	int idx, d, cnt = 0;
	scanf("%d %d", &idx, &d);
	for(int i = 0; i < rowSize[idx]; ++i){
		while(triangle[idx][i] != 0){
			if(triangle[idx][i] % 10 == d) ++cnt;
			triangle[idx][i] /= 10;
		}
	}
	printf("%d\n", cnt);
	return 0;
} 
