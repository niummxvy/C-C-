#include <stdio.h>

int Collatz(int x){
	if(x % 2 == 0) return x /= 2;
  	else return 3*x + 1;
}

int main(){
	int N;
  	scanf("%d", &N);
  	for(int i = 0; i < N; ++i){
      	int x;
      	printf("%d ", x);
      	scanf("%d", &x);
    	while(Collatz(x) != 1){
          	x = Collatz(x);
        	printf("%d ", x);
        }
      printf("%d\n", Collatz(x));
    }
  
	return 0;
}
