#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define min(a,b) ((a) < (b) ? (a) : (b))
#define SIZE 100

int ctoi(char c){
	return c - 'a';
}

void str_bubble(char arr1[SIZE], char arr2[SIZE]){
	char temp[SIZE*10] = {};
	strcpy(temp, arr1);
	memset(arr1, 0, SIZE);
	strcpy(arr1, arr2);
	memset(arr2, 0, SIZE);
	strcpy(arr2, temp);
}

int main(){
	char input[SIZE*100] = {}, dict[26][SIZE][SIZE]; // [a~z][the ith order in each dict][the jth character of each word]
	char list[SIZE*10][SIZE*10] = {};
	int word_count = 0;
	scanf("%s", input);
	getchar();
	
	// split string
	char * pch;
	pch = strtok (input,",");
	while (pch != NULL){
		strcpy(list[word_count++], pch);
//		printf("%s\n", list[word_count-1]);
		pch = strtok (NULL, ",");
	}
//	printf("\n");
	
	// put in each(a~z) array
	for(int i = 0; i < word_count; ++i){
		for(int j = 0; j < SIZE; ++j){
			if(dict[ctoi(list[i][0])][j][0] == 0){
				strcpy(dict[ctoi(list[i][0])][j], list[i]);
//				printf("%s\n", dict[ctoi(list[i][0])][j]);
				break;
			}
		}
	}
//	printf("\n");
	
	// sorting each array (dictionary order)
	for(int i = 0; i < 26; ++i){ // traverse array 'a' ~ 'z'
		for(int j = 0; j < word_count; ++j){ // traverse first word
			if(dict[i][j][0] == 0) break;
			for(int k = j+1; k < word_count; ++k){ // traverse second word
				if(dict[i][k][0] == 0) break;
				for(int m = 0; m < min( strlen(dict[i][j]), strlen(dict[i][k]) ); ++m){
					if(dict[i][j][m] < dict[i][k][m]) break;
					else if(dict[i][j][m] > dict[i][k][m]){
						str_bubble(dict[i][j], dict[i][k]);
						break;
					}
				}
				
				if(strlen(dict[i][j]) > strlen(dict[i][k])){ // (e.g.)"computer","compute"
					int same = 1;
					for(int m = 1; m < strlen(dict[i][k]); ++m){
						if(dict[i][j][m] != dict[i][k][m]) same = 0;
					}
					if(same == 1) str_bubble(dict[i][j], dict[i][k]);
				}
			}
		}
	}
	
	// print each array
/*	for(int i = 0; i < 26; ++i){
		printf("\'%c\'\n", i+'a');
		for(int j = 0; j < word_count; ++j){
			for(int k = 0; k < 20; ++k){ // k < SIZE*10
				printf("%c", dict[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	} */
	
	// search
	char target[SIZE*10] = {};
	while(scanf("%s", target) != EOF){
		int diff = 1, order;
		char lead;
		for(int i = 0; i < word_count; ++i){
			if(strcmp(target, dict[ctoi(target[0])][i]) == 0){
				diff = 0;
				order = i+1;
				lead = toupper(target[0]);
				break;
			}
		}
		if(diff == 0) printf("%c %d\n", lead, order);
		else printf("NOT FOUND\n");
	}
	
	return 0;
} 

// apple,welcome,banana,cat,archive,once,australia,co,abc,bat
// a,aa,aaa,aaaaa,aaaa,aaaaaaa,aaaaaa
// abc,acb,bac,bca,cab,cba
