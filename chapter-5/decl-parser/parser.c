#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
#include "mystd.h"
#define MAXTOKEN  100 

int gettoken(void);
void dcl(void); 
void dirdcl(void); 

int tokentype;           /* type of last token */ 
char token[MAXTOKEN];    /* last token string */ 
char name[MAXTOKEN];      /* identifier name */ 
char datatype[MAXTOKEN]; /* data type = char, int, etc. */ 
char out[1000]; 
enum { NAME, PARENS, BRACKETS }; 

/* dcl:  parse a declarator */ 
void dcl(void) 
{ 
   int ns; 
   for (ns = 0; gettoken() == '*'; ) /* count *'s */ 
	   ns++; 
   dirdcl(); 
   while (ns-- > 0) 
	   strcat(out, " pointer to"); 
} 
/* dirdcl:  parse a direct declarator */ 
void dirdcl(void) 
{ 
   int type; 
   if (tokentype == '(') {         /* ( dcl ) */ 
	   dcl(); 
	   if (tokentype != ')') {
		   printf("warning: missing ) is implicitly added\n"); 
		   ungetch(tokentype);
		   tokentype = ')'; 
	   }

   } else if (tokentype == NAME)  /* variable name */ 
	   strcpy(name, token); 

   else {
	   printf("error: expected name or (dcl)\n"); 
	   ungetch(tokentype);
	   tokentype = NAME;
	   strcpy(token, "<unnamed>");
	   strcpy(name, token); 
   }
   
   while ((type=gettoken()) == PARENS || type == BRACKETS) 
	   if (type == PARENS) { 
		   char temp[MAXTOKEN];
   		   sprintf(temp, " function%s returning", token);
		   strcat(out, temp); 
	   }
	   else { 
		   strcat(out, " array"); 
		   strcat(out, token); 
		   strcat(out, " of"); 
	   } 
} 



int gettoken(void)  /* return next token */ 
{ 
   int c;
   char *p = token; 
   while ((c = getch()) == ' ' || c == '\t') 
	   ; 
   if (c == '(') { 
	   if ((c = getch()) == ')') { 
		   strcpy(token, "()"); 
		   return tokentype = PARENS; 
	   } else { 
		   tokentype = '(';
		   ungetch(c); 
		   char temp[MAXTOKEN];
		   int i=0;
		   while ((temp[i++]=c=getch()) != ')') {
			   if (c == '\n' || i == MAXTOKEN-1) {
				   printf("too long content of parenth or missing )");
				   tokentype = '(';
				   break;
			   }

			   if (c == ',') 
				   tokentype = PARENS;
		   }
		  
		   if (tokentype == PARENS) {
			   temp[i] = '\0';
			   sprintf(token, "(%s", temp);
		   } 
		   else {
			   while (--i >= 0)
				   ungetch(temp[i]);
		   }

		   return tokentype;

	   } 

   } else if (c == '[') { 
	   for (*p++ = c; (*p++ = getch()) != ']'; ) 
		   ; 
	   *p = '\0'; 
	   return tokentype = BRACKETS; 
   } else if (isalpha(c)) { 
	   for (*p++ = c; isalnum(c = getch()); ) 
		   *p++ = c; 
	   *p = '\0'; 
	   ungetch(c); 
	   return tokentype = NAME; 
   } else 
	   return tokentype = c; 
} 


int main()  /* convert declaration to words */ 
#ifndef UNDCL
{ 
	printf("DCL mode: \n");
   while (gettoken() != EOF) {   /* 1st token on line */ 
	   strcpy(datatype, token);  /* is the datatype */ 
	   out[0] = '\0'; 
	   dcl();       /* parse rest of line */ 
	   if (tokentype != '\n') 
		   printf("syntax error\n"); 
	   printf("%s: %s %s\n", name, out, datatype); 
   } 
   return 0; 
} 
#else 
   /* undcl:  convert word descriptions to declarations */ 
{ 
	printf("UNDCL mode\n");
   int type, prevtype; 
   char temp[MAXTOKEN]; 
   while (gettoken() != EOF) { 
	   strcpy(out, token); 
	   while ((type = gettoken()) != '\n') {
		   if (type == PARENS || type == BRACKETS) {
			   if (prevtype == '*') {
				   sprintf(temp, "(%s)%s", out, token);
				   strcpy(out, temp);
			   }
			   else 
				   strcat(out, token); 
		   }
		   else if (type == '*') { 
			   sprintf(temp, "*%s", out); 
			   strcpy(out, temp); 
		   } else if (type == NAME) { 
			   sprintf(temp, "%s %s", token, out); 
			   strcpy(out, temp); 
		   } else 
			   printf("invalid input at %s\n", token); 
			prevtype = type;
	   }
	   printf("%s\n", out);
   } 
   return 0; 
} 
#endif

