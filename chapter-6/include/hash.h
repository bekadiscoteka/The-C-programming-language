#include <stddef.h>

typedef struct vocab {
	char *name;
	char *def;
} Dict;

size_t c_hash(char *);
const char *c_lookup(char *);
Dict *c_install(char *name, char *def);
void undef(char *name);

