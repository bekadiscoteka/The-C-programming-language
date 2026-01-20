#include <stdio.h>

unsigned int rightrot(unsigned int x, unsigned int n);
	

void main(void) {
	printf("%u\n", rightrot(170, 1));         // 85
	printf("%u\n", rightrot(129, 2));         // 96
	printf("%u\n", rightrot(0, 5));           // 0
	printf("%u\n", rightrot(240, 0));         // 240
	printf("%#x\n", rightrot(0x12345678, 32));// 0x12345678
	printf("%#x\n", rightrot(0x80000000, 33));// 0x40000000
	printf("%#x\n", rightrot(1, 1));          // 0x80000000
	printf("%#x\n", rightrot(0xAAAAAAAA, 1));// 0x55555555

	getchar();		
}

unsigned int rightrot(unsigned int x, unsigned int n) {
	unsigned int w = sizeof(unsigned int) * 8;
	
	n %= w;

	if (n == 0)
		return x;
	
	return (x >> n) | (x << (w-n));
}














