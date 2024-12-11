#include <stdio.h>
#include <math.h>

int main(){
	double a, b, c, x1, x2;
	while(scanf("%lf %lf %lf", &a, &b, &c) != EOF){
		if(b*b - 4*a*c < 0){
			printf("No real root\n");
			continue;
		}
		x1 = (-b + sqrt(b*b - 4*a*c)) / (2*a);
		x2 = (-b - sqrt(b*b - 4*a*c)) / (2*a);
		if(x1 < 0 && x2 < 0){
			x1 = -(-b + sqrt(b*b - 4*a*c)) / (2*a);
			x2 = -(-b - sqrt(b*b - 4*a*c)) / (2*a);
			if(-x1 != -x2) printf("Two different roots x1=-%lld , x2=-%lld\n", (int)x1, (int)x2);
			else printf("Two same roots x=-%lld\n", (int)x1);
		}
		else if(x1 < 0 && x2 >= 0){
			x1 = -(-b + sqrt(b*b - 4*a*c)) / (2*a);
			if(-x1 != x2) printf("Two different roots x1=-%lld , x2=%lld\n", (int)x1, (int)x2);
			else printf("Two same roots x=-%lld\n", (int)x1);
		}
		else if(x1 >= 0 && x2 < 0){
			x2 = -(-b - sqrt(b*b - 4*a*c)) / (2*a);
			if(x1 != -x2) printf("Two different roots x1=%lld , x2=-%lld\n", (int)x1, (int)x2);
			else printf("Two same roots x=%lld\n", (int)x1);
		}
		else{
			if(x1 != x2) printf("Two different roots x1=%lld , x2=%lld\n", (int)x1, (int)x2);
			else printf("Two same roots x=%lld\n", (int)x1);
		}
	}
	return 0;
} 
