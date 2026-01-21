#include <stdio.h>
#include <limits.h>

void itob(int number, char str[], int base);
void reverse(char arr[]);

int main(void) {
	char arr[100];
	itob(8, arr, 2);
	printf("%s", arr);
}
void reverse(char arr[]) {
	int size;
	for (size=0; arr[size] != '\0'; size++) 
		;	
	int i, j, temp;
	for (i=0, j=size-1; i < j; ++i, --j) 
		temp = arr[i], arr[i] = arr[j], arr[j] = temp;
	
}

void itob(int number, char str[], int base) {
	unsigned int u_number = number;
	int i=0;
	int sign;
	if ((sign = number) < 0)
		u_number = (unsigned int) (-number);

	do {
		str[i++] = (u_number % base) + '0';
	} while ((u_number /= base) > 0);

	if (sign < 0) 
		str[i++] = '-';

	reverse(str);
	str[i] = '\0';
}
