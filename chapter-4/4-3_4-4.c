#include <stdio.h>
#include <ctype.h>
#define MAXSIZE 1000
#define NUMBER 'n'
#define CMD 'c'

double c_atof(char a[]);
double c_pow(int n, int p);

double push(double); // return value it is pushing 
double pop(void);
double top(void);
short int top_dup(void);
short int top_swap(void);
void clear(void);

short int c_strcmp(char[], char[]);

char getch(void);
void ungetch(char);
int getop(char[]);

int main(void) {
	char s[MAXSIZE];
	int type;
	double temp;
	int c;
	printf("\navailable commands:\n\tCLEAR - clearing stack\n\tTOP - get top number\n\tSWAP - swap top 2 values\n\tDUP - duplicate top value\n"); 
	printf("\tEXIT - exit program\n");
		
	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER: 
				push(c_atof(s));
				break;
			case '/': 
				temp = pop();
				push(pop() / ( temp > 0 ? temp : 1 ));
				break;
			case '*': 
				push(pop() * pop());
				break;
			case '+':
				push(pop() + pop());
				break;
			case '-':
				temp = pop();
				push(pop() - temp);
				break;
			case '%':
				temp = pop();
				push( (double) ((int)pop() % (int)temp) );
				break;
			case CMD:
				if (c_strcmp(s, "CLEAR")) {
					clear();
					printf("\nStack is cleared\n");
				}					
				else if (c_strcmp(s, "DUP")) 
					printf("\nDuplication %s", top_dup() == 0 ? "SUCCESS\n" : "FAIL\n");
				else if (c_strcmp(s, "SWAP"))
					printf("\nSwap %s\n", top_swap() == 0 ? "SUCCESS\n" : "FAIL\n");
				else if (c_strcmp(s, "TOP"))
					printf("\nTOP: %f\n", top());
				else if (c_strcmp(s, "EXIT")) {
					printf("\nGood bye!\n");
					goto exit;
				}
				else 
					printf("\nUndefined operation\n");
				break;
			default: 
				printf("\nUndefined operation\n");
				break; // skip
		}
	}
exit:
	printf("Final result = %.2f\n", pop());
	printf("Press any key to close this program");
	c = getchar();
	return 0;
}

short int c_strcmp(char s0[], char s1[]) {
	for (int i=0; s0[i] == s1[i]; ++i) 
		if (s0[i] == '\0')
			return 1;
	return 0;
}

double c_pow(int n, int p) {
    double result;
    if (p < 0) {
        for (result = 1; p < 0; ++p)
           result /= n; 
        return result;
    }
    else {
        for (result = 1; p > 0; ++p) 
            result *= n;
        return result;
    }
}


double c_atof(char a[]) {
    int i, e, sign;
    double n=0;

    sign = 1;
    i = 0;
    e = 10;
    for (; a[i] == ' ' || a[i] == '\t'; ++i)
        ;

    if (a[i] == '-') {
        sign = -1;
        ++i;
    }

    for (; isdigit(a[i]); ++i) 
        n = n*10 + (a[i] - '0');
    
    if (a[i] == '.') 
        for (++i, e=10; isdigit(a[i]); ++i, e *= 10)
            n = n + ((double) (a[i] - '0'))/e;

   
    if (a[i] == 'e') {
        int temp_n;
        if (a[++i] == '-') {
            for (++i, temp_n=0; isdigit(a[i]); ++i)
                temp_n = temp_n*10 + (a[i] - '0'); 
            n *= c_pow(10, (-1*temp_n));
        }
        else {
             for (temp_n=0; isdigit(a[i]); ++i)
                temp_n = temp_n*10 + (a[i] - '0'); 
             n *= c_pow(10, (-1*temp_n));
        }
    }

    return n*sign;
}

char buf[MAXSIZE];
int bufp=0;

void ungetch(char c) {
	bufp < MAXSIZE ? buf[bufp++] = c : printf("\nbuffer overflow\n");
}

char getch(void) {
	return bufp > 0 ? buf[--bufp] : getchar();
}

int getop(char arr[]) {
	int n=0, i=0, c;
	while ((c=getch()) == ' ' || c == '\t' || c == '\n')
		; // skip
	if (isdigit(c)) {
digit:
		ungetch(c);
		for (; isdigit(c=getch()); ++i)  // good place to experiment with goto
			arr[i] = c;
		if (c == '.') {
			arr[i++] = c;
			for (; isdigit(c=getch()); ++i)
				arr[i] = c;
		}

		ungetch(c);
		arr[i] = '\0';
		return NUMBER;
	}

	else if (c == EOF) {
		return EOF;
	}

	else if (c == '-') {
		if (isdigit(c=getch())) {
			arr[i++] = '-';
			goto digit;
		}
		else {
			ungetch(c);
			c='-';
		}
	}

	else if (isalpha(c) && isupper(c)) {
		ungetch(c);
		while (isalpha(c=getch()))
			arr[i++] = c;
		ungetch(c);
		arr[i] = '\0';
		return CMD;
	}

	

	arr[i++] = c;
	arr[i] = '\0';
	return c;
}


double stack[MAXSIZE];
int stack_ptr=0;

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

