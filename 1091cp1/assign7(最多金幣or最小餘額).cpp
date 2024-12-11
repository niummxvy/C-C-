#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define min(a, b) ((a) < (b) ? (a) : (b))

int cmp(const void * a, const void * b){
	return *(int*)a < *(int*)b;
}

int trial(int *arr, int sum, int rest, int itr, int N){
	int temp_itr = itr;
	if(temp_itr == N && rest == INT_MAX) return sum;
	if(sum - arr[temp_itr] >= 0){
		for(int j = temp_itr; j < N; ++j){
			rest = min(rest, trial(arr, sum - arr[j], rest, j+1, N));
			if(rest == 0) return rest;
		}
	}
	else{
		for(int i = itr; i < N; ++i){
			if(arr[i] < arr[itr] && sum - arr[i] >= 0){
				return trial(arr, sum - arr[i], rest, i+1, N);
			}
		}
		return sum;
	}
	return rest;
}

int main(){
	int N, K, rest = INT_MAX, min_rest = INT_MAX;
	int arr[21] = {};
	int *p = arr;
	scanf("%d %d", &N, &K);
	if(N <= 0) return 0;
	for(int i = 0; i < N; ++i){
		scanf("%d", &arr[i]);
	}
	qsort(p, N, sizeof(int), cmp);
	for(int i = 0; i < N; ++i){
//		printf("start at [%d]: \n", i);
		rest = trial(arr, K, rest, i, N);
//		printf("rest: %d\n", rest);
		min_rest = min(min_rest, rest);
		rest = INT_MAX;
	}
	printf("%d\n", K-min_rest);
	return 0;
} 
