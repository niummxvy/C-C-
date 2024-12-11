#include <stdio.h>

int main(){
	int N, week, M, D;
	scanf("%d", &N);
	for(int i = 0; i < N; ++i){
		scanf("%d %d", &M, &D);
	//	1/1 is Wed.
		if(M == 1){
			week = (1 + D) % 7 + 1;
		}
		else if(M == 2){
			week = (1 + 31 + D) % 7 + 1;
		}
		else if(M == 3){
			week = (1 + 60 + D) % 7 + 1;
		}
		else if(M == 4){
			week = (1 + 91 + D) % 7 + 1;
		}
		else if(M == 5){
			week = (1 + 121 + D) % 7 + 1;
		}
		else if(M == 6){
			week = (1 + 152 + D) % 7 + 1;
		}
		else if(M == 7){
			week = (1 + 182 + D) % 7 + 1;
		}
		else if(M == 8){
			week = (1 + 213 + D) % 7 + 1;
		}
		else if(M == 9){
			week = (1 + 244 + D) % 7 + 1;
		}
		else if(M == 10){
			week = (1 + 274 + D) % 7 + 1;
		}
		else if(M == 11){
			week = (1 + 305 + D) % 7 + 1;
		}
		else if(M == 12){
			week = (1 + 335 + D) % 7 + 1;
		}
		
		if(week == 1){
			printf("Monday\n");
		}
		else if(week == 2){
			printf("Tuesday\n");
		}
		else if(week == 3){
			printf("Wednesday\n");
		}
		else if(week == 4){
			printf("Thursday\n");
		}
		else if(week == 5){
			printf("Friday\n");
		}
		else if(week == 6){
			printf("Saturday\n");
		}
		else if(week == 7){
			printf("Sunday\n");
		}
		week = 0;
	}
		
	
	return 0;
} 

