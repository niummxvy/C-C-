#include <stdio.h>
#define SIZE 10

void cal(int (*mat1)[SIZE], int (*mat2)[SIZE], int row, int col, int times);

int main(){
	int row1, row2, col1, col2;
	while(scanf("%d %d", &row1, &col1) != EOF){
		int mat1[SIZE][SIZE] = {}, mat2[SIZE][SIZE] = {};
		for(int i = 0; i < row1; ++i){
			for(int j = 0; j < col1; ++j){
				scanf("%d", &mat1[i][j]);
			}
		}
		scanf("%d %d", &row2, &col2);
		for(int i = 0; i < row2; ++i){
			for(int j = 0; j < col2; ++j){
				scanf("%d", &mat2[i][j]);
			}
		}
		if(col1 != row2) printf("Invalid calculation!!\n");
		else{
			cal(mat1, mat2, row1, col2, col1);
		}
	}
	
	
	
	return 0;
}

void cal(int (*mat1)[SIZE], int (*mat2)[SIZE], int row, int col, int times){
	int mat[SIZE][SIZE] = {};
	int sum = 0;
	for(int i = 0; i < row; ++i){
		for(int j = 0; j < col; ++j){
			for(int k = 0; k < times; ++k){
				sum += mat1[i][k] * mat2[k][j];
			}
			mat[i][j] = sum;
			sum = 0;
		}
	}
	
	for(int i = 0; i < row; ++i){
		for(int j = 0; j < col-1; ++j){
			printf("%d ", mat[i][j]);
		}
		printf("%d\n", mat[i][col-1]);
	}
}
