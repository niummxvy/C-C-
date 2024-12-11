# include <stdio.h>
# include <string.h>

struct BandD{
	int rowB;
	int colB;
	int rowD;
	int colD;
	int count;
};
typedef struct BandD TARGET;

TARGET findBD(int blocks[25][25], int N, int B, int D);

int main(){
    int N;
    char a[20] = {}, c[20] = {};
    char move[5] = "move";
    char pile[5] = "pile";
    char onto[5] = "onto";
    char over[5] = "over";
    char quit[5] = "quit";

    while(scanf("%d", &N) != EOF){

        int blocks[25][25];
        for(int i = 0; i < 25; ++i){
			for(int j = 0; j < 25; ++j){
				blocks[i][j] = 100;
			}
		}
        
        for(int i = 0; i < N; ++i)
            blocks[N-1][i] = i; // set the bottom blocks up
		
		scanf("%s", a); // input command
        //      seperate the inputed string
        while(strcmp(a, quit) != 0){
			int B, D;
			scanf("%d", &B);
			scanf("%s", c);
			scanf("%d", &D);

//            printf("a: %s\n", a);
//            printf("B: %d\n", B);
//            printf("c: %s\n", c);
//            printf("D: %d\n", D);
			
            TARGET Target = findBD(blocks, N, B, D);
            if(Target.count < 2){
				scanf("%s", a);
				continue;
        	}
            if(strcmp(a, move) == 0){
            	
            	if(Target.colB == Target.colD){
					scanf("%s", a);
            		continue;
				}
				
				for(int row = Target.rowB - 1; row >= 0; --row){
					for(int col = 0; col < N; ++col){
						if(blocks[row][Target.colB] == col){
							blocks[row][Target.colB] = 100;
							blocks[N-1][col] = col; // return the block
						}
					}
				}

                if(strcmp(c, onto) == 0){
					for(int row = Target.rowD - 1; row >= 0; --row){
						for(int col = 0; col < N; ++col){
							if(blocks[row][Target.colD] == col){
								blocks[row][Target.colD] = 100;
								blocks[N-1][col] = col; // return the block
							}
						}
					}
					blocks[Target.rowD - 1][Target.colD] = blocks[Target.rowB][Target.colB];
					blocks[Target.rowB][Target.colB] = 100;
                }
                else if(strcmp(c, over) == 0){
                	for(int row = N-1; row >= 0; --row){
	                	if(blocks[row][Target.colD] == 100){
							blocks[row][Target.colD] = blocks[Target.rowB][Target.colB];
							blocks[Target.rowB][Target.colB] = 100;
							break;
						}
					}
 				}
            }
            else if(strcmp(a, pile) == 0){
            	
            	if(Target.colB == Target.colD){
					scanf("%s", a);
            		continue;
				}
				
                if(strcmp(c, onto) == 0){
					for(int row = Target.rowD - 1; row >= 0; --row){
						for(int col = 0; col < N; ++col){
							if(blocks[row][Target.colD] == col){
								blocks[row][Target.colD] = 100;
								blocks[N-1][col] = col; // return the block
							}
						}
					}
					
					for(int rowD = Target.rowD - 1; rowD >= 0; --rowD){
						if(blocks[Target.rowB][Target.colB] == 100)
							break;
						blocks[rowD][Target.colD] = blocks[Target.rowB][Target.colB];
						blocks[Target.rowB][Target.colB] = 100;
						Target.rowB--;
					}
                }
                else if(strcmp(c, over) == 0){
					for(int rowD = Target.rowD - 1; rowD >= 0; --rowD){
						if(blocks[Target.rowB][Target.colB] == 100)
							break;
						if(blocks[rowD][Target.colD] != 100)
							continue;
						blocks[rowD][Target.colD] = blocks[Target.rowB][Target.colB];
						blocks[Target.rowB][Target.colB] = 100;
						Target.rowB--;
					}
                }
            }

/*			for(int col = 0; col < N; ++col){ // output blocks
        		printf("%d: ", col);
        		for(int row = N-1; row >= 0; --row){
            		if(blocks[row][col] != 100)
                		printf("%d ", blocks[row][col]);
        		}
        		printf("\n");
    		}
*/
			scanf("%s", a);	
    }

    for(int col = 0; col < N; ++col){ // output blocks
        printf("%d: ", col);
        for(int row = N-1; row >= 0; --row){
            if(blocks[row][col] != 100)
                printf("%d ", blocks[row][col]);
        }
        printf("\n");
    }

}

    return 0;
}

TARGET findBD(int blocks[25][25], int N, int B, int D){
	TARGET Target;
	Target.count = 0;
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j){
			if(blocks[i][j] == B){
				Target.rowB = i;
				Target.colB = j;
				Target.count++; 
			}
			if(blocks[i][j] == D){
				Target.rowD = i;
				Target.colD = j;
				Target.count++;
			}
		}
	}
	return Target;
}
