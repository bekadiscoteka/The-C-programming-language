#include <stdio.h>
#include <ctype.h>
#define MAXSIZE 100

char buf[MAXSIZE];
int bufp=0;

char getch(void);  // compile with 4-5.c 
void ungetch(char);


void ungetch(char c) {
	bufp < MAXSIZE ? buf[bufp++] = c : printf("\nbuffer overflow\n");
}

char getch(void) {
	return bufp > 0 ? buf[--bufp] : getchar();
}

int getint(int *pn) {
     int sign=1, c;
     while (isspace(c=getch()))
         ;
     
     if (c == '-' || c == '+') {
        int temp = c;
        sign = (c == '+') ? 1 : -1; 
        c = getch();
         if (isdigit(c)) {
digit_int:
             for (*pn=0; isdigit(c); c=getch())
                 *pn = *pn * 10 + (c - '0');

             *pn *= sign;
             ungetch(c);
             return 1;
         }

         ungetch(temp);
         ungetch(c);
         return 0;
     }

     if (isdigit(c))
        goto digit_int;



     if (c == EOF) 
         return EOF;

     ungetch(c);
     return 0;    
    
 }

int getfloat(float* pn) {
     int sign=1, c;
     while (isspace(c=getch()))
         ;
     
     if (c == '-' || c == '+') {
        int temp = c;
        sign = (c == '+') ? 1 : -1; 
        c = getch();
         if (isdigit(c)) {
digit_float:
             for (*pn=0; isdigit(c); c=getch())
                 *pn = *pn * 10 + (c - '0');
             if (c == '.') 
                 for (int exp = 10; isdigit(c=getch()); exp *= 10) 
                     *pn = *pn + ( ((double)(c - '0'))/exp );

             *pn *= sign;
             ungetch(c);
             return 1;
         }

         ungetch(temp);
         ungetch(c);
         return 0;
     }

     if (isdigit(c))
        goto digit_float;



     if (c == EOF) 
         return EOF;

     ungetch(c);
     return 0;    
}

int main(void) {
    int myInt, result, getint(int*);
    float myFloat;
   
    (result = getint(&myInt)) > 0 ? printf("Found: %d", myInt) : printf("next one is EOF or not digit");

    return 0;
}

