#include <stdio.h>
#define MAXSIZE 1000
#define FAIL 0
#define SUCCESS 1

int get_prog(char arr[], int size);

int line=0, column=0;  // just practising external variables ;)

void main(void) {

	extern int line, column;

	char program[MAXSIZE];
	int status;

	while (1) { 
		if (get_prog(program, MAXSIZE) == SUCCESS) 
			printf("SUCCESS! %s\n", program);
		else 
			printf("\nsyntax error, line %d, column %d\n", line, column);
	}

}

int get_prog(char arr[], int size) {
	int c=0, i=0;

	extern int line, column;
	line = 0;
	column = 0;

	int stack[MAXSIZE];
	int stack_index=0;

	while ((c=getchar()) != EOF && i < size) {
		arr[i++] = c;			

		if (c == '\"' || c == '\'') { 
			char temp = c;
			arr[i++] = c;
			while ((c=getchar()) != temp) {
				if (c == EOF) 
					return FAIL;
				else if (c == '\\') { //automatically skip the next character
					arr[i++] = c;
					c=getchar();
				}
				arr[i++] = c;
			}
			arr[i++] = c;
		}

		else if (c == '(' || c== '{' || c=='[') 
			stack[++stack_index] = c;
		else if (c == ')' || c=='}' || c== ']')
			if (
				stack_index > 0 &&
				(stack[stack_index] == c-1 || stack[stack_index] == c-2)
			) 
				stack_index--;
			else 
				return FAIL;
	}

	arr[i] = '\0';
	

	return SUCCESS;
}
