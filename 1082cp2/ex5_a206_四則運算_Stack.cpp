#include <stdio.h>
#include <string.h>
#include <limits.h>
#define LEN_FORMULA 200
#define LEN_DIGIT 100


int i = 0, dec = 0, inc = 0, Num[LEN_DIGIT] = {};
int top_num = 0, top_op = 0;
char Op[LEN_DIGIT] = {};


void push_num(int *Stack, int a){
	Stack[top_num++] = a;
}

void push_op(char *stack, char a){
	stack[top_op++] = a;
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
	if(op == '(') return 1;
	else if(op == '*' || op == '/') return 3;
	else if(op == '+' || op == '-') return 2;
	else return 0;
}

int cal(int a, int b, char op){ // a, b: first, second
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
			return 0;
		}
}

void In2Post(char *infix){
	int in = 0, post = 0, sign = 0, num = 0;
	while(in < i){
		if(infix[in] == '('){
			push_op(Op, infix[in]);
			in++;
		}
		else if(infix[in] == ')'){
			while(1){
				if(Top_op(Op) == '('){
					pop_op();
					break;
				}
				if(top_num > 1){
					Num[top_num-2] = cal(Num[top_num-2], Num[top_num-1], Top_op(Op));
					pop_num();
					pop_op();
				}
			}
			in++;
		}
		else if(infix[in] == '+'){
			if( InPri( infix[in] ) > InPri( Top_op(Op) )){ // if('+') is superior to the top of stack, push in
				push_op(Op, infix[in]);
				in++;
			}
			else{
				while( InPri( infix[in] ) <= InPri( Top_op(Op) ) ){ // else, pop out directly until ('+') is superior to the top of stack
					if(top_num > 1){
						Num[top_num-2] = cal(Num[top_num-2], Num[top_num-1], Top_op(Op));
						pop_num();
						pop_op();
					}
				}
				push_op(Op, infix[in]);
				in++;
			}
		}
		else if(infix[in] == '-'){
			if( InPri( infix[in] ) > InPri( Top_op(Op) )){ // if('+') is superior to the top of stack, push in
				push_op(Op, infix[in]);
				in++;
			}
			else{
				while( InPri( infix[in] ) <= InPri( Top_op(Op) ) ){ // else, pop out directly until ('+') is superior to the top of stack
					if(top_num > 1){
						Num[top_num-2] = cal(Num[top_num-2], Num[top_num-1], Top_op(Op));
						pop_num();
						pop_op();
					}
				}
				push_op(Op, infix[in]);
				in++;
			}
		}
		else if(infix[in] == '*'){
			if( InPri( infix[in] ) > InPri( Top_op(Op) )){ // if('+') is superior to the top of stack, push in
				push_op(Op, infix[in]);
				in++;
			}
			else{
				while( InPri( infix[in] ) <= InPri( Top_op(Op) ) ){ // else, pop out directly until ('+') is superior to the top of stack
					if(top_num > 1){
						Num[top_num-2] = cal(Num[top_num-2], Num[top_num-1], Top_op(Op));
						pop_num();
						pop_op();
					}
					
				}
				push_op(Op, infix[in]);
				in++;
			}
		}
		else if(infix[in] == '/'){
			if( InPri( infix[in] ) > InPri( Top_op(Op) )){ // if('+') is superior to the top of stack, push in
				push_op(Op, infix[in]);
				in++;
			}
			else{
				while( InPri( infix[in] ) <= InPri( Top_op(Op) ) ){ // else, pop out directly until ('+') is superior to the top of stack
					if(top_num > 1){
						Num[top_num-2] = cal(Num[top_num-2], Num[top_num-1], Top_op(Op));
						pop_num();
						pop_op();
					}
				}
				push_op(Op, infix[in]);
				in++;
			}
		}
		else if(infix[in] >= '0' && infix[in] <= '9'){ // if it's int, push in directly
			num = num * 10 + (infix[in++] - '0');
			if( in > 0 && (( infix[in-1] >= '0' && infix[in-1] <= '9' ) && (infix[in] < '0' || infix[in] > '9'))){
				push_num(Num, num);
				num = 0;
				i++;
			}
		} 
		else if(infix[in] = ' ') break;	 
	}
	while(top_op != -1){
		Num[top_num-2] = cal(Num[top_num-2], Num[top_num-1], Top_op(Op));
		pop_op();
		pop_num();
	}	
	
}


int main(){
	char infix[LEN_FORMULA] = {}, postfix[LEN_FORMULA], stack[200] = {};
	int sum = 0;
	for(i = 0; i < LEN_FORMULA; ++i){
		scanf("%c", &infix[i]);
		if(infix[i] == '\n') break;
		if(infix[i] == ' ') i--;
	}
	In2Post(infix);
	printf("%d\n", Num[0]);
	
	return 0;
} 
