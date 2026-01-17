#include <stdio.h>
#define MAXSIZE 1000
#define FAIL 0
#define SUCCESS 1
#define IDLE 0
#define STAR 1


int get_prog(char arr[], int size);
void set_lc(char c);

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

void set_lc(char c) {
	extern int line, column;

	if (c == '\n') {
		line++;
		column=0;
	}
	else 
		column++;
}

int get_prog(char arr[], int size) {
	int c=0, i=0;

	extern int line, column;
	line = 0;
	column = 0;

	int stack[MAXSIZE];
	int stack_index=0;
	int comment_state = IDLE;

	while ((c=getchar()) != EOF && i < size) {
		arr[i++] = c;			

		if (c == '/') {
			c=getchar();
			arr[i++] = c;
			set_lc(c);

			if (c == '*') {
				while (!((c=getchar()) == '/' && comment_state == STAR)) {
					if (c == EOF)
						return FAIL;
					arr[i++] = c;
					set_lc(c);
					if (comment_state == STAR)
						comment_state = IDLE;
					else if (c == '*') 
						comment_state = STAR;
				}
				arr[i++] = c;
				set_lc(c);
			}
			else if (c == '/') {
				while ((c=getchar()) != '\n') {
					if (c == EOF) return SUCCESS;
					arr[i++] = c;
					set_lc(c);
				}
				arr[i++] = c;
				set_lc(c);
			}
		}
		else if (c == '\"' || c == '\'') { 
			char temp = c;
			while ((c=getchar()) != temp) {
				arr[i++] = c;
				set_lc(c);

				if (c == EOF) 
					return FAIL;
				else if (c == '\\') { //automatically skip the next character
					c=getchar();
					arr[i++] = c;
					set_lc(c);
				}
			}
			arr[i++] = c;
			set_lc(c);
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
		set_lc(c);
	}

	arr[i] = '\0';
	

	return SUCCESS;
}
