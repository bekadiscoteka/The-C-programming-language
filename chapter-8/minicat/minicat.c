#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stddef.h>
#define BUFSIZE 100

static char buf[BUFSIZE];

void printfile(int fd) {
	size_t wr_bufsize;

	while ((wr_bufsize=read(fd, buf, BUFSIZE)) > 0)
		write(1, buf, wr_bufsize);	
}

int main(int argc, char* argv[]) {

	int fd;

	if (argc == 1) {
		printfile(0);
		return 0;
	}

	else
		while (*++argv != NULL) {
			if ( (fd = open(*argv, O_RDONLY, 0)) == -1) {
				char errmsg[] = "Can't open file: ";
				write( 2, errmsg, (sizeof(char) * (strlen(errmsg))) );
				write( 2, *argv, sizeof(char) * strlen(*argv) );
			}

			else { 
				printfile(fd);
				close(fd);
			}
		}

	return 0;
}
