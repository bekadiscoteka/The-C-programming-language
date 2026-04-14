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

int main(void) {
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
					printf("number\n");
				}
				else if (isalpha(c)) 
					state = CMD; 
				else if (c == ' ' || c == '\t') 
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
				ungetc(c, stdin);	
				scanf("%s", temps); 
				c = getchar();
			
				enum {CLEAR, TOP, DUP, SWAP, EXIT, SIN, COS, EXP, POW} searchRes;
				searchRes = strlistcmp(
					9, temps,
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
					"POW"
				);
			
				if (searchRes == EXIT) {
					printf("Goodbye!\n");
					return 0;
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
					default:
						printf("Command: %s is not supported\n", temps);
						break;
				}		

			
				state = IDLE;
				break;
			case SPACE:
				while ((c = getchar()) == ' ' || c == '\t' || c == '\n')
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
