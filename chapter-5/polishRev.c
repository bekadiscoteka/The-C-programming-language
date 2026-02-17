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
						
						do {
							if ((b = s_pop()) == ')')
								parenthc++;
							if (b == '(')
								parenthc--;
							temp_push(b);
						} while (parenthc > 0);

						temp_push(*c);

						do {
							if ((b = s_pop()) == ')')
								parenthc++;
							if (b == '(')
								parenthc--;
							temp_push(b);
						} while (parenthc > 0);

						temp_push('(');	
							
						do {
							if ((a = temp_pop()) == '(')
								parenthc++;
							if (a == ')')
								parenthc--;
							s_push(a);
						} while (parenthc > 0);	

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
	while (!s_isempty()) {
		putchar(s_pop());
		putchar('\n');
	}
	getchar();
}
