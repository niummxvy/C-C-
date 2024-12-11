#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SEN 100

int main(){
	char sen[SEN] = {}, per[200][100] = {};
	int i = 0;
	while(scanf("%[a-zA-Z]", sen) != EOF){
		getchar();
		
		int check = 0;
		strcpy(per[i], sen);
		memset(sen, 0, SEN);
		
		for(int j = 0; j < 100; ++j){ // tolower
			if(per[i][j] >= 'A' && per[i][j] <= 'Z') per[i][j] = tolower(per[i][j]);
		}
		
		for(int j = 0; j < i; ++j){ // remove the rpeated word
			if(strcmp(per[i], per[j]) == 0){
				check = 1;
				memset(per[i], 0, 100);
				break;
			}
		}
		
		if(check == 0 && per[i][0] != 0) i++;
		else continue;
	}
//	for(int j = 0; j < i; ++j) printf("%s\n", per[j]);
	for(int j = 1; j < i; ++j){
		for(int k = j; k > 0; --k){
			for(int m = 0; m < SEN; ++m){
				if(per[k-1][m] > per[k][m]){
					char temp[SEN] = {};
					strcpy(temp, per[k]);
//					printf("------%s\n", temp);
					strcpy(per[k], per[k-1]);
					strcpy(per[k-1], temp);
					break;
				}
				else if(per[k-1][m] == per[k][m]) continue;
				else break;	
			}
		}
	}
//	printf("------------------------------\n");
	for(int j = 0; j < i; ++j) printf("%s\n", per[j]);
	
	return 0;
} 
