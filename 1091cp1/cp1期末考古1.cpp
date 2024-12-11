#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
	char str[100000] = {};
	fgets(str, 100000, stdin);
	strlwr(str);
	str[0] = toupper(str[0]);
	printf("%s\n", str);
	return 0;
} 
