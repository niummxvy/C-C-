#include <stdio.h>
#define LEN_FORMULA 200

int i = 0;

typedef struct value{
	int term;
	double sum;
}Value;

double add_min(char *infix, int m){
	double a = 0, b = 0;
	for(int j = m-1; j >= 0; --j){
		if(infix[j] < '0' || infix[j] > '9') break;
		a = a * 10 + (infix[j] - '0');
	}
	for(int j = m+1; j < i; ++j){
		if(infix[j] < '0' || infix[j] > '9') break;
		b = b * 10 + (infix[j] - '0');
	}
	return (infix[m] == '+')? a+b : a-b;
}


double mul_div(char *infix, int m){
	double a = 0, b = 0;
	for(int j = m-1; j >= 0; --j){
		if(infix[j] < '0' || infix[j] > '9') break;
		a = a * 10 + (infix[j] - '0');
	}
	for(int j = m+1; j < i; ++j){
		if(infix[j] < '0' || infix[j] > '9') break;
		b = b * 10 + (infix[j] - '0');
	}
	return (infix[m] == '*')? a*b : a/b;
}


Value cal(char *infix, Value value){
	int e;
	value.sum = 0;
	for(int j = 0; j < 3; ++j){
		if(j == 0){
			for(int k = value.term; k < i; ++k){
				if(infix[k] == '('){
//					cal(infix, (k+1));
				}
				if(infix[k] == ')'){
					e = k;
					break;
				}
			}
			
//			return;
		}
		else if(j == 1){
			for(int k = value.term; k < i; ++k){				
				if(infix[k] == '*' || infix[k] == '/'){
					printf("k: %d\n", k);
					value.sum += mul_div(infix, k);
					printf("value.sum: %lf\n", value.sum);
				}
			}
		}
		else if(j == 2){
			for(int k = value.term; k < i; ++k){
				if(infix[k] == '+' || infix[k] == '-'){
					printf("k: %d\n", k);
					value.sum += add_min(infix, k);
					printf("value.sum: %lf\n", value.sum);
				}
			}
		}
	}
	return value;
}

int main(){
	char infix[LEN_FORMULA] = {};
	double sum;
	Value value;
	value.term = 0;
	value.sum = 0;
	for(i; i < LEN_FORMULA; ++i){
		scanf("%c", &infix[i]);
		if(infix[i] == '\n') break;
		if(infix[i] == ' ') i--;
	}
	printf("%s", infix);
	value = cal(infix, value);
	printf("%lf\n", value.sum);
	
	return 0;
} 
