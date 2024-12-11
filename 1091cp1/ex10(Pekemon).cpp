#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pokemon{
	char cOrder[5];
	int iOrder;
	char name[12];
	char cAttack[5];
	int iAttack;
	char cDefense[5];
	int iDefense;
	char cHealth[6];
	int iHealth;
};
typedef struct pokemon Pokemon;

int ctoi(char arr[5]){
	int temp = 0;
	for(int i = 0; i < strlen(arr); ++i){
		if(arr[i] >= '0' && arr[i] <= '9') temp = temp * 10 + (arr[i] - '0');
	}
	return temp;
}

int cmp(const void * a, const void * b){
	Pokemon *p1 = (Pokemon*)a;
	Pokemon *p2 = (Pokemon*)b;
	return p2->iAttack - p1->iAttack;
}

void swap(Pokemon *p1, Pokemon *p2){
	Pokemon temp = *p1;
//	strcpy(temp.cOrder, p1->cOrder); strcpy(temp.name, p1->name); strcpy(temp.cAttack, p1->cAttack); strcpy(temp.cDefense, p1->cDefense); strcpy(temp.cHealth, p1->cHealth);
//	temp.iOrder = p1->iOrder; temp.iAttack = p1->iAttack; temp.iDefense = p1->iDefense; temp.iHealth = p1->iHealth; 
	
//	strcpy(p1->cOrder, p2->cOrder); strcpy(p1->name, p2->name); strcpy(p1->cAttack, p2->cAttack); strcpy(p1->cDefense, p2->cDefense); strcpy(p1->cHealth, p2->cHealth);
//	p1->iOrder = p2->iOrder; p1->iAttack = p2->iAttack; p1->iDefense = p2->iDefense; p1->iHealth = p2->iHealth; 
	
//	strcpy(p2->cOrder, temp.cOrder); strcpy(p2->name, temp.name); strcpy(p2->cAttack, temp.cAttack); strcpy(p2->cDefense, temp.cDefense); strcpy(p2->cHealth, temp.cHealth);
//	p2->iOrder = temp.iOrder; p2->iAttack = temp.iAttack; p2->iDefense = temp.iDefense; p2->iHealth = temp.iHealth; 
	*p1 = *p2;
	*p2 = temp;
}

void cmp_def(int begin, int end, Pokemon *pkm){
	for(int i = begin; i < end; ++i){
		for(int j = i+1; j <= end; ++j){
//			printf("(D) %d: %d, %d: %d\n", i, pkm[i].iDefense, j, pkm[j].iDefense);
			if(pkm[i].iDefense < pkm[j].iDefense) swap(&pkm[i], &pkm[j]);
		}
	}
}

void cmp_name_len(int begin, int end, Pokemon *pkm){
	for(int i = begin; i < end; ++i){
		for(int j = i+1; j <= end; ++j){
//			printf("(N) %d: %s, %d: %s\n", i, pkm[i].name, j, pkm[j].name);
			if(strlen(pkm[i].name) < strlen(pkm[j].name)) swap(&pkm[i], &pkm[j]);
		}
	}
}

void cmp_dict(int begin, int end, Pokemon *pkm){
	for(int i = begin; i < end; ++i){
		for(int j = i+1; j <= end; ++j){
			for(int k = 0; k < strlen(pkm[i].name); ++k){
				if(pkm[i].name[k] < pkm[j].name[k]) break;
				else if(pkm[i].name[k] > pkm[j].name[k]){
//					printf("(C) %d: %c, %d: %c\n", i, pkm[i].name[k], j, pkm[j].name[k]);
					swap(&pkm[i], &pkm[j]);
					break;
				}
				
			}
		}
	}
}

int main(){
	int size = 300, count = 0, itr = 0;
	Pokemon *pokemon = (Pokemon*)malloc(sizeof(Pokemon) * size);
//	Pokemon pokemon[300];
	char str[20] = {};
	while(scanf("%s", str) != EOF){
		if(itr % 5 == 0){
			strcpy(pokemon[count].cOrder, str);
			pokemon[count].iOrder = ctoi(pokemon[count].cOrder);
		}
		else if(itr % 5 == 1){
			strcpy(pokemon[count].name, str);
		}
		else if(itr % 5 == 2){
			strcpy(pokemon[count].cAttack, str);
			pokemon[count].iAttack = ctoi(pokemon[count].cAttack);
		}
		else if(itr % 5 == 3){
			strcpy(pokemon[count].cDefense, str);
			pokemon[count].iDefense = ctoi(pokemon[count].cDefense);
		}
		else if(itr % 5 == 4){
			strcpy(pokemon[count].cHealth, str);
			pokemon[count].iHealth = ctoi(pokemon[count].cHealth);
			++count;
		}
		++itr;
		if(count >= size-1){
			size *= 2;
//			printf("size: %d\n", size);
			pokemon = (Pokemon*)realloc(pokemon, sizeof(Pokemon) * size);
		}
	}
	
	qsort(pokemon, count, sizeof(Pokemon), cmp);
/*	printf("-------\n");
	for(int i = 0; i < count; ++i){
		printf("%-4s%-11s%-4d%-4d%-4d\n", pokemon[i].cOrder, pokemon[i].name, pokemon[i].iAttack, pokemon[i].iDefense, pokemon[i].iHealth);
	}
	printf("-------\n"); */
	
	for(int i = 1; i < count; ++i){
		if(pokemon[i].iAttack == pokemon[i-1].iAttack){
			int begin = i-1;
			int end_atk = -1;
			for(int j = i+1; j <= count; ++j){
				if(pokemon[begin].iAttack != pokemon[j-1].iAttack){
					end_atk = j-2;
					cmp_def(begin, end_atk, pokemon);
					break;
				}
			}
			if(end_atk == -1){
				end_atk = count - 1;
				cmp_def(begin, end_atk, pokemon);
			}
			
			for(int j = begin+1; j <= end_atk; ++j){
				if(pokemon[j].iDefense == pokemon[j-1].iDefense){
					begin = j-1;
					int end_def = -1;
					for(int k = j+1; k <= end_atk+1; ++k){
						if(pokemon[begin].iDefense != pokemon[k-1].iDefense){
							end_def = k-2;
							cmp_name_len(begin, end_def, pokemon);
							break;
						}
					}
					if(end_def == -1){
						end_def = end_atk;
						cmp_name_len(begin, end_def, pokemon);
					}
					
					for(int k = begin+1; k <= end_def; ++k){
						if(strlen(pokemon[k].name) == strlen(pokemon[k-1].name)){
							begin = k-1;
							int end_name_len = -1;
							for(int m = k+1; m <= end_def+1; ++m){
								if(strlen(pokemon[begin].name) != strlen(pokemon[m-1].name)){
									end_name_len = m-2;
									cmp_dict(begin, end_name_len, pokemon);
									break;
								}
							}
							if(end_name_len == -1){ // strlen are same to the last one 
								end_name_len = end_def;
								cmp_dict(begin, end_name_len, pokemon);
							}
						}
					}
				}
			}
		}
		
		printf("%-3s %-10s %-3d %-3d %d\n", pokemon[i-1].cOrder, pokemon[i-1].name, pokemon[i-1].iAttack, pokemon[i-1].iDefense, pokemon[i-1].iHealth);
	}
//	        %-4s%-11s%-4d%-4d%-4d\n      cannot, why?
	printf("%-3s %-10s %-3d %-3d %d\n", pokemon[count-1].cOrder, pokemon[count-1].name, pokemon[count-1].iAttack, pokemon[count-1].iDefense, pokemon[count-1].iHealth);
	return 0;
}
/*
001 abcdmn 12 34 56
002 abcdef 12 34 56
003 abcamn 12 34 56
*/

/*
001 aaaa 12 34 56
002 aa 12 35 56
003 aaa 12 36 56
004 bbbb 12 34 56
005 bb 12 35 56
006 bbb 12 36 56
*/

/*
001 aaaa 12 34 56
002 aa 12 35 56
003 aaa 12 35 56
*/

/* 
001 bbb 12 34 56
002 bbbb 12 34 56
003 bb 12 34 56
004 aaa 12 34 56
005 aaaa 12 34 56
006 aa 12 34 56
*/ 

/* filter
007 aca 12 35 56
001 aca 12 34 56
002 aba 12 34 56
003 aca 12 34 56
004 aba 12 34 56
005 aca 12 34 56
008 aba 12 33 56
*/

/*
126 Magmar 1 1 483
213 Shuckle 4 4 331
005 Charmeleon 1 1 634
183 Marill 5 4 113
055 Golduck 1 2 342
312 Minun 5 5 595
145 Zapdos 2 2 342
297 Hariyama 5 6 377
206 Dunsparce 3 2 207
024 Arbok 6 6 862
021 Spearow 3 3 871
163 Hoothoot 6 6 550
148 Dragonair 3 4 193
*/

/*
216 Teddiursa 26 79 446
175 Togepi 31 26 210
353 Shuppet 91 8 383
033 Nidorino 87 100 922
363 Spheal 28 76 781
089 Muk 15 73 828
098 Krabby 91 12 995
126 Magmar 81 46 483
213 Shuckle 25 28 331
005 Charmeleon 57 23 634
183 Marill 91 68 113
055 Golduck 88 20 342
312 Minun 37 40 595
145 Zapdos 88 20 342
297 Hariyama 48 43 377
206 Dunsparce 49 10 207
024 Arbok 15 79 862
021 Spearow 89 63 871
163 Hoothoot 72 52 550
148 Dragonair 74 66 193
014 Kakuna 100 69 640
052 Meowth 88 20 342
001 Bulbasaur 88 50 342
367 Huntail 88 20 342
029 NidoranO 88 25 342
043 Oddish 88 20 342
338 Solrock 22 32 796
070 Weepinbell 61 87 273
073 Tentacruel 41 80 696
059 Arcanine 46 76 428
045 Vileplume 88 20 342
265 Wurmple 65 49 121
079 Slowpoke 10 18 104
305 Lairon 68 18 457
147 Dratini 79 64 426
048 Venonat 88 20 342
133 Eevee 82 67 1052
130 Gyarados 76 30 937
107 Hitmonchan 79 74 101
*/
