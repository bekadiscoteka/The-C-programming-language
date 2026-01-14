#include <stdio.h>

#define UPPER   300
#define LOWER   0
#define STEP    20


// printing in reverse order 
main () {   
// (5.0 / 9.0) * (f-32);
    int fahr; 
    printf("celsuis to fahrenheit");
    for (fahr = UPPER; fahr >= LOWER; fahr -= STEP) 
        printf("%3d\t%6.1f\n", fahr, (5.0 / 9.0) * (fahr-32));
    printf("end of the program"); 
}
