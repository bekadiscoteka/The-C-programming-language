#include <stdio.h>
#include <ctype.h>

double c_atof(char a[]);
double c_pow(int n, int p);

int main(void) {
    printf("%e", c_atof("123.45"));
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


double c_atof(char a[]) {
    int i, aexp, e, n, sign;
    sign = 1;
    e = aexp = n = i = 0;
    for (; a[i] == ' '; ++i)
        ;

    if (a[i] == '-') {
        sign = -1;
        ++i;
    }

    for (; isdigit(a[i]); ++i) 
        n = n*10 + a[i] - '0';
    
    if (a[i] == '.') 
        for (++i; isdigit(a[i]); ++i, --e)
            n = n*10 + a[i] - '0';

   
    if (a[i] == 'e') {
        if (a[++i] == '-') {
            for (++i; isdigit(a[i]); ++i)
                aexp = aexp*10 + (a[i] - '0');
            aexp *= -1;
            e += aexp;
                
        }

        else {
            
            for (; isdigit(a[i]); ++i)
                aexp = aexp*10 + (a[i] - '0');
            e += aexp;


        }
        
    }


    return c_pow(10, e) * (double) (sign * n);
}
