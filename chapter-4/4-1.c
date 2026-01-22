
#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */
int c_getline(char line[], int max);
int strindex(char source[], char searchfor[]);
/* find all lines matching pattern */
int strindex(char[], char[]);

int main()
{
    printf("%d", strindex("hello world hello", "hello"));
    return 0;
}

int strindex(char s[], char t[])
{
   int i, j, k;
   int rightmost = -1;
   for (i = 0; s[i] != '\0'; i++) {
       for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
           ;
       if (k > 0 && t[k] == '\0')
           rightmost = i;
   }
   return rightmost;
}
