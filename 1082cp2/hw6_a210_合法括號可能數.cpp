#include <stdio.h>
// #include <stdlib.h>
#include <string.h>
// #include <math.h>
// #include <time.h>

int ans = 0;
// int ans = 0, N, AC_arr = 0, temp[36] = {}, every[36] = {}, check;
// char par[36] = {}, rec[50][36] = {};

/*
void remove_L(int *arr, int level, int goal, int start){ // only remove '('
//	printf("N: %d\n", N);
/*	printf("level: %d, goal: %d\n", level, goal);
	for(int i = 0; i < N; ++i) printf("%c ", par[i]);
	printf("\n");
	for(int i = 0; i < N; ++i) printf("%d ", arr[i]);
	printf("\n"); 
	if(level == goal){
		int count = 0;
		for(int i = 0; i < N; ++i){
			if(arr[i] == 1 || (par[i] != '(' && par[i] != ')') ) continue; // skip those which have been removed
			if(par[i] == '(') count++;
			else if(par[i] == ')') count--;
			if(count < 0) return;
		}
		
		if(count == 0){ // valid
			char New[36] = {};
			for(int i = 0, j = 0; i < N; ++i){
				if(arr[i] == 1) continue;
				New[j++] = par[i];
			}
//			printf("AC_arr: %d\n", AC_arr);
			if(AC_arr > 0){
				for(int j = 0; j < AC_arr; ++j){
//					for(int k = 0; k < N; ++k) printf("%c", rec[j][k]);
//					printf("\n");
					if(strcmp(rec[j], New) == 0) return; // check whether it's repeated
				}
			}
			
//			printf("New:\n");
//			for(int i = 0; i < strlen(New); ++i) printf("%c ", New[i]);
//			printf("\n");
			
			strcpy(rec[AC_arr++], New);
			ans++;
		}
		return;
	}
	
	
	
	
	
	
	
//	printf("start: %d\n", start);
	for(int i = start; i < N; ++i){ // dicide the i-th elements to be removed
//		printf("i: %d\n", i);
		if(N-start < goal-level) return;
		if(arr[i] == 0){
			arr[i] = 1;
			start = i;
//			for(int j = 0; j < N; ++j){
//				if(arr[j] == 1) printf("%d ", j);
//			}
//			printf("\n");
//			printf("every:\n");
			for(int j = 0, k = 0; j < N; ++j){
				if(arr[j] == 1) continue;
				every[k++] = arr[j];
				check = k;
			}
//			for(int j = 0; j < N; ++j) printf("%d ", every[j]); 
//			printf("\n");

			


			if(memcmp(temp, every, check) == 0){
//				printf("AAA\n");
				
				arr[i] = 0;
				continue;
			}else{
				
				
				for(int j = 0, k = 0; j < N; ++j){
					if(arr[j] == 1) continue;
					temp[k++] = arr[j];
					check = k;
					
				}
				
				
				arr[i] = 0;
			}
			
			printf("temp:\n");
			for(int j = 0; j < check; ++j) printf("%d ", temp[j]);
			printf("\n"); 
			remove_L(arr, level+1, goal, start+1);
			arr[i] = 0;
		}
	}
	return;
}

void remove_R(int *arr, int level, int goal, int start){ // only remove ')'
//	printf("level: %d\n", level);
//	for(int i = 0; i < N; ++i) printf("%d ", arr[i]);
//	printf("\n");
	if(level == goal){
		int count = 0;
		for(int i = 0; i < N; ++i){
			if(arr[i] == 1 || (par[i] != '(' && par[i] != ')') ) continue; // skip those which have been removed
			if(par[i] == '(') count++;
			else count--;			
			if(count < 0) return;
		}
//		printf("count: %d\n", count);
		if(count == 0){ // valid
			char New[36] = {};
			for(int i = 0, j = 0; i < N; ++i){
				if(arr[i] == 1) continue;
				New[j++] = par[i];
			}
//			printf("AC_arr: %d\n", AC_arr);
			if(AC_arr > 0){
				for(int j = 0; j < AC_arr; ++j){
//					for(int k = 0; k < N; ++k) printf("%c", rec[j][k]);
//					printf("\n");
					if(strcmp(rec[j], New) == 0) return; // check whether it's repeated
				}
			}
			
//			printf("New:\n");
//			for(int i = 0; i < strlen(New); ++i) printf("%c ", New[i]);
//			printf("\n");
			
			strcpy(rec[AC_arr++], New);			
			ans++;
	
		}
		return;
	}
	
	
	
	
	
	for(int i = start; i < N; ++i){ // dicide the i-th elements to be removed
		if(N-start < goal) return;
		if(arr[i] == 0){
			arr[i] = 1;
			start = i;
			for(int j = 0, k = 0; j < N; ++j){
				if(arr[j] == 1) continue;
				every[k++] = arr[j];
			}
			if(memcmp(temp, every, N) == 0){
				arr[i] = 0;
				continue;
			}else{
				for(int j = 0, k = 0; j < N; ++j){
					if(arr[j] == 1) continue;
					temp[k++] = arr[j];
				} 
			remove_R(arr, level+1, goal, start+1);
			arr[i] = 0;
			}
		}
	
	return;
}
*/

int isvalid(char *arr){
	int count = 0;
	for(int i = 0; i < strlen(arr); ++i){
		if(arr[i] == '(') count++;
		else if(arr[i] == ')') count--;
		
		if(count < 0) return 0;
	}
	if(count != 0) return 0;
	else return 1;
}

void take(char *arr, int start, int L, int R){
	if(L && R == 0){
		if(isvalid(arr) == 1){
			ans++;
		}
	}
	
	for(int i = 0; i < strlen(arr); ++i){
		if( i != 0 || (i == 0 && arr[i] != arr[i-1]) ){
			char temp[SIZE] = {};
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


int main(){
	
	int Lcheck = 0, diff = 0, left = 0, right = 0, start = 0;
	for(int i = 0; i < 36; ++i){
		scanf("%c", &par[i]);		
		if(par[i] == '\n'){
			N = i;
			break;
		}
		if(par[i] == '(') Lcheck = 1;
		if(Lcheck == 0 && par[i] == ')') i--;
		// remove ')'s before the first '('
		
	}
	for(int i = N-1; i >= 0; --i){
		if(par[i] != ')') N--;  // remove '('s after the last ')'
		else break;
	}
	if(N <= 2){
		printf("1\n");
		return 0;
	}
	
	
	
	
	for(int i = 0; i < N; ++i){
		if(par[i] == '(') left++;
		else if(par[i] == ')') right++;

	}
	diff = abs(left-right);


	if(left > right){
		left -= right;
		right = 0;
		
		/*
		int rm_which_L[36] = {};
		for(int i = 0; i < N; ++i){
			if(par[i] == '(') rm_which_L[i] = 0;
			else rm_which_L[i] = -1; // ')' and other alphabets shouldn't be removed
		}

		remove_L(rm_which_L, 0, diff, 0);
		*/
		
		take(par, 0, left, right);
		if(ans == 0) ans = 1;
		printf("%d\n", ans);

	}
	else if(left < right){
		right -= left;
		left = 0;
		/*
		int rm_which_R[36] = {};
		for(int i = 0; i < N; ++i){
			if(par[i] == ')') rm_which_R[i] = 0;
			else rm_which_R[i] = -1; // '(' and other alphabets shouldn't be removed
		}

		remove_R(rm_which_R, 0, diff, 0);
		*/
		
		take(par, 0, left, right);
		if(ans == 0) ans = 1;
		printf("%d\n", ans);

	}
	else{
		printf("1\n");
	}
	
	return 0;
}
