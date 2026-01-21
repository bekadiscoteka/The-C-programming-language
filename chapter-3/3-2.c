#include <stdio.h>

void c_escape(char dst[], char src[]);

void main() {
	char arr[1000];
	c_escape(arr, "Escape test \n \" \\ \' lala \t");
	printf("%s", arr); 
}


void c_escape(char dst[], char src[]) {
	int dst_i = 0;
	for (int i=0; src[i] != '\0'; ++i) {
		switch(src[i]) {
			case '\n': 
				dst[dst_i++] = '\\';
				dst[dst_i++] = 'n';
				break;
			case '\t':
				dst[dst_i++] = '\\';
				dst[dst_i++] = 't';
				break;
			case '\\': 
				dst[dst_i++] = '\\';
				dst[dst_i++] = '\\';
				break;
			case '\'':
				dst[dst_i++] = '\\';
				dst[dst_i++] = '\'';
				break;
			case '\"':
				dst[dst_i++] = '\\';
				dst[dst_i++] = '\"';
				break;
			default: 
				dst[dst_i++] = src[i];
				break;
		}
	}
}	
