#include <stdio.h>

void fill(int level, long long sumA, long long sumB);
int N, ifTrue = 0, arr[101], Max = 0, ifMax = 0, M;
int main(){
	int sum = 0;
	while(scanf("%d", &N) != EOF){
		if(N == 1){
			printf("True\n");
			continue;
		}
		for(int i = 0; i < 101; ++i){ // initialize
			arr[i] = 10001;
		}
		
		for(int i = 0; i < N; ++i){
			scanf("%d", &arr[i]);
			if(arr[i] > Max){
				Max = arr[i];
				M = i;
			}
		}
		for(int i = 0; i < N; ++i){
			
			if(i == N-1){
				if(sum < Max){
					ifMax = 1;
				}
			}
			
			if(i == M){
				continue;
			}
			
			sum += arr[i];
		}
		fill(0, 0, 0);
		if(ifTrue == 1)
			printf("True\n");
		else
			printf("False\n");
		ifTrue = 0;
		ifMax = 0;
		Max = 0;
		sum = 0;
	}

	return 0;
} 

void fill(int level, long long sumA, long long sumB){
	int temp = 10002;
	int L, R; // first non-10001 element at both sides
	if(level == N){ // check at the last level 
//		printf("(level == N) ifTrue: %d, level:%d, A:%d, B:%d\n", ifTrue, level, sumA, sumB);
		if(sumA < sumB)
			return;
		else if(sumA >= sumB){ // if A can win at any condition, return right away
			ifTrue = 1;
			return;
		}
	}
	
	if(ifMax == 1){ // one element is too large
		if(arr[0] == Max || arr[N-1] == Max){ // Max is at one end
			ifTrue = 1;
			return;
		}
		
		for(int i = 0; i < N; ++i){
			if(i == M-1 || i == M || i == M+1)
				continue;
			arr[i] = 10001;
			++level;
		}
		
		if(level % 2 != 0){
			ifTrue = 1;
			return;
		}
		else{
			return;
		}
		
	}
	
	for(int i = 0; i < N; ++i){
		if(arr[i] != 10001){
			L = i;
			break;
		}
	}
	for(int i = N-1; i >= 0; --i){
		if(arr[i] != 10001){
			R = i;
			break;
		}
	}
			// find non-10001 element at both sides
			if(level % 2 == 0){ // even level
				if(arr[L] >= arr[R]){
					temp = arr[L];		
					sumA += temp;
					arr[L] = 10001;
//					printf("AAA\n");
//					printf("(1) ifTrue: %d, level:%d, A:%d, B:%d\n", ifTrue, level, sumA, sumB);
					fill(level+1, sumA, sumB);
					if(ifTrue == 1)
						return;
					
					arr[L] = temp;
					sumA -= temp;
					
				}
				else if(arr[L] < arr[R]){
					temp = arr[R];
					sumA += temp;
					arr[R] = 10001;
//					printf("BBB\n");
//					printf("(1) ifTrue: %d, level:%d, A:%d, B:%d\n", ifTrue, level, sumA, sumB);
					fill(level+1, sumA, sumB);
					if(ifTrue == 1)
						return;
					
					arr[R] = temp;
					sumA -= temp;
					
				}
					
			}
			else{ // odd level
				if(arr[L] >= arr[R]){
					temp = arr[L];
					sumB += temp;
					arr[L] = 10001;
//	 	  			printf("CCC\n");
//					printf("(1) ifTrue: %d, level:%d, A:%d, B:%d\n", ifTrue, level, sumA, sumB);
					fill(level+1, sumA, sumB);
					if(ifTrue == 1)
						return;
					
					arr[L] = temp;
					sumB -= temp;
					
				}
				else if(arr[L] < arr[R]){
					temp = arr[R];
					sumB += temp;
					arr[R] = 10001;
//					printf("DDD\n");
//					printf("(1) ifTrue: %d, level:%d, A:%d, B:%d\n", ifTrue, level, sumA, sumB);
					fill(level+1, sumA, sumB);
					if(ifTrue == 1)
						return;
					
					arr[R] = temp;
					sumB -= temp;
					
				}
			}
//	printf("(LAST) ifTrue: %d, level:%d, A:%d, B:%d\n", ifTrue, level, sumA, sumB);
	return;
}
