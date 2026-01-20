#include <stdio.h>

int c_bitcount(unsigned int x);

int main(void) {
	printf("%d", c_bitcount(0xff));
}

int c_bitcount(unsigned int x) {
	int i=0;
	while (x != 0) {
		x &= x-1;	
		i++;
	}
	return i;
}












