#include <stdio.h>

void main() {
	
	int c;
	int arr[26];

	for (int i=0; i<26; i++) arr[i] = 0;

	while ((c=getchar()) != EOF) {
		if		(c >= 65 && c <= 90)	++arr[c-65];
		else if	(c >= 97 && c <= 122)	++arr[c-97];	
	}
	printf("\nHistogram of input characters");
	for (int i=0; i<26; i++) printf("\n\t%c: %d", i+97, arr[i]);

	printf("\nend of the program");
}
