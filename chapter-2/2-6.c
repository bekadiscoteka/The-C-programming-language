#include <stdio.h>

int setbits(int x, int p, int n, int y);

void main(void) {
	printf("result: %d", setbits(240, 2, 3, 7));
	getchar();		
}

int setbits(int x, int p, int n, int y) {
	int shift = p+1-n;
	int x_mask = ~(~0 << n) << shift;
	int y_mask = ~x_mask;
	return (x_mask | x) & (y_mask | (y << shift));
}













