#include <stdio.h>

int main(){
	int N, box, arr[51] = {}, num, count = 0, c = 0;
	scanf("%d", &N);
	for(int i = 0; i < N; ++i){
		scanf("%d", &box);
		for(int j = 0; j < box; ++j){
			scanf("%d", &num);
			arr[j] = num;
		}
		for(int k = 0; k < box-1; ++k){
			for(int j = 0; j < box-1; ++j){
				if(arr[j] > arr[j+1]){
					int temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
					count++;
				}
			}
		}
		printf("%d\n", count);
		count = 0;
	}
	
	
	return 0;
}
