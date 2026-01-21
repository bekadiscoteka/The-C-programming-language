#include <stdio.h>
#include <ctype.h>

void expand(char dst[], char src[]);
int casetest(char, char);

int main(void) {
	char s1[100];
	expand(s1, "test a-b-c  A-n  A-Z a-9-1");
	printf("expanded: %s", s1);
}

int casetest(char a, char b) {
	return (isupper(a) && isupper(b)) || (islower(a) && islower(b));
}

void expand(char dst[], char src[]) {
	int dst_i, i, nxt, prev;
	for (dst_i=0, i=0, nxt=i+1, prev=i-1; 
		src[i] != '\0'; 
		prev = i++, nxt=i+1
	) {
		switch(src[i]) {
			case '-': 
				if (
					( isalpha(src[nxt]) && isalpha(src[prev]) && (i > 0)
					&& casetest(src[nxt], src[prev])) 
					|| ( isdigit(src[nxt]) && isdigit(src[prev]) && (i > 0) )
				) {
					for (int j=src[prev]+1; j < src[nxt]; ++j)
						dst[dst_i++] = j;
					for (int j=src[prev]-1; j > src[nxt]; --j)
						dst[dst_i++] = j;
				}
				else 
					dst[dst_i++] = src[i];
				break;
					
			default: dst[dst_i++] = src[i];
		}
	}
	dst[dst_i] = '\0';
}
