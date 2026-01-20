#include <stdio.h>
#define MAXSIZE 1000
int c_any(char s1[], char s2[]);

int c_getline(char dest[], int maxsize);

void main(void) {
	char s1[MAXSIZE], s2[MAXSIZE];	
	char user_resp[5];
	short int state=1;
	int first;
	int sizes1, sizes2;
	while (state) {
		printf("Enter the s1 enter s2\n");
		sizes1 = c_getline(s1, MAXSIZE);
		sizes2 = c_getline(s2, MAXSIZE);
		if ((sizes1 > 0) && (sizes2 > 0)) {
			if ((first=c_any(s1, s2)) >= 0)
				printf("first location index: %d\n", first);
			else 
				printf("there is no similarity\n");
			
		}
		printf("Would you like to continue? (y/n): ");
		c_getline(user_resp, 5);
		if (user_resp[0] != 'y')
			state = 0;
	}
}

int c_any(char s1[], char s2[]) {
	for (int i=0; s1[i] != '\0'; i++) 
		for (int j=0; s2[j] != '\0'; j++) 
			if (s1[i] == s2[j])
				return i;
	return -1;
}

int c_getline(char dest[], int maxsize) {
	int i=0, c;

	while ((c=getchar()) != '\n') {
		if (i < maxsize) {
			if (c == EOF) 
				return 0;
			dest[i++] = c;
		}
	}

	dest[i] = '\0';
	return i;
}


