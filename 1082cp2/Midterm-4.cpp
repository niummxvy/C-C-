#include <stdio.h>

int main(){
	int N, k, arr[21] = {}, sum = 0, c = 0;
	scanf("%d", &N);
	for(int i = 0; i < N; ++i) arr[i] = i + 1;
	scanf("%d", &k);
	if(k <= N) printf("True\n");
	else{
		sum = arr[N-1];
		arr[N-1] = 0;
		c++;
		if(c % 2 == 0){
			for(int i = N-1; i >= 0; --i){
				if(arr[i] != 0){
					sum += arr[i];
					break;
				}
			}
			
		}else{
			for(int i = 0; i < N; ++i){
				if(sum + arr[i] >= k){
					printf("False\n");
					break;
				}
				if(arr[i+1] == 0){
					sum = arr[i];
					arr[i] = 0;
					c++;
				}
			}
			
		}
	}
	
	
	
	return 0;
}
