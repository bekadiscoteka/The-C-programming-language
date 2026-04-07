#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#define MAXPARAM 100

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
					switch (c) {
						case 'd':
							*params++ = c;
							*params = '\0';
							int tempd = va_arg(arg, int);
							printf("Inside d\n");
							printf(param, tempd);
							break;
						case 'e':
							*params++ = c;
							*params = '\0';
							double tempe = va_arg(arg, double);
							printf(param, tempe);
							break;
						case 'f':
							*params++ = c;
							*params = '\0';
							double tempf = va_arg(arg, double);
							printf( param, tempf);
							break;
						case 's':
							*params++ = c;
							*params = '\0';
							char *temps = va_arg(arg, char*);
							printf(param, temps);
							break;
						case 'c':	
							*params++ = c;
							*params = '\0';
							int tempc = va_arg(arg, int);
							printf(param, tempc);
							break;
						case 'u':
							*params++ = c;
							*params = '\0';
							unsigned int tempu = va_arg(arg, unsigned int);
							printf(param, tempu);
							break;

						default: 
							printf("there is no such specifier: %c", c);
							break;
					}
					

				}
		}
	}
	

	

}


