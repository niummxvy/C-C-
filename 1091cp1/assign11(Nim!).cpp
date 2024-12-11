#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int find_row(char pos){
	if(pos == '0' || pos == '2' || pos == '5' || pos == '9' || pos == 'E') return 0;
	else if(pos == '1' || pos == '4' || pos == '8' || pos == 'D') return 1;
	else if(pos == '3' || pos == '7' || pos == 'C') return 2;
	else if(pos == '6' || pos == 'B') return 3;
	else if(pos == 'A') return 4;
	else return 5;
}

int find_col(char pos){
	if(pos == '0' || pos == '1' || pos == '3' || pos == '6' || pos == 'A') return 0;
	else if(pos == '2' || pos == '4' || pos == '7' || pos == 'B') return 1;
	else if(pos == '5' || pos == '8' || pos == 'C') return 2;
	else if(pos == '9' || pos == 'D') return 3;
	else if(pos == 'E') return 4;
	else return 5;
}

int cmp(const void * a, const void * b) { return *(char*)a - *(char*)b; }

int main(){
	char stick[6][6] = { {'0', '2', '5', '9', 'E', '*'},
						 {'1', '4', '8', 'D', '*', '*'},
						 {'3', '7', 'C', '*', '*', '*'},
						 {'6', 'B', '*', '*', '*', '*'},
						 {'A', '*', '*', '*', '*', '*'},
						 {'*', '*', '*', '*', '*', '*'} };
	int who = 0; // black is 0, white is 1
	for(int i = 0; i < 5; ++i){ // print initial table
		for(int j = 0; j < (4-i); ++j) printf(" ");
		for(int j = 0; j <= i; ++j){
			if(j == i) printf("%c", stick[i-j][j]);
			else printf("%c ", stick[i-j][j]);
		}
		printf("\n");
	}
	while(true){
		char str[100] = {};
		fgets(str, 100, stdin);
		int len = strlen(str)-1; // exclude '\0'
		if(len > 3){ // at most choose 3
			if(who % 2 == 0) printf("Black makes an invalid move!\n");
			else printf("White makes an invalid move!\n");
			continue;
		}
		
		qsort(str, len, sizeof(char), cmp); // len: don't include '\0'
		
		bool valid = true;
		for(int i = 0; i < len; ++i){
			if(stick[find_row(str[i])][find_col(str[i])] == 'X'){ // choose repeated one
				if(who % 2 == 0) printf("Black makes an invalid move!\n");
				else printf("White makes an invalid move!\n");
				valid = false;
				break;
			}
		}
		if(valid == false) continue;
		
		int row0 = find_row(str[0]), col0 = find_col(str[0]);
		
		for(int i = 1; i < len; ++i){ // whether all are adjacent (check row)
			if(find_row(str[i]) != row0 + i || find_col(str[i]) != col0){
				valid = false;
				break;
			}
		}
		
		if(valid == false){
			for(int i = 1; i < len; ++i){ // whether all are adjacent (check column)
				if(find_col(str[i]) != col0 + i || find_row(str[i]) != row0){
					valid = false;
					break;
				}
				else valid = true;
			}
		}
		
		if(valid == false && row0 - (len - 1) >= 0 && col0 + (len - 1) < 6){
			for(int i = 1; i < len; ++i){ // whether all are adjacent (check downleft)
				if(str[i] != stick[row0-i][col0+i]){
					valid = false;
					break;
				}
				else valid = true;
			}
		}
			
		if(valid == false){
			if(who % 2 == 0) printf("Black makes an invalid move!\n");
			else printf("White makes an invalid move!\n");
			continue;
		}
		
		for(int i = 0; i < len; ++i) stick[find_row(str[i])][find_col(str[i])] = 'X';
		
		bool all_are_X = true;
		for(int i = 0; i < 5; ++i){
			for(int j = 0; j < (4-i); ++j) printf(" ");
			for(int j = 0; j <= i; ++j){
				if(j == i) printf("%c", stick[i-j][j]);
				else printf("%c ", stick[i-j][j]);
				if(stick[i-j][j] != 'X') all_are_X = false;
			}
			printf("\n");
		}
		if(all_are_X == true){
			if(who % 2 == 0) printf("White wins!\n");
			else printf("Black wins!\n");
			break;
		}
		++who;
	}
	return 0;
}




/*
int stick[5][5]
0 2 5 9 E(14)
1 4 8 D(13) -1
3 7 C(12) -1 -1
6 B(11) -1 -1 -1
A(10) -1 -1 -1 -1


invalid move:
1. >3 sticks
2. different line
3. not adjacent(judge: right, down, downleft)
4. continuous invalid

input process: 
(X) 1. A~E: 10~14
2. sort

++who when successfully moving

output process:
0. space preprocess: for(int i = 0; i < 5; ++i) for(int j = 0; j < (4-i); ++j) printf(" ");
1. removed: removed(int) -> X
(X) 2. last row: itoc(int) -> A~E

Q:
1. 只玩一輪? y 
2. 結尾空格? 會抓 
3. input可能亂序? y


extended:
1. input > 1 digit
2. more sticks are removed in one move
3. more rows



檢查有沒有填在重複位置 
*/
