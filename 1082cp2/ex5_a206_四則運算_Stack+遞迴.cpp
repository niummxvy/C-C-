#include <stdio.h>
#include <string.h>
#define LEN_FORMULA 200
#define LEN_DIGIT 100

int i = 0, top_num = 0, top_op = 0, op_size = 0, check = 0;
int Num[LEN_DIGIT] = {};
char Op[LEN_DIGIT] = {};

void push_num(int *Stack, int a){
	Stack[top_num++] = a;
}

void push_op(char *stack, char a){
	stack[top_op++] = a;
	op_size++;
}

void pop_num(){
	top_num--;
}

void pop_op(){
	top_op--;
}

int Top_num(int *Stack){
	return Stack[top_num-1];
}

char Top_op(char *stack){
	return stack[top_op-1];
}

int InPri(char op){
	if(op == '(') return 2;
	else if(op == ')') return 3;
	else if(op == '*' || op == '/') return 1;
	else if(op == '+' || op == '-') return 0;
	else return -1;
}

void store(char *infix){
	int num = 0, nega = 0;
//	printf("%d %d\n", i, strlen(infix));
	for(int j = 0; j < strlen(infix)-1; ++j){
//		if(infix[j] == 0) break;
		if(infix[j] >= '0' && infix[j] <= '9'){
			num = num*10 + (infix[j] - '0');
		}else{
			if(infix[j] == '-' && infix[j-1] == '('){
				nega = 1;
				continue;
			}
			if(nega == 1){
				push_num(Num, -num);
				nega = 0;
			}else push_num(Num, num);
			num = 0;
			push_op(Op, infix[j]);
		}
	}
	push_num(Num, num);
	
}

int oper(int b, int a, char op){
	printf("b: %d a: %d, op: %c\n", b, a, op);
	switch(op){
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			return a/b;
		default:
			return a;
	}
}

int cal(){
	int num1 = 0, num2 = 0;
	char op;
	num1 = Top_num(Num);
	pop_num();
	num2 = Top_num(Num);
	pop_num();
	op = Top_op(Op);
	pop_op();
	while(top_op > 0){
		if(InPri(op) == 3){
			push_num(Num, num2);
			num1 = cal();
			if(top_op > 0){
				num2 = Top_num(Num);
				pop_num();
				op = Top_op(Op);
				pop_op();
				if(top_op == 0){
//					printf("AAA\n");
					return oper(num1, num2, op);
				}
				
			}else{
				return num1;
				break;
			}
		}
		if(InPri(Top_op(Op)) == 3){
			pop_op();
			num2 = cal();
			if(top_op == 0){
//				printf("BBB\n");
				return oper(num1, num2, op);
			}		
		}
		if(InPri(op) == 2){
			return num1;
		}
		if(InPri(Top_op(Op)) == 2){
			pop_op();
			pop_num();
//			printf("CCC\n");
			return oper(num1, num2, op);
		}
		if( InPri(op) > InPri(Top_op(Op)) ){
			num1 = oper(num1, num2, op);
			if(check == 1) return num1;
			op = Top_op(Op);
			pop_op();
			num2 = Top_num(Num);
			pop_num();
		}else{
			if(InPri(Op[top_op-2]) > InPri(Top_op(Op))){
				check = 1;
				push_num(Num, num2);
				num2 = cal();
				check = 0;
				num1 = oper(num1, num2, op);
				op = Top_op(Op);
				pop_op();
				num2 = Top_num(Num);
				pop_num();
//				printf("%d %d %d\n", num3, num2, num1);
				if(top_op == -1) return num1;
			}
//			printf("DDD\n");
			else{
				
				num2 = oper(num2, Top_num(Num), Top_op(Op));
				op_size--;
				pop_op();
				pop_num();
			}
		}
		printf("num1: %d num2: %d\n", num1, num2);
	}
//	printf("EEE\n");
	
	return oper(num1, num2, op);
}

int main(){
	char infix[LEN_FORMULA] = {};
	for(i; i < LEN_FORMULA; ++i){
		scanf("%c", &infix[i]);
		if(infix[i] == '\n'){
			i--;
			break;
		}
		if(infix[i] == ' ') i--;
	}
	store(infix);
	if(top_num == 1){
		printf("%d\n", Num[0]);
		return 0;
	}
	for(int j = 0; j < top_num; ++j) printf("%d ", Num[j]);
	printf("\n");
	for(int j = 0; j < top_op; ++j) printf("%c ", Op[j]);
	printf("\n"); 
	printf("%d\n", cal());
	return 0;
}
