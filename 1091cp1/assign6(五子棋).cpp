# include<stdio.h>
#define SIZE 15
#define LEN 225

struct position{
	int x;
	int y;
};
typedef struct position Pos;

int C2col(char C){
	return C - 'A';
}

int I2row(int I){
	return I-1;
}

int isRepeat(Pos posi[], int order){
	for(int i = 0; i < order; ++i){
		for(int j = i+1; j < order; ++j){
			if((posi[i].x == posi[j].x) && (posi[i].y == posi[j].y)) return 1;
		}
	}
	return 0;
}

int isOut(Pos posi[], int order){
	int temp = order - 1;
	if((posi[temp].x < 0 || posi[temp].x > SIZE-1) || (posi[temp].y < 0 || posi[temp].y > SIZE-1))
		return 1;
	return 0;
}

int judge(int (*Board)[SIZE], int order);

int main(){
	int board[SIZE][SIZE] = {};
	for(int i = 0; i < SIZE; ++i){
		for(int j = 0; j < SIZE; ++j){
			board[i][j] = 0;
		}
	}
	int order = 0, isTie = -1;
	char C;
	int I;
	Pos pos[LEN+5];
	for(int i = 0; i < LEN; ++i){
		pos[i].x = 100;
		pos[i].y = 100;
	}
	
	while(scanf(" %c %d", &C, &I) != EOF){
		pos[order].x = I2row(I);
		pos[order].y = C2col(C);
		++order;
		if(isRepeat(pos, order) != 0){
			printf("Invalid move at step %d.\n", order);
			return 0;
		}else if(isOut(pos, order) != 0){
			printf("Invalid move at step %d.\n", order);
			return 0;
		}
		else{
			if(order % 2 == 1){ // odd is black
				board[pos[order-1].x][pos[order-1].y] = 1;
			}else if(order % 2 == 0){ // even is white
				board[pos[order-1].x][pos[order-1].y] = 2;
			}
			
/*			for(int i = 0; i < SIZE; ++i){
				for(int j = 0; j < SIZE; ++j){
					printf("%d ", board[i][j]);
				}
				printf("\n");
			} */
			
			isTie = judge(board, order);
			if(isTie == 0 || order > LEN) break;
		}
		
	}
	if(isTie == 1 || order > LEN){
		printf("The game is tie.\n");
	}
	return 0;
} 


int judge(int (*Board)[SIZE], int order){
	// OOOOO
	for(int i = 0; i < SIZE; ++i){
		for(int j = 2; j < SIZE-2; ++j){
			if(Board[i][j-2] != 0
			&& Board[i][j-1] != 0
			&& Board[i][j] != 0
			&& Board[i][j+1] != 0
			&& Board[i][j+2] != 0
			&& Board[i][j-2] == Board[i][j-1]
			&& Board[i][j-1] == Board[i][j]
			&& Board[i][j] == Board[i][j+1]
			&& Board[i][j+1] == Board[i][j+2]){
				if(order % 2 == 1){
					printf("The winner is black.\n");
					return 0;
				}else{
					printf("The winner is white.\n");
					return 0;
				}
			}
		}
	}
	/*
	    O
	   O
	  O
	 O
	O
	*/
	for(int i = 2; i < SIZE-2; ++i){
		for(int j = 2; j < SIZE-2; ++j){
			if(Board[i-2][j+2] != 0
			&& Board[i-1][j+1] != 0
			&& Board[i][j] != 0
			&& Board[i+1][j-1] != 0
			&& Board[i+2][j-2] != 0
			&& Board[i-2][j+2] == Board[i-1][j+1]
			&& Board[i-1][j+1] == Board[i][j]
			&& Board[i][j] == Board[i+1][j-1]
			&& Board[i+1][j-1] == Board[i+2][j-2]){
				if(order % 2 == 1){
					printf("The winner is black.\n");
					return 0;
				}else{
					printf("The winner is white.\n");
					return 0;
				}
			}
		}
	}
	/*
	O
	O
	O
	O
	O
	*/
	for(int i = 2; i < SIZE-2; ++i){
		for(int j = 0; j < SIZE; ++j){
			if(Board[i-2][j] != 0
			&& Board[i-1][j] != 0
			&& Board[i][j] != 0
			&& Board[i+1][j] != 0
			&& Board[i+2][j] != 0
			&& Board[i-2][j] == Board[i-1][j]
			&& Board[i-1][j] == Board[i][j]
			&& Board[i][j] == Board[i+1][j]
			&& Board[i+1][j] == Board[i+2][j]){
				if(order % 2 == 1){
					printf("The winner is black.\n");
					return 0;
				}else{
					printf("The winner is white.\n");
					return 0;
				}
			}
		}
	}
	/*
	O
	 O
	  O
	   O
	    O
	*/
	for(int i = 2; i < SIZE-2; ++i){
		for(int j = 2; j < SIZE-2; ++j){
			if(Board[i-2][j-2] != 0
			&& Board[i-1][j-1] != 0
			&& Board[i][j] != 0
			&& Board[i+1][j+1] != 0
			&& Board[i+2][j+2] != 0
			&& Board[i-2][j-2] == Board[i-1][j-1]
			&& Board[i-1][j-1] == Board[i][j]
			&& Board[i][j] == Board[i+1][j+1]
			&& Board[i+1][j+1] == Board[i+2][j+2]){
				if(order % 2 == 1){
					printf("The winner is black.\n");
					return 0;
				}else{
					printf("The winner is white.\n");
					return 0;
				}
			}
		}
	}
	return 1;
}
