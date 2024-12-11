#include <stdio.h>
#include <string.h>

typedef struct cat{
	int x;
	int y;
}Cat;

typedef struct queue{
	int x;
	int y;
}Queue;

int main(){
	int N;
	int dx[4] = {1, 0, -1, 0};
	int dy[4] = {0, -1, 0, 1};
	while(scanf("%d", &N) != EOF){
		if(N == 0) break;
		char puzzle[101][101] = {};
		Cat cat;
		int m = 0, c = 0; // mouse/cat check
		for(int row = 0; row < N; ++row){
			scanf("%s", puzzle[row]);
			getchar();
		}
		
/*		for(int i = 0; i < N; ++i){
			for(int j = 0; j < 100; ++j){
				if(puzzle[i][j] == '\n') break;
				printf("%c", puzzle[i][j]);
			}
			printf("\n");
		} */
		
		int column;
		for(int row = 0; row < N; ++row){
			for(int col = 0; col < 101; ++col){
				if(puzzle[row][col] == 0){
					column = col;
					break;
				}
				else if(puzzle[row][col] == 'K'){
					cat.x = col;
					cat.y = row;
					c = 1;
				}
			}
			if(c == 1) break;
		}
		
// BFS
		int map[101][101] = {}, front = 0, rear = 0; // queue[x][y]
		memset(map, 0, sizeof(map));
		
		Queue queue[1000000];
		queue[rear].x = cat.x;
		queue[rear].y = cat.y;
		++rear;
		map[cat.y][cat.x] = 0;
		for(front; front < rear; ++front){
			int catX = queue[front].x;
			int catY = queue[front].y;
			if(puzzle[catY][catX] == '@'){
				m = 1;
				printf("%d\n", map[catY][catX]);
				break;
			}

			for(int i = 0; i < 4; ++i){
				if(catX + dx[i] >= 0 && catX + dx[i] < column && catY + dy[i] >= 0 && catY + dy[i] < N && 
				puzzle[catY + dy[i]][catX + dx[i]] != '#' && map[catY + dy[i]][catX + dx[i]] == 0){
					queue[rear].x = catX + dx[i];
					queue[rear].y = catY + dy[i];
					rear++;
					map[catY + dy[i]][catX + dx[i]] = map[catY][catX] + 1;
					
				}
			}
			
			
		}
		if(m == 0) printf("= =\n");
	}
	
	
	
	return 0;
} 
