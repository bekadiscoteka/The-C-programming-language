
/*
system functions:
int write(int fd, char* s, size_t byte); this will output string to fd (controlled by OS over process)
we specify number of bytes, which means it's not smart

int read(int fd, char* s, size_t byte); the same as write()

int open(char* name, int mode, int permission); opens file, what permission is for UNKNOWN for me yet
modes: O_RDONLY, O_WRONLY, O_RDWR

close(df);  - OS will no longer control that fd

unlink(char* filename) - removes the file

lseek(fd, int offset, int origin) makes offset for file, starting from origin
modes for origin: 0 - start; 1 - current; 2 - end

this means OS is still smart enough to keep track of where are we writing and change that position

problems: 
get rid of byte specifying: add smart string readers
add buffer: getc(), putc(), ungetc(), getchar(), putchar()
functions for check: feof(), ferror();

AND THE MOST IMPORTANT REASON: 
these are UNIX system functions that tied to this specific OS
we should implement those functions with less use of system calls
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define sEOF (-1)
#define sNULL (0)
#define sBUFSIZ 1024
#define OPEN_MAX 20

#define s_stdin 0
#define s_stdout 1
#define s_stderr 2

static unsigned FILE_N = 3;

typedef struct __iobuf {
	char* ptr;
	char* base;
	int cnt;
	int flag;
	int fd;	
} sFILE;

enum flags {
	_READ = 1,
	_WRITE = 2,
	_EOF = 4,
	_ERR = 8
};

enum fseek_origins {
	SFSEEK_BEGIN=0,
	SFSEEK_CURR,
	SFSEEK_END
};

int _fillbuf(sFILE *);
int _flushbuf(sFILE *, int);
int s_fflush(sFILE *);


#define s_fgetc(p) (--(p->cnt) >= 0 ?\
		*(p->ptr++) : _fillbuf(p))

#define s_fputc(p, c) (--(p->cnt) >= 0 ?\
		*( (p->ptr)++ ) = c : _flushbuf(p, c)) 
#define s_feof(p) (p->flag == _EOF)
#define s_ferror(p) (p->flag == _ERR)
#define s_fileno(p) (p->fd)

// #define getchar() s_getc(s_stdin)
// #define putchar(c) s_putc(s_stdout, c)


sFILE *s_fopen(char *name, char *mode) {
	int fd, flag, oflag;
	if (FILE_N == OPEN_MAX)
		return NULL;


	switch (*mode) {
		case 'r': 
			flag = _READ;
			oflag = O_RDONLY;
			break;
		case 'w': case 'a': 
			flag = _WRITE;
			oflag = O_WRONLY;
			break;
		default: 
			return NULL;		
	}

	sFILE *f; 
	if ( (f=malloc(sizeof(sFILE))) == NULL )
		return NULL;

	if (( f->fd = open(name, oflag, 0) ) == -1)
		return NULL;
	f->cnt = 0;	
	f->flag = flag;
	f->ptr = f->base = NULL;

	if (*mode == 'a') 
		lseek(f->fd, 0L, 2);

	FILE_N++;

	return f; 
}



int s_fclose(sFILE *p) {
	if (s_fflush(p) == -1) 
		return -1;
	free(p->base);	
	free(p);
	return 0;
}

int _fillbuf(sFILE *fp) {
	if ((fp->flag & _READ) == 0)
		return -1;

	if (fp->base == NULL)
		fp->base = malloc(sBUFSIZ);

	int state = read(fp->fd, fp->base, sBUFSIZ);	

	switch (state) {
		case -1:
			fp->flag = _ERR;
			return 0;
		case 0:
			fp->flag = _EOF;
			return sEOF;
	}

	fp->cnt = sBUFSIZ;
	fp->ptr = fp->base;
	fp->cnt--;
	return *fp->ptr++; 
}

int s_fflush(sFILE *p) {   // return number of flushed elements, -1 for error
	if ( (p->flag & _WRITE) == 0 )
		return -1;

	if (p->base != NULL) {
		p->ptr = p->base;
		int n = write(p->fd, p->base, sBUFSIZ - p->cnt);

		if (n == -1) 
			p->flag = _ERR;

		p->cnt = sBUFSIZ;
		return n;
	}
	return -1;
}

int s_fseek(sFILE *f, long offset, int origin) {
	if (f == NULL) 
		return -1;

	switch (f->flag) {
		case _WRITE:
			if (s_fflush(f) == -1) 
				return -1;
			break;
		case _READ:
			f->ptr = f->base + sBUFSIZ;
			f->cnt = 0;	
			break;
		default:	
			return -1;
	}	

	if ((lseek(s_fileno(f), offset, origin)) == -1)
		return -1;
}

int _flushbuf(sFILE *p, int c) {
	if ((p->flag & _WRITE) == 0)
		return -1;

	if (p->base == NULL) {	
		p->base = malloc(sBUFSIZ);
		p->ptr = p->base;
		p->cnt = sBUFSIZ;

		p->cnt--;
		*p->ptr++ = c;
		return 0;
	}

	p->ptr = p->base;
	p->cnt = sBUFSIZ;


	if (( write(p->fd, p->base, sBUFSIZ ) == -1))
		return -1;

	// additional c
	p->cnt--;
	*p->ptr++ = c;

	return 0;
}











