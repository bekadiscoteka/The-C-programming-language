#include <stddef.h>
typedef unsigned long Align;

union header {
	struct {
		union header *ptr;
		unsigned size;
	} s;
	Align x;
};

typedef union header Header;

void *s_malloc(unsigned);
void s_free(void*);
void *s_calloc(unsigned, unsigned);
void s_bfree(void*, unsigned);

