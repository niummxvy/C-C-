#include <stdio.h>
#include <math.h>

int main(){
	long double p;
	int N, n;
	scanf("%d", &N);
	for(int i = 0; i < N; ++i){
		scanf("%d", &n);
		scanf("%Lf", &p);
		printf("%d %d %Lf", N, n, p);
	}
	
	
	
	return 0;
}
