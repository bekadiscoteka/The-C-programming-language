#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "calc.h"
static double vars[ALPHA_NUM];
static short vardefs[ALPHA_NUM];

short isvar(char v) {
	return ((v-'a') >= 0) ? vardefs[(v-'a')] : 0;
}

double getvar(char v) {
	if (v >= 'a') {
		return vars[v-'a'];
	}
	else 
		printf("\ngetvar ERROR\n");
	return 0;
}

void setvar(char v, double n) {
	if (v >= 'a') {
	   vars[v-'a'] = n;	
	   vardefs[v-'a'] = 1; 
	}
	else 
	   printf("\n setvar ERROR\n");	
}


void init_vardefs(short n) {
	for (int i=0; i<ALPHA_NUM; ++i) 
		vardefs[i] = n;
}
