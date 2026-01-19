#include <stdio.h>
#define MAXSIZE 1000
void c_squeeze(char s1[], char s2[]);
int c_getline(char dest[], int maxsize);

void main(void) {
	char s1[MAXSIZE], s2[MAXSIZE];	
	char user_resp[5];
	short int state=1;
	int sizes1, sizes2;
	while (state) {
		printf("Enter the s1 enter s2\n");
		sizes1 = c_getline(s1, MAXSIZE);
		sizes2 = c_getline(s2, MAXSIZE);
		if ((sizes1 > 0) && (sizes2 > 0)) {
			c_squeeze(s1, s2);
			printf("s1: %s\n", s1);
		}
		printf("Would you like to continue? (y/n): ");
		c_getline(user_resp, 5);
		if (user_resp[0] != 'y')
			state = 0;
	}
}

void c_squeeze(char s1[], char s2[]) {
	int s=0;
	short int contains;
	for (int i=0; s1[i] != '\0'; i++) {
		contains=0;
		for (int j=0; s2[j] != '\0' && contains == 0; j++) 
			if (s1[i] == s2[j])
				contains = 1;

		if (!contains) 
			s1[s++] = s1[i];
	}
	s1[s] = '\0';
}

int c_getline(char dest[], int maxsize) {
	int i=0, c;

	for (i=0; (c=getchar()) != '\n' ; ++i) {
		if (i < maxsize-1) {
			if (c == EOF) 
				return 0;
			dest[i] = c;
		}
	}
	dest[i] = '\0';
	return i;
}













