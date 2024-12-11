#include <stdio.h>
#include <limits.h>

int main(){
	long long B1, G1, C1, B2, G2, C2, B3, G3, C3;
	int dic;
	while(scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld", &B1, &G1, &C1, &B2, &G2, &C2, &B3, &G3, &C3) != EOF){
		long long result[6] = {}, min = INT_MAX;
		for(int i = 0; i < 6; ++i){
			if(i == 0){
				result[i] = G1+C1+B2+G2+B3+C3;
				if(result[i] < min){
					min = result[i];
					dic = i;
				}
			}else if(i == 1){
				result[i] = G1+C1+B2+C2+B3+G3;
				if(result[i] < min){
					min = result[i];
					dic = i;
				}
			}else if(i == 2){
				result[i] = B1+G1+C2+G2+B3+C3;
				if(result[i] < min){
					min = result[i];
					dic = i;
				}
			}else if(i == 3){
				result[i] = G1+B1+B2+C2+G3+C3;
				if(result[i] < min){
					min = result[i];
					dic = i;
				}
			}else if(i == 4){
				result[i] = B1+C1+C2+G2+B3+G3;
				if(result[i] < min){
					min = result[i];
					dic = i;
				}
			}else if(i == 5){
				result[i] = B1+C1+B2+G2+G3+C3;
				if(result[i] < min){
					min = result[i];
					dic = i;
				}
			}
		}
		if(dic == 0){
			printf("BCG %lld\n", min);
		}else if(dic == 1){
			printf("BGC %lld\n", min);
		}else if(dic == 2){
			printf("CBG %lld\n", min);
		}else if(dic == 3){
			printf("CGB %lld\n", min);
		}else if(dic == 4){
			printf("GBC %lld\n", min);
		}else if(dic == 5){
			printf("GCB %lld\n", min);
		}
	}
	return 0;
} 
