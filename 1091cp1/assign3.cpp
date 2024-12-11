#include <stdio.h>

int Letter2int(char c){
	int list[26] = {1, 0, 9, 8, 7, 6, 5, 4, 9, 3, 2, 2, 1, 0, 8, 9, 8, 7, 6, 5, 4, 3, 1, 3, 2, 0};
	return(list[c-'A']);
}

int char2int(char c){
	return c - '0';
}

int main() {
  	int N;
  	scanf("%d", &N);
  	for(int i = 0; i < N; ++i){
		char Letter;
		scanf(" %c", &Letter);
		int checksum = 0;
		checksum += Letter2int(Letter);
		char n[10] = {};
		for(int j = 0; j < 9; ++j) scanf("%c", &n[j]);
		checksum += 8*char2int(n[0]) + 7*char2int(n[1]) + 6*char2int(n[2]) + 5*char2int(n[3]) + 4*char2int(n[4]) + 3*char2int(n[5]) + 2*char2int(n[6]) + char2int(n[7]) + char2int(n[8]);
		checksum %= 10;
		if(checksum == 0) printf("Valid\n");
		else printf("Invalid\n");
    }
}

