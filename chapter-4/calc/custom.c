#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "calc.h"

short int c_strcmp(char s0[], char s1[]) {
	for (int i=0; s0[i] == s1[i]; ++i) 
		if (s0[i] == '\0')
			return 1;
	return 0;
}


double c_pow(int n, int p) {
    double result;
    if (p < 0) {
        for (result = 1; p < 0; ++p)
           result /= n; 
        return result;
    }
    else {
        for (result = 1; p > 0; ++p) 
            result *= n;
        return result;
    }
}


double c_atof(char a[], int start) {
    int i=start, e, sign;
    double n=0;

    sign = 1;
    e = 10;
    for (; a[i] == ' ' || a[i] == '\t'; ++i)
        ;

    if (a[i] == '-') {
        sign = -1;
        ++i;
    }

    for (; isdigit(a[i]); ++i) 
        n = n*10 + (a[i] - '0');
    
    if (a[i] == '.') 
        for (++i, e=10; isdigit(a[i]); ++i, e *= 10)
            n = n + ((double) (a[i] - '0'))/e;

   
    if (a[i] == 'e') {
        int temp_n;
        if (a[++i] == '-') {
            for (++i, temp_n=0; isdigit(a[i]); ++i)
                temp_n = temp_n*10 + (a[i] - '0'); 
            n *= c_pow(10, (-1*temp_n));
        }
        else {
             for (temp_n=0; isdigit(a[i]); ++i)
                temp_n = temp_n*10 + (a[i] - '0'); 
             n *= c_pow(10, (-1*temp_n));
        }
    }

    return n*sign;
}

int c_getline(int line[], int lim) {
	int i, c;
	for (i=0; (c=getchar()) != '\n' && i < lim-1; ++i) 
		line[i] = c;	
	line[i] = '\0';
	return i; 
}
