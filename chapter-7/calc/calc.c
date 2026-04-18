#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define STACKSIZE 100

#define perf(operator) {\
	b = pop(&s);\
	a = pop(&s);\
	push(&s, (a operator b));\
}
typedef struct {
	float stack[STACKSIZE];
	float* sp;
	float* end;
} Stack;

void stack_init(Stack* s) {
	s->sp = s->stack;
	s->end = s->stack + STACKSIZE;
}

Stack* push(Stack* s, float n) {
	if (s->sp < s->end) 
		*(s->sp++) = n;
	else 
		printf("Stack overflow\n");
	return s;
}

float top(const Stack* s) {
	return *(s->sp - 1);
}

int isempty(const Stack* s) {
	if (s->sp == s->stack) 
		return 1;
	else 
		return 0;
}

float pop(Stack* s) {
	if (s->sp > s->stack) 
		return *--(s->sp);
	else 
		printf("\nStack underflow\n");
	return 0;
}

Stack* clear(Stack* s) {
	s->sp = s->stack;
	return s;
}

int strlistcmp(int listc, char* t, ...) {
	va_list a;
	va_start(a, t);
	
	for (int i = 0; i < listc; i++) {
		char* item = va_arg(a, char*);
		if (strcmp(item, t) == 0)
			return i;
	}

	va_end(a);
	return -1;
}
void sayHello(void) {
	char str[] = {
		"REVERSE POLISH CALCULATOR\n"
		"To see manual: help, HELP"
	};

	printf("%s\n", str);
}

void help_section(void) {
	char str[] = {
	"Expected reverse-polish calculator;\n\
EB01: numbers are added into stack, when operation is performed on top 2 numbers of stack; \n\
EB02: it supports floating point number format (32 bit);\n\
EB03: it supports minus sign format;\n\ 
EB04: supported operations: * + - / \n\
EB05: [ENTER] is for updating stack\n\
CONOPS:\n\
	input: 5 5 6 + [enter]\n\
	stack: 5 11 \n\
	input: 5.1 5 6 + - [enter]\n\
	stack: -5.9\n\ 
	input: 1 1 -2.1 + 1 * [enter]\n\
	stack: -3.1\n\ 
	input: 1 1 + TOP [ENTER]\n\
	output: 2\n\
EB06: also supports special commands: \n\
	General:\n\
	CLEAR - for clearing the stack \n\
	TOP - get top element\n\
	DUP - duplicate top element	\n\
	SWAP - swap top 2 element \n\
	EXIT - quit the program \n\
	Math:\n\
	SIN - sinus of top number\n\
	COS - cosine of top number\n\
	EXP - e powered by top number\n\
	POW - power operation of top 2 numbers\n\
==================================================\n"
	};
	printf("\f%s", str);
}

int main(void) {
	
	sayHello();
	enum {IDLE, CMD, OPER, SPACE, NUM} state = IDLE;
	Stack s;
	stack_init(&s);
	int c;
	char temps[100];
	float a, b, tempf;
	while (1) {
		switch (state) {
			case IDLE: 
				c = getchar();
				if (isdigit(c)) {
					state = NUM;
				}
				else if (isalpha(c)) 
					state = CMD; 
				else if (isspace(c)) 
					state = SPACE;
				else if (c == EOF) 
					return 0;
				else 
					state = OPER;
				break;
			case NUM: 
				ungetc(c, stdin);
				tempf = 0;
				scanf("%f", &tempf);
				push(&s, tempf);
				state = IDLE;
				break;
			case CMD: 
				state = IDLE;
				ungetc(c, stdin);	
				scanf("%s", temps); 
				c = getchar();
			
				enum {CLEAR, TOP, DUP, SWAP, EXIT, SIN, COS, EXP, POW, help, HELP} searchRes;
				searchRes = strlistcmp(
					11, temps,
					// gen
					"CLEAR",
					"TOP",
					"DUP",
					"SWAP",
					"EXIT",

					// math		
					"SIN",
					"COS",
					"EXP",
					"POW",
					"help",
					"HELP"
				);

				switch(searchRes) {
					case HELP: case help:
						help_section();
						break;
					case EXIT:
						printf("Goodbye!\n");
						return 0;
						break;
				}
			
				if (isempty(&s)) {
					printf("Stack is empty\n");
					break;
				}

				switch (searchRes) {
					case CLEAR:
						clear(&s);
						break;
					case TOP:
						printf("TOP: %f\n", top(&s));
						break;
					case DUP: 
						push(&s, top(&s));
						break;
					case SWAP:
						if ((s.sp - s.stack) < 2) {
							printf("Not enough elements on stack\n");
							break;
						}
						b = pop(&s); a = pop(&s);
						push(&s, b); push(&s, a);
						break;
					case SIN:
						push(&s, sin(pop(&s)));
						break;
					case COS:
						push(&s, cos(pop(&s)));
						break;
					case EXP:
						push(&s, exp(pop(&s)));
						break;
					case HELP: case help:
						help_section();
						break;

					case POW:
						state = IDLE;
						a = pop(&s); b = pop(&s);
						push(&s, pow(a, b));
						break;
					default:
						printf("Command: %s is not supported\n", temps);
						break;
				}		

				break;
			case SPACE:
				while (isspace(c = getchar()))
				   ;
				ungetc(c, stdin);
				state = IDLE;
				break;	
			case OPER:
				state = IDLE;
				if ((s.sp - s.stack) < 2) {
					printf("Not enough elements on stack\n");
					break;
				}
				switch (c) {
					case '+':
						perf(+);
						break;
					case '-':
						perf(-);
						break;
					case '/':
						perf(/);
						break;
					/*
					case '%':
						perf(%);
						break;
					*/
					case '*':
						perf(*);
						break;
					default:
						printf("Operation %c is not supported\n", c);
						break;
				}
				break;
		}
	}
}
