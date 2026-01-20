#include <stdio.h>

unsigned int bit_invert(unsigned int x, unsigned int p, unsigned int n);

void main(void) {
	printf("%d\n", bit_invert(170, 4, 3)); // 182
	printf("%d\n", bit_invert(240, 2, 3)); // 247
	printf("%d\n", bit_invert(47, 7, 2));  // 239
	printf("%d\n", bit_invert(16, 4, 1));  // 0
	printf("%d\n", bit_invert(0, 7, 8));   // 255
	printf("%d\n", bit_invert(204, 5, 4)); // 240
	printf("%d\n", bit_invert(189, 3, 2)); // 177
	getchar();		
}

unsigned int bit_invert(
		unsigned int x, 
		unsigned int p, 
		unsigned int n
	) {
	
	return x ^ (~(~0 << n) << (p+1-n));
	
}














