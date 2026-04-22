#include <sys/dir.h>   /* local directory structure */ 
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h>      /* flags for read and write */ 
#include <unistd.h>
#include <sys/types.h>  /* typedefs */ 
#include <sys/stat.h>   /* structure returned by stat */ 
#include "dirent.h" 
#include <stdlib.h>
#define DIRSIZ 14

int fstat(int fd, struct stat *); 
/* opendir:  open a directory for readdir calls */ 
sDIR *s_opendir(char *dirname) 
{ 
   int fd; 
   struct stat stbuf; 
   sDIR *dp; 
   if ((fd = open(dirname, O_RDONLY, 0)) == -1 
	|| fstat(fd, &stbuf) == -1 
	|| (stbuf.st_mode & S_IFMT) != S_IFDIR 
	|| (dp = (sDIR *) malloc(sizeof(sDIR))) == NULL) 
		return NULL; 
   dp->fd = fd; 
   return dp; 
} 


/* closedir:  close directory opened by opendir */ 
void s_closedir(sDIR *dp) 
{ 
   if (dp) { 
	   close(dp->fd); 
	   free(dp); 
   } 
} 

/* readdir:  read directory entries in sequence */ 
Dirent *s_readdir(sDIR *dp) 
{ 
   struct direct dirbuf;  /* local directory structure */ 
   static Dirent  d;      /* return: portable structure */ 
   while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) 
				   == sizeof(dirbuf)) { 
	   if (dirbuf.d_ino == 0) /* slot not in use */ 
		   continue; 
	   d.ino = dirbuf.d_ino; 
	   strncpy(d.name, dirbuf.d_name, DIRSIZ); 
	   d.name[DIRSIZ] = '\0';  /* ensure termination */ 
	   return &d; 
   } 
   return NULL; 
}
