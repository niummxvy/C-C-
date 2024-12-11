#include <stdio.h>
#include <string.h>

int main(void){
	char input[10000] = {};
	while(scanf("%s", input) != EOF){
		long long sum = 0;
 		for(int i = 0; i < strlen(input); ++i){
 			int nega = 0;
 			int num = 0;
			if(input[i] >= '0' && input[i] <= '9'){
				if(input[i-1] == '-') nega = 1;
				for(i; i < strlen(input); ++i){
					num = num * 10 + input[i] - '0';
					if(input[i+1] < '0' || input[i+1] > '9') break;
				}
				if(nega == 1) num *= -1;
				sum += num;
			}
		}
		printf("%lld\n", sum);
	}
	return 0;
}
