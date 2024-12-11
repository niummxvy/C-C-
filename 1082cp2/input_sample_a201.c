#include <stdio.h>
#include <string.h>

int main(void) {
 
 int n = 0;
 char s[2] = " ";
 char *token;
 
 // get the first number and \n
 scanf("%d\n", &n);

 for(int i=0;i<n;i++) {
  char str[1000] = {'\0'};

  fgets(str, 1000, stdin);

  // remove the \n or \r
  for(int i=0;i<strlen(str);i++){
   str[i] = (str[i] >= 32 && str[i]<= 126) ? str[i] : '\0';
  }

  token = strtok(str, s);
  // walk through other tokens
    while(token != NULL) {

       printf( "%s ", token);
       token = strtok(NULL, s);
    }
    puts("");
 }

 return 0; 
}
