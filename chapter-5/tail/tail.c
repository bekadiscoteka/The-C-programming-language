#include "mystring.h"
#include "stdio.h"
#include "mystd.h"

int main(int argc, char *argv[]) {
	int n=10;
	char *s = NULL;
	while (--argc > 0) {
		switch (**++argv) {
			case '-':
				n = catoi(*argv + 1);
				break;
			default:
				s = *argv;
				break;
		}
	}

	size_t size = c_strlen(s);	

	if (n <= size) {
		s += size - n;
		printf("%s", s);	
	}
	else 
		printf("input is less than n argument");

	return 0;

	
}
