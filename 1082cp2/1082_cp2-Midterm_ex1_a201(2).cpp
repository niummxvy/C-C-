#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void * a, const void * b){
	if(*(int*)a <= *(int*)b) return 0;
	else return 1;
}

int main(void) {
 
	int n = 0;
	
	
	// get the first number and \n
	scanf("%d\n", &n);
	
	for(int i=0;i<n;i++) {
		char str[1000] = {'\0'};
		char s[2] = " ";
		char *token, store[101] = {}, nega[101] = {};
		int j = 0, sign[101], num[101] = {}, count = 0;
		for(int k = 0; k < 101; ++k){
			sign[k] = 1;
		}
	  	fgets(str, 1000, stdin);
	
	  	// remove the \n or \r
	  	for(int i=0;i<strlen(str);i++){
	   		str[i] = (str[i] >= 32 && str[i]<= 126) ? str[i] : '\0';
	  	}
	
	  	token = strtok(str, s);
	  	store[0] = *token;
//	  	printf("store: %d\n", store[0]);
	  	// walk through other tokens
	    while(token != NULL) {
			if(*token == '-'){ // negative integers
				count++;
//				nega[j] = *token;
				sign[j] = -1; 
//				printf("%c", store[j]);
				token++;
				while(*token != NULL){
					num[j] = num[j] * 10 + (*token - '0');
//					printf("%d, ", num[j]);
					*token++;
				}
//				printf("%d ", num[j]);
				++j;
//				++j;
//				num[j] = *token - 0;
//				printf("%d ", num[j]);
//				++j;
			}else if((int)*token >= 48 && (int)*token <= 57){ // positive integers
				count++;
				while(*token != NULL){
					num[j] = num[j] * 10 + (*token - '0');
//					printf("%d, ", num[j]);
					*token++;
				}
//					num[j] = *token - '0';
//					printf("%d ", num[j]);
				++j;
			}
			else if((int)*token >= 97 && (int)*token <= 122){ // alphabets
				count++;
				store[j] = *token;
//				printf("%c ", store[j]);
				++j;
			}
			else{
				count++;
				store[j] = *token;
				++j;
			}
//	       	printf("%s ", token);
	       	token = strtok(NULL, s);
	    }
//	    puts("");
	    if(((int)store[0] >= 48 && (int)store[0] <= 57) || (int)store[0] == 45){ // integers
//	    	printf("trans: ");
	    	for(int k = 0; k < count; ++k){
//	    		num[k] = (int)store[k] - 48;
	    		num[k] *= sign[k];
//	    		printf("%d ", num[k]);
			}
//			printf("\n"); 
			qsort(num, count, sizeof(int), cmp);
			for(int k = 0; k < count; ++k){
	    		printf("%d ", num[k]);
			}
			printf("\n");
		}
		else if((int)store[0] >= 97 && (int)store[0] <= 122){ // alphabets
//			printf("trans: ");
			for(int k = 0; k < count; ++k){
				num[k] = (int)store[k] - 97;
//				printf("%d ", num[k]);
			}
//			printf("\n");
			qsort(num, count, sizeof(int), cmp);
			for(int k = 0; k < count; ++k){
				num[k] += 97;
				printf("%c ", (char)num[k]);
			}
			printf("\n");
		}
		else{
			for(int k = 0; k < count; ++k){
				num[k] = (int)store[k];
//				printf("%d ", num[k]);
			}
//			printf("\n");
			qsort(num, count, sizeof(int), cmp);
			for(int k = 0; k < count; ++k){
				printf("%c ", (char)num[k]);
			}
			printf("\n");
		}
		

	 }

 	return 0; 
}
