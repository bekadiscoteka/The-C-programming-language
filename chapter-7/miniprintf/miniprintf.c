#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#define MAXPARAM 100

#define place_arg(type) {\
	type temp = va_arg(arg, type);\
	printf(param, temp);\
}\

typedef enum {IDLE, SPEC} States;

void miniprintf(char* fmt, ...) {
	// initializing stuff
	va_list arg;
	va_start(arg, fmt);
	//va_arg(arg, char*);
	
	char c;
	char param[MAXPARAM];
	char *params = param;
	States state = IDLE;
	while ((c=*fmt++) != '\0') {
		switch (state) {
			case IDLE:
				if (c == '%') {
					state = SPEC;
					params = param;
					*params++ = '%';
				}	
				else
				   	putchar(c);
				break;
			case SPEC:
				if (c == '.' || isdigit(c))
					*params++ = c;
				else {

					state = IDLE;
					*params++ = c;
					*params = '\0';

					switch (c) {
						case 'd':
							place_arg(int);
							break;
						case 'e': case 'f':
							place_arg(double);
							break;
						case 's':
							place_arg(char*);
							break;
						case 'c':	
							place_arg(int);
						case 'u':
							place_arg(unsigned int);
							break;
						case '%':
							printf(param);
							break;
						default: 
							printf("there is no such specifier: %c", c);
							break;
					}
					

				}
		}
	}
	
	va_end(arg);

}


int main(void) {
	miniprintf("Hello %s", ",world");
	return 0;
}
