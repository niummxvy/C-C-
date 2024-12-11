#include <stdio.h>
#include <limits.h>
#define SIZE 10000
// #define MAX (a, b) ((a) > (b) ? (a):(b))

int MAX(int a, int b){
	if(a >= b) return a;
	else return b;
}

int main(){
	long long Max = INT_MIN, sum;
	int c = 0, arr[SIZE] = {};
	while(scanf("%d", &arr[c]) != EOF){
		++c;
	}
	sum = 0;
	for(int i = 0; i < c; ++i){
		Max = MAX(Max, arr[i]);
	}
	if(Max < 0){ // every element < 0 will happen
		printf("Maximum contiguous sum is %lld\n", Max);
	}else{
		Max = INT_MIN;
		for(int i = 0; i < c; ++i){
			if(sum + arr[i] < 0) sum = 0;
			else sum += arr[i];
			Max = MAX(Max, sum);
//			printf("sum: %lld\n", sum);
		}
		printf("Maximum contiguous sum is %lld\n", Max);
	}
	return 0;
} 
