#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 200

struct detail{
	char name[100];
	int type;
	double atk;
	double rcv;
};
typedef struct detail Detail;

int canDissolve = 1; // whether the table can be dissolved
int table[5][6], dissolved[5][6] = {}; // table stores the complete table, dissolve stores where can be dissolved
int fall[300][6], row_fall = 0; // stones ready to fall(for every column) and how many rows in fall[]
int itr[6] = {}; // itr in fall(for every column)
double normal[6] = {}, reinforced[6] = {}; // normal and reinforced stones(for every type)

int type_to_num(char type[SIZE]){
	if(strcmp(type, "Water") == 0) return 0;
	else if(strcmp(type, "Fire") == 0) return 1;
	else if(strcmp(type, "Earth") == 0) return 2;
	else if(strcmp(type, "Light") == 0) return 3;
	else if(strcmp(type, "Dark") == 0) return 4;
	else if(strcmp(type, "None") == 0) return -1;
}

int stone_to_num(char type){
	if(type == 'w') return 0;
	else if(type == 'f') return 1;
	else if(type == 'e') return 2;
	else if(type == 'l') return 3;
	else if(type == 'd') return 4;
	else if(type == 'h') return 5;
	else if(type == 'W') return 6;
	else if(type == 'F') return 7;
	else if(type == 'E') return 8;
	else if(type == 'L') return 9;
	else if(type == 'D') return 10;
	else if(type == 'H') return 11;
}

void dissolve(){
	for(int row = 0; row < 5; ++row){
		for(int col = 0; col < 6; ++col){
			if(col < 4 && table[row][col] != -1 && table[row][col+1] != -1 && table[row][col+2] != -1
			&& table[row][col] % 6 == table[row][col+1] % 6 && table[row][col+1] % 6 == table[row][col+2] % 6){ // right
				canDissolve = 1;
				for(int i = col; i <= col+2; ++i){
					if(dissolved[row][i] == 0){
						if(table[row][i] < 6) ++normal[table[row][i] % 6];
						else ++reinforced[table[row][i] % 6];
					}
					dissolved[row][i] = 1;
				}
				for(int right = col+3; right < 6; ++right){
					if(table[row][right] != -1 && table[row][right] % 6 == table[row][col] % 6){
						if(dissolved[row][right] == 0){
							if(table[row][right] < 6) ++normal[table[row][right] % 6];
							else ++reinforced[table[row][right] % 6];
						}
						dissolved[row][right] = 1;
					}
					else break;
				}
			}
			
			if(row < 3 && table[row][col] != -1 && table[row+1][col] != -1 && table[row+2][col] != -1
			&& table[row][col] % 6 == table[row+1][col] % 6 && table[row+1][col] % 6 == table[row+2][col] % 6){ // down
				canDissolve = 1;
				for(int i = row; i <= row+2; ++i){
					if(dissolved[i][col] == 0){
						if(table[i][col] < 6) ++normal[table[i][col] % 6];
						else ++reinforced[table[i][col] % 6];
					}
					dissolved[i][col] = 1;
				}
				for(int down = row+3; down < 5; ++down){
					if(table[down][col] != -1 && table[down][col] % 6 == table[row][col] % 6){
						if(dissolved[down][col] == 0){
							if(table[down][col] < 6) ++normal[table[down][col] % 6];
							else ++reinforced[table[down][col] % 6];
						}
						dissolved[down][col] = 1;
					}
					else break;
				}
			}
		}
	}
	
/*	printf("dissolved: \n");
	for(int row = 0; row < 5; ++row){
		for(int col = 0; col < 6; ++col){
			printf("%d ", dissolved[row][col]);
		}
		printf("\n");
	} 
	for(int i = 0; i < 6; ++i) printf("%lf ", normal[i]);
	printf("\n");
	for(int i = 0; i < 6; ++i) printf("%lf ", reinforced[i]);
	printf("\n"); */
	
	for(int row = 0; row < 5; ++row){
		for(int col = 0; col < 6; ++col){
			if(dissolved[row][col] == 1){
				table[row][col] = -1;
				dissolved[row][col] = 0;
			}
		}
	}
}

void fill(int col){
	if(itr[col] >= 0){
		int start_fill = -1;
		for(int row = 4; row >= 0; --row){
			if(table[row][col] == -1){
				start_fill = row;
				break;
			}
		}
		if(start_fill != -1){
			while(itr[col] >= 0 && start_fill >= 0)
				table[start_fill--][col] = fall[itr[col]--][col];
		}
	}
}

int cmp(const void * a, const void * b){
	Detail atk1 = *(Detail*)a;
	Detail atk2 = *(Detail*)b;
	return atk2.atk - atk1.atk;
}

int main(){
	for(int i = 0; i < 5; ++i){
		for(int j = 0; j < 6; ++j){
			table[i][j] = -1;
		}
	}
	for(int i = 0; i < 300; ++i){
		for(int j = 0; j < 6; ++j){
			fall[i][j] = -1;
		}
	}
	char str[SIZE] = {};
	int count = 0;
	Detail detail[6];
	while(fgets(str, SIZE, stdin)){
		if(str[strlen(str)-1] == '\n') str[strlen(str)-1] = 0;
		if(strcmp(str, "--------------------") == 0){
			++count;
			break;
		}
		char content[SIZE] = {};
		for(int i = 0; i < strlen(str); ++i){
			if(str[i] == ':'){
				for(int j = i+2, k = 0; j < strlen(str); ++j) content[k++] = str[j];
				break;
			}
		}
		switch (count % 5){
			case 0:
				break;
			case 1:
				memset(detail[count/5].name, 0, 100);
				strcpy(detail[count/5].name, content);
				break;
			case 2:
				detail[count/5].type = type_to_num(content);
				break;
			case 3:
				detail[count/5].atk = 0;
				for(int i = 0; i < strlen(content); ++i) 
					detail[count/5].atk = detail[count/5].atk * 10 + (content[i] - '0');
				break;
			case 4:
				detail[count/5].rcv = 0;
				for(int i = 0; i < strlen(content); ++i) 
					detail[count/5].rcv = detail[count/5].rcv * 10 + (content[i] - '0');
				if(strcmp(detail[count/5].name, "None") == 0) count -= 5;
				break;
		}
		++count;
	}
	
	while(scanf("%s", str) != EOF){
		if(strcmp(str, "------") == 0) break;
		for(int i = 0; i < strlen(str); ++i) fall[row_fall][i] = stone_to_num(str[i]); 
		++row_fall;
	}
	for(int i = 0; i < 6; ++i) itr[i] = row_fall-1;
	
	for(int i = 0; i < 5; ++i){
		scanf("%s", str);
		for(int j = 0; j < strlen(str); ++j) table[i][j] = stone_to_num(str[j]);
	}
	
	while(canDissolve == 1){
		canDissolve = 0;
		
		dissolve();
		for(int col = 0; col < 6; ++col){
			for(int row1 = 4; row1 >= 0; --row1){
				if(table[row1][col] == -1){
					for(int row2 = row1-1; row2 >= 0; --row2){
						if(table[row2][col] != -1){ // pull down (haven't fallen yet)
							table[row1][col] = table[row2][col];
							table[row2][col] = -1;
							break;
						}
					}
				}
			}
		}
		for(int col = 0; col < 6; ++col){ // calculate how many stones should be fallen in every slot
			fill(col);
		}
	}
/*	printf("\n");
	for(int i = 0; i < 5; ++i){
		for(int j = 0; j < 6; ++j){
			printf("%d ", table[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(int i = 0; i < 6; ++i) printf("%lf ", normal[i]);
	printf("\n");
	for(int i = 0; i < 6; ++i) printf("%lf ", reinforced[i]);
	printf("\n"); */
	
	for(int i = 0; i < count/5; ++i){
		double atk = detail[i].atk, rcv = detail[i].rcv;
		detail[i].atk *= normal[detail[i].type]/3;
		detail[i].atk += atk * reinforced[detail[i].type]/2;
		detail[i].rcv *= normal[5]/3;
		detail[i].rcv += rcv * reinforced[5]/2;
	}
	
	qsort(detail, count/5, sizeof(Detail), cmp);
	
	for(int i = 0; i < 6; ++i){
		printf("-------------------------------------------\n");
		if(i < count/5){ // not None
			printf("| %-39s |\n", detail[i].name);
			printf("| Damage : %-10.0lf| Recovery : %-8.0lf|\n", detail[i].atk, detail[i].rcv);
		}
		else{
			printf("| None                                    |\n");
			printf("| Damage : 0         | Recovery : 0       |\n");
		}
	}
	printf("-------------------------------------------\n");
	return 0;
} 

/*
----LEADER----
NAME : Cauldron of Divinity - Tuo Ba Yu-Er
TYPE : Fire
ATTACK : 1497
RECOVERY : 451
----MEMBER1----
NAME : None
TYPE : None
ATTACK : 0
RECOVERY : 0
----MEMBER2----
NAME : Scourge of Transfiguration - Circe
TYPE : Earth
ATTACK : 1356
RECOVERY : 402
----MEMBER3----
NAME : None
TYPE : None
ATTACK : 0
RECOVERY : 0
----MEMBER4----
NAME : Land Overlord Duncan
TYPE : Earth
ATTACK : 1100
RECOVERY : 386
----SUPPORTER----
NAME : Stone of Origin - Syu Siao-Syue
TYPE : Water
ATTACK : 1462
RECOVERY : 481
--------------------
fDlflw
FDwfdf
FHwedf
ddHedH
FHweDf
FHwdhf
lHllDH
wdwdlh
lwWhld
------
hHhHhH
feldhw
wfeldh
wfeldh
wfeldh

*/
