#include <stdio.h>
#include <string.h>
#define LEN 1005


int main(){
	char num1[LEN] = {}, num2[LEN] = {}, temp[LEN] = {}, str[LEN*2], sum[LEN] = {};
	int cnt = 0;
	scanf("%s", str);
	for(int i = 0; i < sizeof(str); ++i){
		if(str[i] == '\0') break;
//		printf("%c", str[i]);
		if(str[i] == '+'){
			strcpy(num1, temp);
			memset(temp, 0, sizeof(temp));
			cnt = 0;	
		}
		else temp[cnt++] = str[i];
	}
	strcpy(num2, temp);
//	printf("%s+%s\n", num1, num2);

	for(int i = 1; i < LEN; ++i){
		sum[i-1] = num1[i-1] + num2[i-1] - '0';
		while(sum[i-1] > '9'){
			++sum[i];
			sum[i-1] -= 10;
		}
	}
	int start;
	for(int i = LEN-1; i >= 0; --i){
		if(sum[i] != '0') 
	}
	return 0;
} 

// 9999999+10000000001
