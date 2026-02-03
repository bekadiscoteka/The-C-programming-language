#include <stdio.h>
#define swap(t, x, y) {t temp = x; x = y; y = temp;}

int main() {
    int first = 8;
    int second = 9;
    swap(int, first, second);
    printf("first = %d, second = %d", first, second);
} 


