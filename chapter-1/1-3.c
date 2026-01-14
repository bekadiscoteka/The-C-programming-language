#include <stdio.h>

int main () {   
    int lower, upper, step;
    float f, c;

    lower = 0;
    upper = 300;
    step = 20;
    f = lower;

    printf("TEMPERATURE CONVERSION"); 
    while (f <= upper) {
        c = (5.0 / 9.0) * (f-32);
        printf("%3.0f\t%6.1f\n", f, c);
        f = f + step; 
    }
}
