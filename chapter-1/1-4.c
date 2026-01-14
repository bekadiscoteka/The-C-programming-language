// celsius to fahrenheit
#include <stdio.h>

void main() {
   float c, f;
   int upper, lower, step;

   lower = 0;
   step = 20;
   upper = 300;
   c = lower;

   while (c <= upper) {
       f = ((9.0 * c) / 5.0) + 32.0;
       printf("%6.0f\t%6.1f\n", c, f);
       c += step;
   }
}
