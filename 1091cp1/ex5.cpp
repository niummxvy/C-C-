#include <stdio.h>
#include <limits.h>
#define SIZE 10000

int main(){
	long long Max = INT_MIN, sum;
	int c = 0, arr[SIZE] = {};
	while(scanf("%d", &arr[c]) != EOF){
		++c;
	}
	for(int i = 0; i < c; ++i){
		sum = 0;
		for(int j = i; j < c; ++j){
			sum += arr[j];
			if(sum > Max) Max = sum;
		}
	}
	printf("Maximum contiguous sum is %lld\n", Max);
	return 0;
} 
