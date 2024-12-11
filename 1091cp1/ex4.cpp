#include <stdio.h>

long long gcd(long long a, long long b){
	long long temp;
	while(a % b != 0){
		temp = b;
		b = a % b;
		a = temp;
	}
	return b;
}

int main(){
	long long LCM, GCD, num;
	scanf("%lld", &num);
	GCD = num;
	LCM = num;
	while(scanf("%lld", &num) != EOF){
		if(num == 0) break;
		GCD = gcd(LCM, num);
		LCM = (LCM / GCD) * num;
	}
	if(num == 0) printf("0\n");
	else printf("%lld\n", LCM);
	return 0;
}
