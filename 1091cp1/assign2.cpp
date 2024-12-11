#include <stdio.h>
#include <math.h>

double Max(double a, double b){
	if(a >= b) return a;
	else return b;
}

double min(double a, double b){
	if(a >= b) return b;
	else return a;
}

int main(){
	double x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8, A1, A2, L1, L2, L3, L4;
	scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", 
	&x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4, &x5, &y5, &x6, &y6, &x7, &y7, &x8, &y8);
	
	L1 = sqrt( pow( (Max(x1, x2) - min(x1, x2)) , 2) + pow( (Max(y1, y2) - min(y1, y2)) , 2) );
	L2 = sqrt( pow( (Max(x1, x4) - min(x1, x4)) , 2) + pow( (Max(y1, y4) - min(y1, y4)) , 2) );
	L3 = sqrt( pow( (Max(x5, x6) - min(x5, x6)) , 2) + pow( (Max(y5, y6) - min(y5, y6)) , 2) );
	L4 = sqrt( pow( (Max(x5, x8) - min(x5, x8)) , 2) + pow( (Max(y5, y8) - min(y5, y8)) , 2) );
	
	A1 = L1 * L2;
	A2 = L3 * L4;
	
	printf("%g\n%g\n", A1, A2);
	
	if(A1 > A2) printf("A > B\n");
	else if(A1 == A2) printf("A = B\n");
	else printf("A < B\n");
	
	return 0;
}

// -3.7 0 -3.7 6.5 0 6.5 0 0 0 -666.3 0 0 333.6 0 333.6 -666.3
