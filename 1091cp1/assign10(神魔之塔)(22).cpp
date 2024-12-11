#include <stdio.h>
#include <string.h>
#include"math.h"
char matrix_tmp[1000][7]={},tmp[100]={},a[100]={},name[10][100]={},type_c[10][2]={};//[人數][內容]
int col,col_0,col_1,col_2,col_3,col_4,col_5,matrix_upper[1000][7]={},matrix[1000][7]={},matrix2[6][7]={},matrix_top[6][7]={},matrix_low[6][7]={},count=0,type[10][2]={};
double w_count=0,f_count=0,W_count=0,F_count=0,d_count=0,D_count=0,l_count,L_count,E_count=0,e_count=0,H_count=0,h_count=0,damage[10][2]={},recovery_output[10][2]={},recovery[10][2]={},attack[10][2]={};

void initialization_matrix2();
void test();
void new_matrix();
void record();
void swap();
int change(char a);
void count_stone();
void clean();
void print();
void calculate_dama_reco();
void order();

int main(){

	for(int i=0;i<6;i++){
		scanf("%s",tmp);//無用資訊
		scanf("%[^ ]%*3c%[^\n]%*c",tmp,name[i]);//name
		scanf("%[^ ]%*3c%[A-Z]",tmp,type_c[i]);//type_FirstWord
		type[i][0] = change(type_c[i][0]);//type_math
		scanf("%[^ ]%*3c%[^\n]%*c",tmp,a);
		sscanf(a,"%lf",attack[i]);//attack
		scanf("%[^ ]%*3c%[^\n]%*c",tmp,a);
		sscanf(a,"%lf",recovery[i]);//recovery
	}//六個成員輸入
	scanf("%[^\n]%*c",tmp);//無用資訊
	
	while(1){
		scanf("%s",matrix_tmp[col++]);
		for(int i=0;i<strlen(matrix_tmp[col-1]);i++){
			matrix_upper[col-1][i] = change(matrix_tmp[col-1][i]);
			matrix[col-1][i] = '\0';
		}
		if(strcmp(matrix_tmp[col-1],"------")==0) break;
	}//等著掉的圖形吃進去matrix_upper

	col = col_0 = col_1 = col_2  = col_3 = col_4  = col_5 = col-2;//上面珠子列數

	initialization_matrix2();

	for(int i=0;i<5;i++){
		scanf("%s",matrix_tmp[i]);
		for(int j=0;j<strlen(matrix_tmp[i]);j++){
			matrix[i][j] = change(matrix_tmp[i][j]);
		}
	}//目前盤面轉換成數字

	for(int a=0;a<20;a++){
		record();//計算是否可消
		clean();//消除紀錄的珠子
		swap();
		count_stone();
		new_matrix();
		initialization_matrix2();
	}
	calculate_dama_reco();
	order();
	print();
	return 0;
}







void order(){
	for(int i=0;i<5;i++){
		for(int j=i+1;j<6;j++){
			if(damage[i][0]<damage[j][0]){
				double a;
				a = damage[i][0];
				damage[i][0] = damage[j][0];
				damage[j][0] = a;
				a = recovery_output[j][0];
				recovery_output[j][0] = recovery_output[i][0];
				recovery_output[i][0] = a;
				char s[100]={};
				strcpy(s,name[j]);
				strcpy(name[j],name[i]);
				strcpy(name[i],s);
			}
		}
	}
}

void calculate_dama_reco(){
	for(int i=0;i<6;i++){
		if(type[i][0]%7==1){
			damage[i][0] = attack[i][0] * (w_count/3);
			damage[i][0] += attack[i][0] * (W_count/2);
		}
		if(type[i][0]%7==2){
			damage[i][0] = attack[i][0] * (f_count/3);
			damage[i][0] += attack[i][0] * (F_count/2);
		}
		if(type[i][0]%7==3){
			damage[i][0] = attack[i][0] * (e_count/3);
			damage[i][0] += attack[i][0] * (E_count/2);
		}
		if(type[i][0]%7==4){
			damage[i][0] = attack[i][0] * (l_count/3);
			damage[i][0] += attack[i][0] * (L_count/2);
		}
		if(type[i][0]%7==5){
			damage[i][0] = attack[i][0] * (d_count/3);
			damage[i][0] += attack[i][0] * (D_count/2);
		}
		recovery_output[i][0] = recovery[i][0] * (h_count/3);
		recovery_output[i][0] += recovery[i][0] * (H_count/2);
	}
}

void clean(){
	for(int i=0;i<5;i++){
		for(int j=0;j<6;j++){
			if(matrix2[i][j]!=0){
				matrix[i][j]=0;
			}
		}
	}//消除盤面上的可消除符石
}

void new_matrix(){
	for(int i=0;i<6;i++){
		for(int j=4;0<=j;j--){
			if(0<=col_0 && matrix[j][i]==0 && i==0){
				matrix[j][i] = matrix_upper[col_0--][i];
			}
			if(0<=col_1 && matrix[j][i]==0 && i==1){
				matrix[j][i] = matrix_upper[col_1--][i];
			}
			if(0<=col_2 && matrix[j][i]==0 && i==2){
				matrix[j][i] = matrix_upper[col_2--][i];
			}
			if(0<=col_3 && matrix[j][i]==0 && i==3){
				matrix[j][i] = matrix_upper[col_3--][i];
			}
			if(0<=col_4 && matrix[j][i]==0 && i==4){
				matrix[j][i] = matrix_upper[col_4--][i];
			}
			if(0<=col_5 && matrix[j][i]==0 && i==5){
				matrix[j][i] = matrix_upper[col_5--][i];
			}			
		}
		col--;
	}
}

void record(){
	for(int i=0;i<5;i++){
		for(int j=0;j<6;j++){
			if(i<3){
				if((matrix[i][j]%7)==(matrix[i+1][j]%7)){
					if((matrix[i][j]%7)==(matrix[i+2][j]%7)){
						if(i<=1){
							if((matrix[i][j]%7)==(matrix[i+3][j]%7)){
								if(i==0){
									if((matrix[i][j]%7)==(matrix[i+4][j]%7)){
										matrix2[i+4][j]=matrix[i+4][j];
									}
								}
								matrix2[i+3][j]=matrix[i+3][j];
							}
						}
						matrix2[i+2][j]=matrix[i+2][j];
						matrix2[i+1][j]=matrix[i+1][j];
						matrix2[i][j]=matrix[i][j];
					}
				}		
			}//直
			if(j<4){
				if((matrix[i][j]%7)==(matrix[i][j+1]%7)){
					if((matrix[i][j]%7)==(matrix[i][j+2]%7)){
						if(j<=2){
							if((matrix[i][j]%7)==(matrix[i][j+3]%7)){
								if(i<=1){
									if((matrix[i][j]%7)==(matrix[i][j+4]%7)){
										if(i==0){
											if((matrix[i][j]%7)==(matrix[i][j+4]%7)){
												matrix2[i][j+5]=matrix[i][j+5];
											}
										}
										matrix2[i][j+4]=matrix[i][j+4];
									}
								}
								matrix2[i][j+3]=matrix[i][j+3];
							}
						}
						matrix2[i][j+2]=matrix[i][j+2];
						matrix2[i][j+1]=matrix[i][j+1];
						matrix2[i][j]=matrix[i][j];
					}
				}		
			}//橫
		}
	}//record
}

int change(char a){
	switch(a){
		case 'w': return 1;
		case 'f': return 2;
		case 'e': return 3;
		case 'l': return 4;
		case 'd': return 5;
		case 'h': return 6;
		case 'W': return 8;
		case 'F': return 9;
		case 'E': return 10;
		case 'L': return 11;
		case 'D': return 12;
		case 'H': return 13;
	}
	return 0;
}

void test(){
	for(int i=0;i<5;i++){
		for(int j=0;j<6;j++){
			printf("%d",matrix[i][j]);
		}
		printf("\n");
	}
}

void swap(){
	for(int j=0;j<6;j++){
		for(int a=0;a<6;a++){
			for(int i=1;i<5;i++){
				if(matrix[i-1][j]!=0 && matrix[i][j]==0){
					matrix[i][j] = matrix[i-1][j];
					matrix[i-1][j] = 0;
				}
			}
		}
	}
}

void initialization_matrix2(){
	for(int i=0;i<5;i++){
		for(int j=0;j<6;j++){
			matrix2[i][j]=0;
		}
	}//初始matrix2
}

void count_stone(){
	for(int i=0;i<5;i++){
		for(int j=0;j<6;j++){
			if(matrix2[i][j]==1) w_count++;
			if(matrix2[i][j]==2) f_count++;
			if(matrix2[i][j]==3) e_count++;
			if(matrix2[i][j]==4) l_count++;
			if(matrix2[i][j]==5) d_count++;
			if(matrix2[i][j]==6) h_count++;	
			if(matrix2[i][j]==8) W_count++;
			if(matrix2[i][j]==9) F_count++;
			if(matrix2[i][j]==10) E_count++;
			if(matrix2[i][j]==11) L_count++;
			if(matrix2[i][j]==12) D_count++;
			if(matrix2[i][j]==13) H_count++;			
		}
	}//計算符石個數
}

void print(){
	printf("-------------------------------------------\n");
	for(int i=0;i<6;i++){
		printf("| %-39s |\n",name[i]);
		printf("| Damage : %-10.0f| Recovery : %-8.0f|\n",damage[i][0],recovery_output[i][0]);
		printf("-------------------------------------------\n");
	}
}
