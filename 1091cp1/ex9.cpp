#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define min(a,b) ((a) < (b) ? (a) : (b))
#define SIZE 50

int ctoi(char c){
	return c - 'a';
}

void str_bubble(char arr1[SIZE], char arr2[SIZE]){
	char temp[SIZE] = {};
	strcpy(temp, arr1);
	memset(arr1, 0, SIZE);
	strcpy(arr1, arr2);
	memset(arr2, 0, SIZE);
	strcpy(arr2, temp);
}

int main(){
	char input[SIZE*400] = {}, dict[26][SIZE*40][SIZE] = {}; // [a~z][the ith order in each dict][the jth character of each word]
	int times[26][SIZE*40] = {};
	while(fgets(input, SIZE*400, stdin)){
		char list[SIZE*40][SIZE] = {};
		int word_count = 0;

		for(int i = 0; i < SIZE*400; ++i){
			if(input[i] >= 'A' && input[i] <= 'Z') input[i] = tolower(input[i]);
			if(input[i] == '\n'){
				input[i] = 0;
				break;
			}
		}
		char * pch = NULL;
		pch = strtok(input,"~`!@#$%^&*()-_=+[{}]\\|;:\'\",<.>/? 1234567890");
		while (pch != NULL){
			strcpy(list[word_count++], pch);
			
			pch = strtok (NULL, "~`!@#$%^&*()-_=+[{}]\\|;:\'\",<.>/? 1234567890");
		}

		for(int i = 0; i < SIZE*40; ++i){
			for(int j = 0; j < SIZE*40; ++j){
				if(strcmp(dict[ctoi(list[i][0])][j], list[i]) == 0){ // repeat
					++times[ctoi(list[i][0])][j];
					break;
				}
				if(dict[ctoi(list[i][0])][j][0] == 0){ // no repeat
					strcpy(dict[ctoi(list[i][0])][j], list[i]);
					times[ctoi(list[i][0])][j] = 1;
					break;
				}
			}
		}

		for(int i = 0; i < 26; ++i){ // traverse array 'a' ~ 'z'
			for(int j = 0; j < SIZE*40; ++j){ // traverse first word
				if(dict[i][j][0] == 0) break;
				for(int k = j+1; k < SIZE*40; ++k){ // traverse second word
					if(dict[i][k][0] == 0) break;
					for(int m = 0; m < min( strlen(dict[i][j]), strlen(dict[i][k]) ); ++m){
						if(dict[i][j][m] < dict[i][k][m]) break;
						else if(dict[i][j][m] > dict[i][k][m]){
							str_bubble(dict[i][j], dict[i][k]);

							int temp = times[ctoi(dict[i][j][0])][j]; 
							times[ctoi(dict[i][j][0])][j] = times[ctoi(dict[i][k][0])][k];
							times[ctoi(dict[i][k][0])][k] = temp;
							break;
						}
					}

					if(strlen(dict[i][j]) > strlen(dict[i][k])){ // (e.g.)"computer","compute"
						int same = 1;
						for(int m = 1; m < strlen(dict[i][k]); ++m){
							if(dict[i][j][m] != dict[i][k][m]) same = 0;
						}
						if(same == 1){
							str_bubble(dict[i][j], dict[i][k]);
							int temp = times[ctoi(dict[i][j][0])][j]; 
							times[ctoi(dict[i][j][0])][j] = times[ctoi(dict[i][k][0])][k];
							times[ctoi(dict[i][k][0])][k] = temp;
						}
					}
				}
			}
		}
	}

	for(int i = 0; i < 26; ++i){
		for(int j = 0; j < SIZE*40; ++j){
			if(dict[i][j][0] == 0) break;
			for(int k = 0; k < SIZE; ++k){ // k < SIZE
				if(dict[i][j][k] == 0) break;
				printf("%c", dict[i][j][k]);
			}
			if(times[i][j] != 0) printf(" %d\n", times[i][j]);
		}
	}
	return 0;
}

/*
I have a pen. I have an apple.
Uhh!! Apple-pen.

I have a pen. I have a pineapple.
Uhh!! Pineapple-pen.

Apple-pen. Pineapple-pen.
Uhh!! Pen pineapple apple pen.
*/


/*
acb abc acc acb bca bac bcc bca cba cab ccc cba
*/
