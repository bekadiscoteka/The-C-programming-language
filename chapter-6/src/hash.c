#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mystd.h"
#include "mystring.h"
#include "hash.h"
#define HASHSIZE 100
#define MAXWORD 100

/*  
*//*  -------------------------
*//*  SIMPLE HASH IMPLEMENTATION
*//*  -------------------------
*//*
*/


static Dict *hashtab[HASHSIZE];

size_t c_hash(char *name) {
	unsigned acc = 1;
	for (int i = 0; name[i] != '\0'; ++i) 
		acc = acc * name[i] + 13;		

	return (size_t) acc % HASHSIZE;
}

const char *c_lookup(char *name) {
	Dict *p;
	if ((p = hashtab[c_hash(name)]) == NULL) 
		return NULL;
	if (strcmp(p->name, name) == 0)
		return p->def;
}

Dict *c_install(char *name, char *def) {
	if (c_lookup(name) == NULL) {
		Dict *temp;
		temp = hashtab[c_hash(name)] = (Dict *) malloc(sizeof(Dict));	
		temp->name = c_strdup(name);
		temp->def = c_strdup(def);
		return temp;
	}
	else 
		return NULL;
}

void undef(char *name) {
	extern Dict *hashtab[HASHSIZE];

	if (c_lookup(name) != NULL) {
		free(hashtab[c_hash(name)]);
	    hashtab[c_hash(name)] = NULL;
	}
}







