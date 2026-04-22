#include <sys/dir.h>
#define MAX_PATH 1024 

typedef struct {       /* portable directory entry */ 
   long ino;                  /* inode number */ 
   char name[NAME_MAX+1];     /* name + '\0' terminator */ 
} Dirent; 

typedef struct {       /* minimal DIR: no buffering, etc. */ 
   int fd;               /* file descriptor for the directory */ 
   Dirent d;             /* the directory entry */ 
} sDIR; 

sDIR *s_opendir(char *dirname); 
Dirent *s_readdir(sDIR *dfd); 
void s_closedir(sDIR *dfd); 






