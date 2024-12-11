#include <stdio.h>

int main(){
	int L, W, x, y, A, b;
	
	while(scanf("%d %d %d %d", &L, &W, &x, &y) != EOF){
		if(L == 0) break;
		A = L * W;
		b = x * y;
		if(A % b != 0) printf("-1\n");
		else printf("%d\n", A / b);
	}
	
	
	return 0;
}
