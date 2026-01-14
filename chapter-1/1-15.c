// celsius to fahrenheit
#include <stdio.h>

// function prototype

float get_fahr(float celsius);

void main() {
   float c, f;
   int upper, lower, step;

   lower = 0;
   step = 20;
   upper = 300;
   c = lower;

   while (c <= upper) {
       f = get_fahr(c); //((9.0 * c) / 5.0) + 32.0;
       printf("%6.0f\t%6.1f\n", c, f);
       c += step;
   }
}

float get_fahr(float celsius) { // i experimented to remove braces and it doesn't seem to work as loop block :)
	return ((9.0 * celsius) / 5.0) + 32.0;
}
