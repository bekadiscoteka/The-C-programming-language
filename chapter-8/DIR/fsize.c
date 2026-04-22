#include <stdio.h> 
#include <limits.h>
#include <string.h> 
#include <fcntl.h>      /* flags for read and write */ 
#include <unistd.h>
#include <sys/types.h>  /* typedefs */ 
#include <sys/stat.h>   /* structure returned by stat */ 
#include "dirent.h" 
#include <stdlib.h>
#include <time.h>
#include <math.h>

void fsize(char *);
void dirwalk(char *, void (*fcn)(char *)); 

/* print file name */ 

int main(int argc, char **argv) 
{ 
   if (argc == 1)  /* default: current directory */ 
	   fsize("."); 
   else 
	   while (--argc > 0) 
		   fsize(*++argv); 
   return 0; 
} 

/* fsize:  print the name of file "name" */ 
void fsize(char *name) 
{ 
   struct stat stbuf; 
   if (stat(name, &stbuf) == -1) { 
	   fprintf(stderr, "fsize: can't access %s\n", name); 
	   return; 
   } 
   if ((stbuf.st_mode & S_IFMT) == S_IFDIR) 
	   dirwalk(name, fsize); 

   printf("%*s\t%*s\t%26s\t%26s\n", /*(int) sqrt(INT_MAX)*/ 10, "size:", 10, "name:", "created:", "last accessed:");

   char created_time[26], accessed_time[26];
   strcpy(created_time, ctime(&(stbuf.st_ctime)));
   strcpy(accessed_time, ctime(&(stbuf.st_atime)));

    created_time[strlen(created_time) - 1] = '\0';
    accessed_time[strlen(accessed_time) - 1] = '\0';

   printf("%*ld\t%*s\t%26s\t%26s\n", /*(int) sqrt(INT_MAX)*/ 10, stbuf.st_size, 10, name, created_time, accessed_time);
} 

/* dirwalk:  apply fcn to all files in dir */ 
void dirwalk(char *dir, void (*fcn)(char *)) 
{ 
   char name[MAX_PATH]; 
   Dirent *dp; 
   sDIR *dfd; 
   if ((dfd = s_opendir(dir)) == NULL) { 
	   fprintf(stderr, "dirwalk: can't open %s\n", dir); 
	   return; 
   } 
   while ((dp = s_readdir(dfd)) != NULL) { 
	   if (strcmp(dp->name, ".") == 0 
		   || strcmp(dp->name, "..")) 
		   continue;    /* skip self and parent */ 
	   if (strlen(dir)+strlen(dp->name)+2 > sizeof(name)) 
		   fprintf(stderr, "dirwalk: name %s %s too long\n", 
			   dir, dp->name); 
	   else { 
		   sprintf(name, "%s/%s", dir, dp->name); 
		   (*fcn)(name); 
	   } 
   } 
   s_closedir(dfd); 
} 



 
