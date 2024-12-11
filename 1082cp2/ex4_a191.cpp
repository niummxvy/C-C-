#include <stdio.h>

int main(){
	int N, arr[101][101] = {}, Maxi = 0, Maxj = 0, Maxk = 0, Maxm = 0;
	long long Max = 0, sum = 0;
	scanf("%d", &N);
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j){		
			scanf("%d", &arr[i][j]);
		}
	}
	for(int i = 0; i < N; ++i){ // decide where to start (row)
		for(int j = 0; j < N; ++j){ // decide where to start (column)	
			for(int k = 1; k <= N-i; ++k){ // decide the width of subrectangle
				for(int m = 1; m <= N-j; ++m){ // decide the length of subrectangle
					for(int n = i; n < i+k; ++n){ // to accumulate (row)
						for(int p = j; p < j+m; ++p){ // to accumulate (column)
							sum += arr[n][p];
						}
					}
					if(sum > Max){
						Max = sum;
						Maxi = i;
						Maxj = j;
						Maxk = k;
						Maxm = m;
					}
					sum = 0;
				}
			}
		}
	}
	printf("%d\n", Max);
	return 0;
}
