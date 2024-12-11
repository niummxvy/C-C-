#include <stdio.h>
#include <string.h>
#define SIZE 252

char big[SIZE] = {}, L[SIZE] = {}, H[SIZE] = {}, mid[SIZE] = {}, square[SIZE] = {};


void right_move(char *arr){
	int gap;
/*	for(int i = 0; i < SIZE; ++i){
		if(arr[i] == '_') break;
		printf("big_before[%d]: %c\n", i, arr[i]);
	} */
	
	for(int i = SIZE-2; i >= 0; --i){
		if(arr[i] != '_'){
			gap = SIZE-1-i;
//			printf("gap: %d\n", gap);
			break;
		}
	}
	for(int i = 0; i+gap < SIZE; ++i){
		arr[i+gap] = arr[i];
		arr[i] = '_';
	}
}

void divide_by_2(char *dividend){
	int temp = 0;
	for(int i = 0; i < SIZE-1; ++i) square[i] = '_';
	square[SIZE-1] = 0;
	for(int i = 0; i < SIZE-1; ++i){
		if(dividend[i] != '_'){
			temp = temp*10 + (int)dividend[i] - '0';
			if(temp >= 2){
				for(int j = 1; j <= 10; ++j){
					if(2 * j > temp){
						temp = temp - 2*(j-1);
						mid[i] = (char)(j-1 + '0');
						break;
					}
				}
			}
			else if(temp < 2 && mid[i-1] != '_') mid[i] = '0';
		}
	}
/*	for(int i = SIZE-1; i >= 0; --i) {
		if(mid[i] == '_') break;
//		printf("mid[%d]: %c\n", i, mid[i]);
	} */
//	printf("%s\n", mid);
}

void find_mid(char *a, char *b){
	char c[SIZE] = {};
	for(int i = 0; i < SIZE-1; ++i) c[i] = '_';
	c[SIZE-1] = 0;
	for(int i = SIZE-2; i >= 0; --i){
		if(a[i] == '_' && b[i] == '_') break;
		if(c[i] == '_') c[i] = '0';
		if(a[i] == '_' || b[i] == '_') c[i] = c[i] + a[i] + b[i] - '0' - '_';
		else{
			if((int)a[i]-'0' + (int)b[i]-'0' > 9){
				c[i-1] = '0';
				c[i] = c[i] + (a[i]-'0' + b[i]-'0') % 10;
				int tmp = (int)a[i]-'0' + (int)b[i]-'0';
				while(tmp > 9){
					c[i-1] = c[i-1] + 1;
					tmp -= 10;
				}
				
			}
			else c[i] = c[i] + a[i]-'0' + b[i]-'0';
		}
		
	}
//	printf("c: %s\n", c);
	divide_by_2(c);
}

void mul(char *a, char *b, int digit_b){
	int temp[digit_b][SIZE-1];
	memset(temp, 0, sizeof(temp));
	int space = 0;
	for(int i = 0; i < SIZE-1; ++i) square[i] = '_';
	square[SIZE-1] = 0;
	for(int row = 0; row < digit_b; ++row){ // row
		for(int col = SIZE-2; col > SIZE-2-digit_b; --col){ // column
			temp[row][col-space] = (a[col] - '0') * (b[SIZE-2-row] - '0');
		}
		space++;
	}
/*	for(int i = 0; i < digit_b; ++i){
		for(int j = 0; j < SIZE-1; ++j){
			printf("%d", temp[i][j]);
		}
		printf("\n");
	}  */
	square[SIZE-2] = '0';
	for(int col = SIZE-2; col > SIZE-2-3*digit_b; --col){
		int carry = 0, unit = 0;
		for(int row = 0; row < digit_b; ++row){
			carry += temp[row][col] / 10;
			unit += temp[row][col] % 10;
			if(unit >= 10){
				carry++;
				unit -= 10;
			}
		}
		if(carry == 0 && unit == 0 && square[col-1] == '0') break;
		if(square[col-1] == '_') square[col-1] = '0';
		while(square[col] + unit > '9'){
			square[col-1] = square[col-1] + 1;
			unit -= 10;
		}
		square[col] = square[col] + unit;
		if(col > 0){
//			int add = 0;
//			printf("carry: %d\n", carry);
			square[col-1] = ((int)square[col-1] + carry);
			
/*			while(carry != 0){
				if(square[col-1-add] + 1 > '9') ++add;
				if(square[col-1-add] == '_') square[col-1-add] = '0';
				square[col-1-add] = square[col-1-add] + 1;
				printf("square[%d]: %c\n", col-1-add, square[col-1-add]);
				--carry;
			} */
		}
//		printf("square[%d]: %c\n", col, square[col]);
	}
	
	for(int i = SIZE-2-3*digit_b; i < SIZE; ++i){
		if(square[i] != '0') break;
		square[i] = '_';
	}
/*	for(int i = SIZE-2-3*digit_b; i < SIZE-2; ++i){
		if(square[i] == '_' && square[i+1] != '_'){
			square[i] = square[i+1];
			square[i+1] = '_';
		}
	} */
	for(int i = SIZE-2; i >= 0; --i){
		if(square[i] != '_') break;
		square[i] = 0;
//		printf("square[%d] == '_'\n", i);
	} 
//	square[SIZE-1] = '\0'; 
//	printf("%s\n", square);
}

int main(){
	int count = 0, lower_digit, upper_digit, digit_mid = 0, digit_square = 0;
	for(int i = 0; i < SIZE; ++i){
		big[i] = '_';
		L[i] = '_';
		H[i] = '_';
		mid[i] = '_';
		square[i] = '_';
		if(i == SIZE-1){
			big[i] = 0;
			L[i] = 0;
			H[i] = 0;
			mid[i] = 0;
			square[i] = 0;
		}
	}
	scanf("%s", big);
	for(int i = 0; i < SIZE; ++i){
		if(big[i] == '_') break;
		++count;
	}
	count -= 2; // big: 10^count
	lower_digit = count/2;
	upper_digit = count/2 + 1;
	right_move(big);
	
	for(int i = SIZE-1; i >= 0; --i){
		if(big[i] == '_') break;
//		printf("big[%d]: %c\n", i, big[i]);
	} 
	
	
	for(int i = SIZE-2; i >= SIZE-2-lower_digit; --i){
		if(i == SIZE-2-lower_digit){
			L[i] = '1';
			break;
		}
		L[i] = '0';
	}
	for(int i = SIZE-2; i >= SIZE-2-upper_digit; --i){
		if(i == SIZE-2-upper_digit){
			H[i] = '1';
			break;
		}
		H[i] = '0';
	}
//	printf("%s\n%s\n%s\n", big, L, H);
	find_mid(L, H);

	for(int i = SIZE-2; i >= 0; --i){
		if(mid[i] == '_') break;
		++digit_mid;
	}
//	printf("%d\n", digit_mid);
	mul(mid, mid, digit_mid);
	for(int i = SIZE-2; i >= 0; --i){
		if(square[i] == '_') break;
		++digit_square;
	}
	digit_square -= 1; 
	while(strcmp(square, big) != 0){
//		printf("%d %d\n", count, digit_square);
		if(count > digit_square) strcpy(L, mid);
		else if(count < digit_square) strcpy(H, mid);
		else{
			for(int i = SIZE-(count+2); i < SIZE; ++i){
//				printf("i: %d\n", i);
				if(big[i] > square[i]){
					strcpy(L, mid);
//					printf("need bigger: %d // big[%d]: %c // square[%d]: %c\n", i, i, big[i], i, square[i]);
					break;
				}
				else if(big[i] < square[i]){
					strcpy(H, mid);
//					printf("need smaller: %d // big[%d]: %c // square[%d]: %c\n", i, i, big[i], i, square[i]);
					break;
				}
/*				if(i == SIZE-1){
					printf("AAA\n");
					for(int j = SIZE-digit_mid; j < SIZE; ++j){
						printf("%c", mid[j]);
					}
					printf("\n");
					return 0;
				} */
			}
		}
//		printf("L: %s\nH: %s\n", L, H);
		find_mid(L, H);
		digit_mid = 0;
		digit_square = 0;
		for(int i = SIZE-2; i >= 0; --i){
			if(mid[i] == '_') break;
			++digit_mid;
		}
		mul(mid, mid, digit_mid);
		for(int i = SIZE-2; i >= 0; --i){
			if(square[i] == '_') break;
			++digit_square;
		}
		digit_square -= 1;
//		printf("\n");
	}
	for(int j = SIZE-digit_mid-1; j < SIZE; ++j){
		printf("%c", mid[j]);
	}
	printf("\n");
	
	return 0;
}
