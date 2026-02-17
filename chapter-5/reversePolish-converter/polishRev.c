#include <stdio.h>
#include <ctype.h>
#define STACK_MAXSIZE 1000

char s_stack[STACK_MAXSIZE];
char *s_stackp = s_stack;

char tempstack[STACK_MAXSIZE];
char *tempstackp = tempstack;


char temp_pop() {
	if (tempstackp == tempstack) 
		printf("\nstack is empty\n");
	else 
		return *--tempstackp;
}

char s_pop() {
	if (s_stackp == s_stack) 
		printf("\nstack is empty\n");
	else 
		return *--s_stackp;
}

void temp_push(char c) {
	if (tempstackp - tempstack > STACK_MAXSIZE) 
		printf("\nstack overflow\n");
	else 
		*tempstackp++ = c;	
}

void s_push(char c) {
	if (s_stackp - s_stack > STACK_MAXSIZE) 
		printf("\nstack overflow\n");
	else 
		*s_stackp++ = c;
}

int s_isempty(void) {
	if (s_stackp == s_stack) 
		return 1;
	return 0;
}

int temp_isempty(void) {
	return tempstackp == tempstack;
}

void s2temp(void) {
	char c;
	int parenthc=0;
	do {
		if ((c = s_pop()) == ')')
			parenthc++;
		if (c == '(')
			parenthc--;
		temp_push(c);
	} while (parenthc > 0);
}

void temp2s(void) {
	
	char c;
	int parenthc=0;

	do {
		if ((c = temp_pop()) == '(')
			parenthc++;
		if (c == ')')
			parenthc--;
		s_push(c);
	} while (parenthc > 0);	

}

int main(int argc, char *argv[]) {
	while (--argc > 0) {
		for (char* c = *++argv; *c != '\0'; ++c) {
			if (isdigit(*c)) 
				s_push(*c);
			else {
				char a, b;

				int parenthc = 0;
				
				
				
				switch (*c) {
					case '*': 
					case '+': 
					case '-': 
					case '/':
						
						temp_push(')');					

						s2temp();

						temp_push(*c);

						s2temp();

						temp_push('(');	
						
						temp2s();	
						
						break;
					default:
						printf("\nundefined operation: ");
						putchar(*c);
						putchar('\n');
						break;
				}
			}
		}
	}		
	s2temp();

	while (!temp_isempty()) {
		putchar(temp_pop());
		putchar(' ');
	}

	getchar();
}
