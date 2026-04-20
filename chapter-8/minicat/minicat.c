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
	size_t wr_bufsize;
	char buf[BUFSIZE];

	if (argc == 1) {
		printfile(0);
		return 0;
	}

	else
		while (*++argv != NULL) {
			if ( (fd = open(*argv, O_RDONLY, 0)) == -1) {
				char errmsg[100] = "Usage: cat filename\n";
				sprintf(errmsg, "Can't open file %s, with %3o permission\n", *argv, O_RDONLY);
				write( 2, errmsg, (sizeof(errmsg[1]) * (strlen(errmsg)+1)) );
			}
			else 
				printfile(fd);
			close(fd);
		}

	return 0;
}
