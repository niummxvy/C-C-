#include <stdio.h>
#include <string.h>

int record[15][15] = {}, Col, Row, ans = 0, all;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

void DFS(int startY, int startX, int rear, int visited){
	rear++;
	record[startY][startX] = 1;
	visited++;

	if(visited == all){
		ans++;
		return;
	}
	
	for(int i = 0; i < 4; ++i){
		if(startX + dx[i] >= 0 && startX + dx[i] < Col 
		&& startY + dy[i] >= 0 && startY + dy[i] < Row 
		&& record[startY + dy[i]][startX + dx[i]] == 0){
			if(startX + dx[0] >= 0 && startX + dx[0] < Col 
			&& startY + dy[0] >= 0 && startY + dy[0] < Row 
			&&
			startX + dx[1] >= 0 && startX + dx[1] < Col 
			&& startY + dy[1] >= 0 && startY + dy[1] < Row 
			&&
			startX + dx[2] >= 0 && startX + dx[2] < Col 
			&& startY + dy[2] >= 0 && startY + dy[2] < Row 
			&&
			startX + dx[3] >= 0 && startX + dx[3] < Col 
			&& startY + dy[3] >= 0 && startY + dy[3] < Row)
			{ // «r¨ì§À¤Ú 
				if(i % 2 == 0){ // right or left
					if(record[startY + dy[1]][startX + dx[1]] == 1 && record[startY + dy[3]][startX + dx[3]] == 1 && 
					   record[startY + dy[0]][startX + dx[0]] == 0 && record[startY + dy[2]][startX + dx[2]] == 0) continue;
				}else{ // up or down
					if(record[startY + dy[0]][startX + dx[0]] == 1 && record[startY + dy[2]][startX + dx[2]] == 1 && 
					   record[startY + dy[1]][startX + dx[1]] == 0 && record[startY + dy[3]][startX + dx[3]] == 0) continue;
				}
			} 
			
			
			if(startX != 0 && startX != Col-1 && startY != 0 && startY != Row-1){ // not at side now
				if(i == 2 && startX + dx[i]  == 0){ // left wall (turn left)				
					if(record[startY + dy[1]][startX + dx[i]] == 0 && record[startY + dy[3]][startX + dx[i]] == 0){
						int touch_wall = 0;
						for(int j = 0; j < Col; ++j){
							if(record[0][j] == 1) touch_wall = 1;
							if(record[Row-1][j] == 1) touch_wall = 1;
						}
						for(int j = 0; j < Row; ++j){
							if(record[j][0] == 1) touch_wall = 1;
							if(record[j][Col-1] == 1) touch_wall = 1;
						}
						if(touch_wall == 1){
							touch_wall = 0;
							continue;
						}
					}
				}
				else if(i == 0 && startX + dx[i]  == Col-1){ // right wall (turn right)				
					if(record[startY + dy[1]][startX + dx[i]] == 0 && record[startY + dy[3]][startX + dx[i]] == 0){
						int touch_wall = 0;
						for(int j = 0; j < Col; ++j){
							if(record[0][j] == 1) touch_wall = 1;
							if(record[Row-1][j] == 1) touch_wall = 1;
						}
						for(int j = 0; j < Row; ++j){
							if(record[j][0] == 1) touch_wall = 1;
							if(record[j][Col-1] == 1) touch_wall = 1;
						}
						if(touch_wall == 1){
							touch_wall = 0;
							continue;
						}
					}
				}
				else if(i == 1 && startY + dy[i]  == 0){ // up wall (turn up)
					if(record[startY + dy[i]][startX + dx[0]] == 0 && record[startY + dy[i]][startX + dx[2]] == 0){
						int touch_wall = 0;
						for(int j = 0; j < Col; ++j){
							if(record[0][j] == 1) touch_wall = 1;
							if(record[Row-1][j] == 1) touch_wall = 1;
						}
						for(int j = 0; j < Row; ++j){
							if(record[j][0] == 1) touch_wall = 1;
							if(record[j][Col-1] == 1) touch_wall = 1;
						}
						if(touch_wall == 1){
							touch_wall = 0;
							continue;
						}
					}
				}
				else if(i == 3 && startY + dy[i]  == Row-1){ // down wall (turn down)				
					if(record[startY + dy[i]][startX + dx[0]] == 0 && record[startY + dy[i]][startX + dx[2]] == 0){
						int touch_wall = 0;
						for(int j = 0; j < Col; ++j){
							if(record[0][j] == 1) touch_wall = 1;
							if(record[Row-1][j] == 1) touch_wall = 1;
						}
						for(int j = 0; j < Row; ++j){
							if(record[j][0] == 1) touch_wall = 1;
							if(record[j][Col-1] == 1) touch_wall = 1;
						}
						if(touch_wall == 1){
							touch_wall = 0;
							continue;
						}
					}
				}
			} 
	
			DFS(startY + dy[i], startX + dx[i], rear, visited);
			record[startY + dy[i]][startX + dx[i]] = 0;
		}
	}
	
}

int main(){
	int col, row;

	while(scanf("%d %d", &col, &row) != EOF){
		Col = col;
		Row = row;
		all = Col * Row;
		for(int start_col = 0; start_col < Col; ++start_col){
			for(int start_row = 0; start_row < Row; ++start_row){
				DFS(start_row, start_col, 0, 0);
				record[start_row][start_col] = 0;
			}
		}
		
		printf("%d\n", ans/2);
		ans = 0;
	}

	return 0;
}
