#include <stdio.h>

int i = 0; // short for term

void cal(char formula[500], int term, char total[102]){ // calculate in brackets
	char first_num[102], sec_num[102];
	for(int j = 0; j < 102; ++j){
//		total[j] = '0';
		first_num[j] = '0';
		sec_num[j] = '0';
	}
	while(term < i){
		
		int digit_first = 0, digit_sec = 0;
		if(formula[term] == ')') return;
		else if(formula[term] >= '0' && formula[term] <= '9'){
			for(int j = 101; j >= 0; --j){ // нnзя 
				first_num[j] = total[j];
				total[j] = '0';
				sec_num[j] = '0';
			}
			for(int j = term; j < i; ++j){
				if(formula[j] < '0' || formula[j] > '9') break;
				digit_first++;
			}
			for(int j = 102-digit_first, k = term; j < 102; ++j){
				first_num[j] = formula[k];
				k++;
			}
			term += digit_first;
			printf("first_num: ");
			for(int j = 0; j < 102; ++j){
				printf("%c", first_num[j]);
			}
			printf("\n");
		}
		else if(formula[term] == '+'){
			if(formula[term+1] == '('){
			//	recursive, sec_num
				term++;
				cal(formula, term, total);
			}
			for(int j = term+1; j < i; ++j){
				if(formula[j] < '0' || formula[j] > '9') break;
				digit_sec++;
			}
			for(int j = 102-digit_sec, k = term+1; j < 102; ++j){
				sec_num[j] = formula[k];
				k++;
			}
			term += digit_sec+1;
			printf("sec_num: ");
			for(int j = 0; j < 102; ++j){
				printf("%c", sec_num[j]);
			}
			printf("\n");
			for(int j = 101; j >= 0; --j){
				total[j] += first_num[j] + sec_num[j] - 96;
				if(total[j] > '9'){
					total[j] -= 10;
					total[j-1]++;
				}
				printf("%c", total[j]);
				first_num[j] = total[j];
				total[j] = '0';
				sec_num[j] = '0';
				
			}
			printf("\n");
			
		}
//			total = first_num + sec_num;
//			printf("total: %lld\n", total);
		
	}
}

int main(){
	char formula[500] = {}, sum[102];
	for(i = 0; i < 500; ++i){
		scanf("%c", &formula[i]);
		if(formula[i] == '\n') break;
		if(formula[i] == ' ') i--;
	}
//	for(int j = 0; j < i; ++j) printf("%c", formula[j]);
//	printf("\n");
	for(int j = 0; j < 102; ++j) sum[j] = '0';
	for(int j = 0; j < i; ++j){
		if(formula[j] == '('){
			cal(formula, j+1, sum);
		}
	}
	for(int j = 0; j < 102; ++j){
		printf("%c", sum[j]);
	}
	return 0;
} 
