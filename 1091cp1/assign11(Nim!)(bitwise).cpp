#include <stdio.h>

void print(int board){				//	print a board.
	int index = 0;
	for(int level = 0; level < 5; level++){
		for(int a = 0; a < 4-level; a++){
			printf(" ");
		}
		for(int a = 0; a <= level; a++){
			if(board & (1 << index)){
				printf("X");
			}
			else{
				if(index < 10){
					printf("%d", index);
				}
				else{
					printf("%c", index-10+'A');
				}
			}
			if(a == level){
				printf("\n");
			}
			else{
				printf(" ");
			}
			index++;
		}
	}
	return;
}

int search(int* list, int board){			//	search for legal moves, fill into list, and return the amount of legal moves.
        int size = 0;
        int index = 0;
        for(int level = 0; level < 5; level++){
                for(int a = 0; a <= level; a++){
                        if((board & (1 << index)) == 0){
                                list[size++] = board | (1 << index);
                                if((a+1) <= level && (board & (1 << (index+1))) == 0){
                                        list[size++] = board | (1 << index) | (1 << (index+1));
                                        if((a+2) <= level && (board & (1 << (index+2))) == 0){
                                                list[size++] = board | (1 << index) | (1 << (index+1)) | (1 << (index+2));
                                        }
                                }
                                if((index + level + 1) < 15 && (board & (1 << (index+level+1))) == 0){
                                        list[size++] = board | (1 << index) | (1 << (index+level+1));
                                        if((index + level + 1 + level + 2) < 15 && (board & (1 << (index + level + 1 + level + 2))) == 0){
                                                list[size++] = board | (1 << index) | (1 << (index+level+1)) | (1 << (index + level + 1 + level + 2));
                                        }
                                }
                                if((index + level + 2) < 15 && (board & (1 << (index+level+2))) == 0){
                                        list[size++] = board | (1 << index) | (1 << (index+level+2));
                                        if((index + level + 2 + level + 3) < 15 && (board & (1 << (index + level + 2 + level + 3))) == 0){
                                                list[size++] = board | (1 << index) | (1 << (index+level+2)) | (1 << (index + level + 2 + level + 3));
                                        }
                                }
                        }
                        index++;
                }
        }
        return size;
}

int main(){
	int board = 0;
	print(board);
	char input[100] = {0};
	int turn = 0;
	while(scanf("%s", input) != EOF){
		//
		//	do something...
		//
		print(board);
		turn++;
		if(board == 0x00007FFF){			//	If the board is empty.
			if(turn & 1){
				printf("White wins!\n");
			}
			else{
				printf("Black wins!\n");
			}
		}
	}
}

