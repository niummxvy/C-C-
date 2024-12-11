#include <stdio.h>

int main(){
	int N, k, arr[21] = {}, sum = 0, c = 0;
	scanf("%d", &N);
	for(int i = 0; i < N; ++i) arr[i] = i + 1;
	scanf("%d", &k);
	if(k <= N) printf("True\n");
	else{
		for(int i = N-1; i >= 0; ++i){
			if(arr[i] != 0){
				if(k < arr[i] + arr[i-1]){
					if(c % 2 == 0){ // A
						
					}
					else{ // B
						
					}
				else{
					k -= arr[i];
					c++;
				}
			}
			else continue;
		
		}
			
	}
	
	
	return 0;
}
