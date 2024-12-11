#include <cstdio>
// WRRGGGGRGGGBBBBWW
// WRRRWWWRRBBYYYBBBY 2	
int min = 50;

int elim(char *balls, int n, int *record, int c){
	c++;
	int same = 1, rest = 0, chosen[n], count = 0;
	for(int p = 0; p < n; ++p) chosen[p] = -1;
	
	for(int i = n-1; i > 0; --i){ // backward search
		if(record[i] != 1){ // hasn't been chosen yet
			for(int j = i-1; j >= 0; --j){
				if(j != 0){
					if(record[j] != 1){ // balls[i] and balls[j] haven't been chosen yet.
						if(balls[i] == balls[j]){
							same++;
							chosen[count++] = i;
							i = j+1;
							break;
						}else{ // meet different color
							if(same < 3){
								count = count - same + 1;
								same = 1;
								for(int p = 0; p < n; ++p) chosen[p] = -1;
								i = j+1;
								break;
							}else{
								chosen[count++] = i;	
								for(int q = 0; q < n; q++){
									if(chosen[q] == -1) continue;
									record[chosen[q]] = 1;
								}
								
								int temp_min = elim(balls, n, record, c);
								min = (min < temp_min)? min : temp_min;
								
								for(int q = 0; q < n; q++){
									if(chosen[q] == -1) continue;
									record[chosen[q]] = 0;
									chosen[q] = -1;
								}
								same = 1;
								i = j+1;
								break;
							}
						}
					}
				}else{
					if(record[j] != 1){ // balls[i] and balls[j] haven't been chosen yet.
						if(balls[i] == balls[j]){
							same++;
							chosen[count++] = i;
							chosen[count++] = j;
						}
					}
						if(same < 3){
							count = count - same + 1;
							same = 1;
							for(int p = 0; p < n; ++p) chosen[p] = -1;
						}else{
							chosen[count++] = i;
							for(int q = 0; q < n; q++){
								if(chosen[q] == -1) continue;
								record[chosen[q]] = 1;
							}
							
							int temp_min = elim(balls, n, record, c);
							min = (min < temp_min)? min : temp_min;
							
							for(int q = 0; q < n; q++){
								if(chosen[q] == -1) continue;
								record[chosen[q]] = 0;
								chosen[q] = -1;
							}
							same = 1;
							i = j+1;
						}
						
					
				}
			}
		}
	}
	for(int k = 0; k < n; ++k) if(record[k] != 1) rest++;
	return (min < rest)? min : rest;
}

int main(){
	int n;
	char balls[50] = {};
	for(int i = 0; i < 50; ++i){
		scanf("%c", &balls[i]);
		if(balls[i] == '\n') break;
		n = i+1;
	}
	int record[50] = {};
	printf("%d\n", elim(balls, n, record, 0));
	
	return 0;
} 
