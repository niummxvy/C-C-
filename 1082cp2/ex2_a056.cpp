#include <stdio.h>
// #include <stdlib.h>

int main(){
	int K;
	scanf("%d", &K);
	for(int i = 0; i < K; i++){
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		if(x != y && y != z && x != z){
			printf("YES\n");
			continue;
		}
		printf("NO\n");
	}
//	system("pause");
	return 0;
}
