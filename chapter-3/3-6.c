#include <stdio.h>
#include <limits.h>

void itoa(int number, char str[], int min);
void reverse(char arr[]);

int main(void) {
	char arr[100];
	itoa(85, arr, 10);
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

void itoa(int number, char str[], int min) {
	unsigned int u_number = number;
	int i=0;
	int sign;
	if ((sign = number) < 0)
		u_number = (unsigned int) (-number);
	do {
		str[i++] = (u_number % 10) + '0';
	} while ((u_number /= 10) > 0);

	if (sign < 0) 
		str[i++] = '-';
	
	while (i < min)
		str[i++] = '0';
	reverse(str);
	str[i] = '\0';
}
