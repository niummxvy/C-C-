#include <stdio.h>
#include <string.h>
#define LEN_FORMULA 200
#define LEN_DIGIT 20


typedef struct digit{
		int a;
		int b;
		int dig;
}Digit;


int i = 0, nega = 0, dec = 0, inc = 0;


int InPri(char op){
	if(op == '(') return 1;
	else if(op == '*' || op == '/') return 3;
	else if(op == '+' || op == '-') return 2;
	else return 0;
}

int OutPri(char op){
	if(op == '(') return 3;
	else if(op == '*' || op == '/') return 2;
	else if(op == '+' || op == '-') return 1;
	else return 0;
}

void trim(char *postfix){
	int j = 0, k, m, n = 0, p;
	for(j; j < i; ++j) if(postfix[j] == 0) break;
	p = j;
	for(k = j; k < i; ++k) if(postfix[k] != 0) break;
	m = i-k;
//	printf("m: %d\n", m);
//	printf("%s\n", postfix);
	while(n < m){
		postfix[j++] = postfix[k++];
//		printf("%c", postfix[j]);
		n++;
	}
	n = 0;
	while(n <= m){
//		printf("%d %d %d\n", p, m, n);
		postfix[p+m+n] = 0;
		n++;
	}
//	printf("\n");
}

void fill(char *c, char *postfix, int term){
	int nonzero = 0;
	while(c[nonzero] == '0') nonzero++;
//	for(int k = nonzero; k < LEN_DIGIT; ++k) printf("%c", c[k]);
//	printf("\n");
	while(nonzero < LEN_DIGIT) postfix[term++] = c[nonzero++];
	postfix[term] = '|';
	i++;
}

void In2Post(char *infix, char *postfix, char *stack){
	int in = 0, post = 0, sign = 0;
	while(in < i){
		if(infix[in] == '('){
			dec++;
			stack[sign++] = infix[in++];
		}
		else if(infix[in] == ')'){
			dec++;
			for(sign = sign-1; sign >= 0; --sign){
				if(stack[sign] == '('){
					stack[sign] = 0;
					break;
				}
				postfix[post++] = stack[sign]; // if(')'), pop out directly until '('
				stack[sign] = 0;
			}
			in++;
		}
		else if(infix[in] == '+'){
			if( InPri( infix[in] ) > InPri( stack[sign-1] ) ){ // if('+') is superior to the top of stack, push in
				stack[sign++] = infix[in++];
			}else{
				while( InPri( infix[in] ) <= InPri( stack[sign-1] ) ){ // else, pop out directly until ('+') is superior to the top of stack
					postfix[post++] = stack[--sign];
					stack[sign] = 0;
				}
				stack[sign++] = infix[in++];
			}
		}
		else if(infix[in] == '-'){
			if( InPri( infix[in] ) > InPri( stack[sign-1] ) ){ // if('-') is superior to the top of stack, push in
				stack[sign++] = infix[in++];
			}else{
				while( InPri( infix[in] ) <= InPri( stack[sign-1] ) ){ // else, pop out directly until ('-') is superior to the top of stack
					postfix[post++] = stack[--sign];
					stack[sign] = 0;
				}
				stack[sign++] = infix[in++];
			}
		}
		else if(infix[in] == '*'){
			if( InPri( infix[in] ) > InPri( stack[sign-1] ) ){ // if('*') is superior to the top of stack, push in
				stack[sign++] = infix[in++];
			}else{
				while( InPri( infix[in] ) <= InPri( stack[sign-1] ) ){ // else, pop out directly until ('*') is superior to the top of stack
					postfix[post++] = stack[--sign];
					stack[sign] = 0;
				}
				stack[sign++] = infix[in++];
			}
		}
		else if(infix[in] == '/'){
			if( InPri( infix[in] ) > InPri( stack[sign-1] ) ){ // if('/') is superior to the top of stack, push in
				stack[sign++] = infix[in++];
			}else{
				while( InPri( infix[in] ) <= InPri( stack[sign-1] ) ){ // else, pop out directly until ('/') is superior to the top of stack
					postfix[post++] = stack[--sign];
					stack[sign] = 0;
				}
				stack[sign++] = infix[in++];
			}
		}
		else if(infix[in] >= '0' && infix[in] <= '9'){ // if it's int, push in directly
			postfix[post++] = infix[in++];
		}
		else if(infix[in] = ' ') in++;
		
		if( ( postfix[post-1] >= '0' && postfix[post-1] <= '9' ) && (infix[in] < '0' || infix[in] > '9')){
			postfix[post++] = '|'; // separate int from int or sign by '|'
			i++;
		}
	}
	
	i -= dec;
	
	if(stack[sign-1] != 0){ // if the first sign is not '(' (&& the last sign is not ')')
		while(sign >= 0){
			postfix[post++] = stack[--sign];
			stack[sign] = 0;
		}
	}
}


Digit store(char *postfix, char *a, char *b, int term){
	Digit digit;
	digit.a = LEN_DIGIT-1;
	digit.b = LEN_DIGIT-1;
	int spacer = 0;
	postfix[term] = 0;
	for(int k = term-1; k >= 0; --k){
		if(postfix[k] == '|'){
			spacer++;
			postfix[k] = 0;
			if(spacer == 3){
				postfix[k] = '|';
				digit.dig = k+1;
//				printf("store: %s\n", postfix);
				return digit;
			}
		}
		else{
			if(spacer == 1){
				b[digit.b--] = postfix[k]; // pop out
				postfix[k] = 0; // pop out
			}
			else if(spacer == 2){
				a[digit.a--] = postfix[k]; // pop out
				postfix[k] = 0; // pop out
			}
		}
		digit.dig = k;
	}
//	printf("spacer: %d\n", spacer);
//	printf("a: %s\n", a);
//	printf("b: %s\n", b);
	
	return digit;
}


void add(char *a, char *b, char *c){
	
}
/*
void min(char *a, char *b, char *c){
	int[LEN_DIGIT] = {};
	for(int col = LEN_DIGIT-1; col >= 0; ++col){
		
	}
}
*/
void mul(char *a, char *b, char *c, Digit digit){
	int temp[LEN_DIGIT-digit.b][LEN_DIGIT] = {};
	int space = 0;
	for(int row = 0; row < LEN_DIGIT-digit.b; ++row){ // row
		for(int col = LEN_DIGIT-1; col > digit.a; --col){ // column
			temp[row][col-space] = (a[col] - '0') * (b[LEN_DIGIT-1-row] - '0');
		}
		space++;
	}
/*	for(int j = 0; j < LEN_DIGIT-1-digit.b; ++j){
		for(int k = 0; k < LEN_DIGIT; ++k){
			printf("%d ", temp[j][k]);
		}
		printf("\n");
	} */
	for(int col = LEN_DIGIT-1; col >= 0; --col){
		int carry = 0, unit = 0;
		for(int row = 0; row < LEN_DIGIT-1-digit.b; ++row){
			carry += temp[row][col] / 10;
			unit += temp[row][col] % 10;
			if(unit >= 10){
				carry++;
				unit -= 10;
			}
		}
//		printf("A: %d %d\n", carry, unit);
		if((int)c[col] + unit >= 58){
			c[col-1] = ((int)c[col-1] + 1);
			unit -= 10;
		}
		c[col] = ((int)c[col] + unit);
		if(col > 0) c[col-1] = ((int)c[col-1] + carry);
//		printf("B: %c %c\n", c[col-1], c[col]);
	}
//	for(int j = 0; j < LEN_DIGIT; ++j) printf("%c", c[j]);
//	printf("\n");
}

void div(char *a, char *b, char *c, Digit digit){
	int A = 0, B = 0;
	int nonzero_a = 0, nonzero_b = 0;
	while(b[nonzero_b] == '0') nonzero_b++;
	while(a[nonzero_a] == '0') nonzero_a++;
	
//	for(int k = 0; k < LEN_DIGIT; ++k) printf("%c", b[k]);
//	printf("\n");
	while(nonzero_b < LEN_DIGIT){
		B = B*10 + (b[nonzero_b++] - '0');
	}
	
	for(int col = 0; col < LEN_DIGIT; ++col){
		int temp_a = nonzero_a;
		for(int j = 0; j < LEN_DIGIT; ++j){
			if(A >= B) break;
			A = A*10 + (a[temp_a++] - '0');
		}
//		printf("A:B = %d %d\n", A, B);
	}
}


void cal(char *postfix, char *a, char *b, char *c){ // a, b, c : first, second, sum
	int post = 0;
	Digit digit;
	while(post < i){
//		printf("post: %d\n", post);
		if(postfix[post] == '+'){
			digit = store(postfix, a, b, post);
/*			add(a, b, c, digit);
			fill(c, postfix, digit.dig);
//			for(int x = 0; x < i; ++x) printf("%c", postfix[x]);
//			printf("\n");
			trim(postfix);
//			for(int x = 0; x < i; ++x) printf("%c", postfix[x]);
//			printf("\n");
			memset(a, '0', LEN_DIGIT);
			memset(b, '0', LEN_DIGIT);
			memset(c, '0', LEN_DIGIT);
			post = 0; */
		}
		else if(postfix[post] == '-'){
/*			digit = store(postfix, a, b, post);
//			min(a, b, c, digit);
			fill(c, postfix, digit.dig);
//			for(int x = 0; x < i; ++x) printf("%c", postfix[x]);
//			printf("\n");
			trim(postfix);
//			for(int x = 0; x < i; ++x) printf("%c", postfix[x]);
//			printf("\n");
			memset(a, '0', LEN_DIGIT);
			memset(b, '0', LEN_DIGIT);
			memset(c, '0', LEN_DIGIT);
			post = 0; */
		}
		else if(postfix[post] == '*'){
			digit = store(postfix, a, b, post);
			mul(a, b, c, digit);
			fill(c, postfix, digit.dig);
//			for(int x = 0; x < i; ++x) printf("%c", postfix[x]);
//			printf("\n");
			trim(postfix);
//			for(int x = 0; x < i; ++x) printf("%c", postfix[x]);
//			printf("\n");
			memset(a, '0', LEN_DIGIT);
			memset(b, '0', LEN_DIGIT);
			memset(c, '0', LEN_DIGIT);
			post = 0;
		}
		else if(postfix[post] == '/'){
			digit = store(postfix, a, b, post);
			div(a, b, c, digit);
			fill(c, postfix, digit.dig);
//			for(int x = 0; x < i; ++x) printf("%c", postfix[x]);
//			printf("\n");
			trim(postfix);
//			for(int x = 0; x < i; ++x) printf("%c", postfix[x]);
//			printf("\n");
			memset(a, '0', LEN_DIGIT);
			memset(b, '0', LEN_DIGIT);
			memset(c, '0', LEN_DIGIT);
			post = 0;
		}
		else if(postfix[post] == 0) break;
/*		else if(postfix[post] >= '0' && postfix[post] <= '9'){
			
		} */
		post++;
	}
}


int main(){
	char infix[LEN_FORMULA] = {}, postfix[LEN_FORMULA], sum[LEN_DIGIT], first[LEN_DIGIT], second[LEN_DIGIT], stack[200] = {};
	memset(postfix, '.', LEN_DIGIT);
	memset(first, '0', LEN_DIGIT);
	memset(second, '0', LEN_DIGIT);
	memset(sum, '0', LEN_DIGIT);
	int j = 0;
	for(i; i < LEN_FORMULA; ++i){
		scanf("%c", &infix[i]);
		if(infix[i] == '\n') break;
		if(infix[i] == ' ') i--;
	}
	printf("i: %d\n", i);
	In2Post(infix, postfix, stack);
	printf("i: %d\n", i);
	printf("%s\n", postfix);
	cal(postfix, first, second, sum);
	printf("%s\n", postfix);
	
	
	
	return 0;
} 
