#define MAXSIZE 1000
#define NUMBER 'n'
#define CMD 'c'
#define UNKNOWN -2
#define VAR 'v'
#define VAR_DEF 'd'
#define SKIP 's'
#define ALPHA_NUM 26  // number of letters in english alphabet

void init_vardefs(short);
int c_getline(int line[], int limit);

double c_atof(char a[], int start);
double c_pow(int n, int p);

double push(double); // return value it is pushing 
double pop(void);
double top(void);
short int top_dup(void);
short int top_swap(void);
void clear(void);
short int is_empty(void);

short int c_strcmp(char[], char[]);

int getch(void);
void ungetch(int);
void ungets(char[]);
int getop(char[]);
void blank_skip(void);
int getdigit(char arr[], int startpoint);

short int isvar(char);
double getvar(char);
void setvar(char, double);

