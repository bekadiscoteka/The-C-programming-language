#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "calc.h"
static double stack[MAXSIZE];
static int stack_ptr=0;

double push(double data) {
	if (stack_ptr < MAXSIZE) 
		stack[stack_ptr++] = data;
	else 
		printf("\nStack overflow\n");
	return data;
}

double pop(void) {
	return (stack_ptr > 0) ? stack[--stack_ptr] : 0;
}

double top(void) {
	return (stack_ptr > 0) ? stack[stack_ptr-1] : 0;
}

short int is_empty(void) {
	return (stack_ptr > 0) ? 0 : 1;
}

short int top_dup(void) {
	if (stack_ptr > 0) {
		push(top());
		return 0;
	}
	else return 1;
}

short int top_swap(void) {
	if (stack_ptr > 1) {
		double temp0 = pop();
		double temp1 = pop();
		push(temp0);
		push(temp1);
		return 0;
	}

	else return 1;
}

void clear(void) {
	stack_ptr = 0;
}
