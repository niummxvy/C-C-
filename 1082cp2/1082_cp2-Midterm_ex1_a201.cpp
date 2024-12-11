#include <stdio.h>
#include <stdlib.h>

int cmp(const void * a, const void * b){
	if(*(int*)a <= *(int*)b) return 0;
	else return 1;
}

int main(){
	int time, N;
	while(scanf("%d", &time) != EOF){
		getchar();
		for(int j = 0; j < time; ++j){
 
			int count = 0;
			char arr[101] = {};
			int temp[101] = {};
			for(int i = 0; i < 100; ++i){
				scanf("%c", &arr[i]);
				if(arr[i] == ' '){
					i--;
					continue;
				}
				if(arr[i] == '\n') break;
				temp[i] = (int)arr[i];
				if(i > count) count = i;
			}
			qsort(temp, count+1, sizeof(int), cmp);
			for(int i = 0; i <= count; ++i){
				printf("%c ", (char)temp[i]);
			} 
//			printf("AAA\n");
			printf("\n");
		}
	}
	return 0;
} 
