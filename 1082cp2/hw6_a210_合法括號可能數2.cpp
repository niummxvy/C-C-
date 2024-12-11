#include <stdio.h>
#include <string.h>
#define SIZE 40

int ans = 0;

int isvalid(char arr[SIZE]){
	int count = 0;
	for(int i = 0; i < strlen(arr); ++i){
		if(arr[i] == '(') count++;
		else if(arr[i] == ')') count--;
		
		if(count < 0) return 0;
	}
	if(count != 0) return 0;
	return 1;
}

void take(char arr[SIZE], int start, int L, int R){
	if(L == 0 && R == 0){
		if(isvalid(arr) == 1){
			ans++;
		}
	}
	else{
		for(int i = start; i < SIZE; ++i){
			if( i == 0 || (i != 0 && arr[i] != arr[i-1]) ){
				char temp[SIZE];
				strcpy(temp, arr);
				if(arr[i] == '(' && L > 0){
					temp[i] = ' ';
					take(temp, i+1, L-1, R);
				}
				else if(arr[i] == ')' && R > 0){
					temp[i] = ' ';
					take(temp, i+1, L, R-1);
				}
			}
		}
	}
	
}

int main(){
	char par[SIZE] = {};
	int Lcheck = 0, left = 0, right = 0, N;
	for(int i = 0; i < SIZE; ++i){
		scanf("%c", &par[i]);		
		if(par[i] == '\n'){
			par[i] = '\0';
			N = i;
			break;
		}
		if(par[i] == '(') Lcheck = 1;
		if(Lcheck == 0 && par[i] == ')') i--;
		// remove ')'s before the first '('
		 
		
	}
	
	
	
	for(int i = N-1; i >= 0; --i){
		if(par[i] == ')'){
			for(int j = i+1; j < N; ++j){
				if(par[j] != '('){
					par[++i] = par[j];
					par[j] = ' ';
				}
				else par[j] = ' ';
			}
			break;
		}
	}
//	for(int i = 0; i < N; ++i) printf("%c ", par[i]);
//	printf("\n");
	
	if(N <= 2){
		printf("1\n");
		return 0;
	}
	
	for(int i = 0; i < N; ++i){
		if(par[i] == '(') left++;
		else if(par[i] == ')'){
			if(left > 0) left--;
			else right++;
		}
	}
//	printf("L=%d,R=%d\n",left,right);
	take(par, 0, left, right);
	if(ans == 0) ans = 1;
	printf("%d\n", ans);
		

	
	
	
	return 0;
}
