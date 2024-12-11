# include <stdio.h>

int main(){
	int Input[3] = {}, Rmax = 0; // Input[3] = {L, H, R}
	float mid;
	int x[100020] = {}, y[100020] = {};
	while(scanf("%d", &Input[0]) != EOF){
		for(int j = 1; j <= 2; ++j)
			scanf("%d", &Input[j]);
		if(Input[2] > Rmax)
			Rmax = Input[2];
		for(int i = 10*Input[0]; i <= 10*Input[2]; ++i){
//			if(x[i] == 0){
//				x[i] = 1;
				if(y[i] < Input[1]){
					y[i] = Input[1];
//				}
			}
		}
	}

//	for(int i = 0; i <= R; ++i)
//		printf("%d ", y[i]);
//	printf("\n");
	if(y[0] != 0){
		printf("0 %d ", y[0]);
	}
	for(int i = 1; i <= 10*Rmax + 1; ++i){
		mid = (float)(y[i] + y[i-1]) / 2.0;
//		printf("mid: %f\n", mid);

		if(y[i] != y[i-1]){
			if(mid < y[i-1]){
				printf("%d %d ", (i-1) / 10, y[i]);
				continue;
			}
			printf("%d %d ", i / 10, y[i]);
		}
	}
	
	return 0;
}

