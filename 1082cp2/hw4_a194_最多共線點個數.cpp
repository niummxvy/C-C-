#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct coordinate{
	int x;
	int y;
}Cor;

int cmp(const void * a, const void * b){	
	if((*(Cor*)a).x == (*(Cor*)b).x) return (*(Cor*)a).y < (*(Cor*)b).y; // descend
	else return (*(Cor*)a).x < (*(Cor*)b).x; // descend
}

int gcd(int a, int b){
	if(b != 0) gcd(b, a%b);
	else return a;
}

int main(){
	int N;
	int tempX, tempY, x, y;
	
	while(scanf("%d", &N) != EOF){
		if(N <= 0) continue;
		int k = 1, n = 1, count = 2, Max = 0;
		Cor XY[N], slope_XY[N];
		memset(XY, 0, N);
		memset(slope_XY, 0, N);
		
		for(int i = 0; i < N; ++i){ // (n)
			scanf("%d %d", &x, &y);
			XY[i].x = x; // record the x coordinate
			XY[i].y = y; // record the y coordinate
		}
		if(N == 1){
			printf("1\n");
			continue;
		}
		else if(N == 2){
			printf("2\n");
			continue;
		}
/*		for(int i = 0; i < N; ++i){
			printf("X: ");
			printf("%d ", XY[i].x);
		}
		printf("\n");
		for(int i = 0; i < N; ++i){
			printf("Y: ");
			printf("%d ", XY[i].y);
		}
		printf("\n"); */
		for(int i = 0; i < N-1; ++i){
			for(int j = i+1; j < N; ++j){
				slope_XY[j-k].x = (XY[j].x - XY[i].x) / gcd((XY[j].x - XY[i].x), (XY[j].y - XY[i].y));
				slope_XY[j-k].y = (XY[j].y - XY[i].y) / gcd((XY[j].x - XY[i].x), (XY[j].y - XY[i].y));
			}
			k++;
/*			printf("slope before qsort: \n");
			for(int j = 0; j < N-n; ++j){

				printf("%d:%d ", slope_XY[j].x, slope_XY[j].y);
			}
			printf("\n\n"); */

			qsort(slope_XY, N-n, sizeof(Cor), cmp); // n*(n*log(n))
			n++;
/*			printf("slope after qsort: \n");
			for(int j = 0; j < N-n; ++j){

				printf("%d:%d ", slope_XY[j].x, slope_XY[j].y);
			}
			printf("\n\n"); */

			tempX = slope_XY[0].x;
			tempY = slope_XY[0].y;
			for(int j = 1; j < N; ++j){
				if(tempX == 0 && slope_XY[j].x == tempX){
					count++;
					if(count > Max) Max = count;
					continue;
				}
				if(tempY == 0 && slope_XY[j].y == tempY){
					count++;
					if(count > Max) Max = count;
					continue;
				}
				if(slope_XY[j].x == tempX && slope_XY[j].y == tempY){
					count++;
					if(count > Max) Max = count; // find mode (the most one) (n^2)	
				}
				else if(slope_XY[j].x == tempX*(-1) && slope_XY[j].y == tempY*(-1)){
					count++;
					if(count > Max) Max = count;
				}
				else{
					tempX = slope_XY[j].x;
					tempY = slope_XY[j].y;
					count = 2;
				}
			}
			count = 2;
		}
		printf("%d\n", Max);
	}
	return 0;
} 

/*
9
-1 2
1 2
-1 1
1 1
-1 0
1 0
-1 -1
1 -1
1 -2
*/


