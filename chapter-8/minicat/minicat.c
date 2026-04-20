#include <stdio.h>
#include <syscall.h>
#include <fcntl.h>
#include <string.h>
#include <stddef.h>
#define BUFSIZE 100

int main(int argc, char* argv[]) {
	if (argc != 2) {
		char errmsg[] = "Usage: cat filename\n";
		write( 2, errmsg, (sizeof(errmsg[1]) * (strlen(errmsg)+1)) );
		return 1;
	}
	int fd;
	size_t wr_bufsize;
	char buf[BUFSIZE];

	if ( (fd = open(*++argv, O_RDONLY, 0)) == -1) {
		char errmsg[100] = "Usage: cat filename\n";
		sprintf(errmsg, "Can't open file %s, with %3o permission\n", *argv, O_RDONLY);
		write( 2, errmsg, (sizeof(errmsg[1]) * (strlen(errmsg)+1)) );
		return 1;
	}

	while ((wr_bufsize=read(fd, buf, BUFSIZE)) > 0)
		write(1, buf, wr_bufsize);	
	return 0;
}
