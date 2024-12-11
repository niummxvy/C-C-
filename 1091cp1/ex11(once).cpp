#include <stdio.h>
#include <string.h>
#define VOC 10001
#define LEN 101
#define min(a,b) ((a) < (b) ? (a) : (b))

void swap(char *s1, char *s2){
	char str[LEN] = {};
	strcpy(str, s1);
	strcpy(s1, s2);
	strcpy(s2, str);
}

int main(){
	char dict[VOC][LEN] = {};
	int voc = 0;
	while(scanf("%s", dict[voc]) != EOF) ++voc;
	
	for(int i = 0; i < voc-1; ++i){
		for(int j = i+1; j <= voc-1; ++j){
			for(int k = 0; k < min(strlen(dict[i]), strlen(dict[j])); ++k){
				if(dict[i][k] < dict[j][k]) break;
				else if(dict[i][k] > dict[j][k]){
					swap(dict[i], dict[j]);
					break;
				}
			}
			if(strlen(dict[i]) > strlen(dict[j])){ // (e.g.)"computer","compute"
				int same = 1;
				for(int m = 0; m < strlen(dict[j]); ++m){
					if(dict[i][m] != dict[j][m]) same = 0;
				}
				if(same == 1) swap(dict[i], dict[j]);
			}
		}
	}
	
//	for(int i = 0; i < voc-1; ++i) printf("[%d]: %s\n", i, dict[i]);
//	printf("\n");
	for(int i = 0; i < voc-1; i += 2){
		if(strcmp(dict[i], dict[i+1]) != 0){
			printf("%s\n", dict[i]);
			break;
		}
	}
	
	return 0;
} 
