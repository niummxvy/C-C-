#include <stdio.h>
#include <limits.h>

int divide(long long divisor, char shang[102], char *p, int count, int digit){
	long long dividend = 0;
	int R = 0, a = 0;
	for(int i = 0; i < digit; ++i){ // find the first nonzero digit
		if(p[i] == 0) a++;
		else break;
	}
	for(int i = 0; i < digit - a; ++i){ // left move
		p[i] = p[i+a];
	}
	for(int i = 0; i < digit - a; ++i){ // calculate the division of every digit
		dividend += p[i] - '0';
		if(dividend < divisor){
			dividend *= 10;
			shang[i] = 0;
		}else{
			int shang_count = 0;
			for(int j = 1; j <= 10; ++j){
				if(divisor * j <= dividend){
					shang_count++;
				}else{
					dividend -= divisor * (j-1);
					dividend *= 10;
					break;	
				}
			}
			shang[i] = (char)(shang_count+48); // every digit of shang
		}
	}
	if(dividend != 0) return 0;
	else
	
}

int main(){
	int N, n, digit = 0;
	long long k;
	char p[102] = {};
	scanf("%d", &N);
	for(int i = 0; i < N; ++i){
		scanf("%d", &n);
		getchar();
		scanf("%s", p);
		for(int i = 0; i < N; ++i){
			if(p[i]) digit++;
		}
		
		for(int i = 2; i < INT_MAX; ++i){
			int count = 0;
			divide(i, long long dividend, p, count, digit);
		}
	}
	
	
	return 0;
}
