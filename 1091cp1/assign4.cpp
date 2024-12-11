#include <stdio.h>

int solve_x(char dir, int step){
	if(dir == 'R') return step;
	else return -step; 
}

int solve_y(char dir, int step){
	if(dir == 'U') return step;
	else return -step; 
}

int main(){
	char dir;
	int x, y, step1, step2, skip = 0;
	scanf("%d %d", &x, &y);
	while(scanf(" %c %d", &dir, &step1) != EOF){
		if(skip != 0 && dir == 'T'){
			scanf("%d", &step2);
//			printf("x: %d, y: %d, dir: %c, skip: %d\n", x, y, dir, skip);
			--skip;
			continue;
		}
		else if(skip != 0 && dir != 'T'){
//			printf("x: %d, y: %d, dir: %c, skip: %d\n", x, y, dir, skip);
			--skip;
			continue;
		}
		
		if(dir == 'S') skip = step1;
		if(dir == 'T'){
			scanf("%d", &step2);
			x = step1;
			y = step2;
		}
		if(dir == 'L' || dir == 'R') x += solve_x(dir, step1);
		if(dir == 'U' || dir == 'D') y += solve_y(dir, step1);
		
//		printf("x: %d, y: %d, dir: %c, skip: %d\n", x, y, dir, skip);
	}
	printf("(%d , %d)\n", x, y);
	
	
	return 0;
} 
