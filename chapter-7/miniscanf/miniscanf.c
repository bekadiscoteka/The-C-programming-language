#include <stdio.h>
#include <stdarg.h>

#define assign(arg, type) {\
	type *temp = va_arg(arg, type*);\
	scanf("%" #type, temp);\
}\

/*
stExp: 
	stakeholders: me, C developers, Brian
	read from standard input, based on the format fmt
 */

void miniscanf(char *fmt, ...) {
	enum {IDLE, IDENT} state = IDLE;
	va_list a;
	va_start(a, fmt);
	
	char c;	
	while (c = *fmt++) {
		switch (state) {
			case IDLE: 
				if (c == '%')
					state = IDENT;
				else if (c != getchar())
					return 0;
				break;
			case IDENT:
				switch (c) {
					case 'd': 
						assign(a, int);	
						break;
					case 'f':
						assign(a, float);
						break;
					case 'e':
						assign(a, double);
						break;
					case 's':
						assign(a, char*);
						break;
					default:
						printf("There is no such type %c", c);
						break;
				}
				state = IDLE;
				break;
		}
	}


	va_end(a);
}

int main(void) {
	int d;
	float f;
	miniscanf("%d float %f", &d, &f);
	printf("\nD = %d\nF = %f", d, f);
	return 0;
}
