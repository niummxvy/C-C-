#include <stdio.h>
int max(int a, int b){
	if(a >= b) return a;
	else return b;
}
int main(){
	int N, arr[101] = {}, sum = 0, Max = -2147483647;
	scanf("%d", &N);
	for(int i = 0; i < N; ++i){
		scanf("%d", &arr[i]);
	}
	for(int i = 0; i < N; ++i){
		sum = max(sum + arr[i], arr[i]);
		Max = max(Max, sum);
	}
	printf("%d\n", Max);
	return 0;
}


