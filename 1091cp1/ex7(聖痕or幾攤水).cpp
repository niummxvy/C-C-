#include <stdio.h>
#define SIZE 21

void find(int sign[][SIZE], int x, int y, int n){
	sign[y][x] = 1;
	if(x+1 < n && sign[y][x+1] == 0) find(sign, x+1, y, n); // right
	if(y-1 >= 0 && sign[y-1][x] == 0) find(sign, x, y-1, n); // up
	if(x-1 >= 0 && sign[y][x-1] == 0) find(sign, x-1, y, n); // left
	if(y+1 < n && sign[y+1][x] == 0) find(sign, x, y+1, n); // down
}

int main(){
	int T;
	scanf("%d", &T);
	for(int time = 0; time < T; ++time){
		int n, score = 0;
		scanf("%d", &n);
		char graph[SIZE][SIZE] = {}; 
		int sign[SIZE][SIZE] = {};
		
		for(int i = 0; i < SIZE; ++i){
			for(int j = 0; j < SIZE; ++j){
				sign[i][j] = 100;
			}
		}
		
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				scanf(" %c", &graph[i][j]); // input '#' or '.'
			}
		}
		
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				// turn '#' to 0 and turn '.' to 2
				if(graph[i][j] == '#') sign[i][j] = 0;
				else if(graph[i][j] == '.') sign[i][j] = 2;
			}
		}
		
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				if(sign[i][j] == 0){
					find(sign, j, i, n);
					++score;
				}
			}
		}
		printf("%d\n", score);
	}
	return 0;
}
