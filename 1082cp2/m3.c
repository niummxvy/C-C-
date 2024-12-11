#include <stdio.h>

int main(){

	int calendar[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
	char day[7][10] = {"Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday","Monday"};

	int num,M,D,days;
	scanf("%d\n",&num);
	for(int i = 0; i < num; i++){
		days = 0;
		scanf("%d %d\n",&M,&D);
		for (int j = 0; j < M-1; j++) 
			days += calendar[j];
		days+=D;
		printf("%s\n", day[days%7]);

	}
	return 0; 
}