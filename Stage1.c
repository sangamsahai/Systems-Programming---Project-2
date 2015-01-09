#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/param.h>
#include <sys/vnode.h>
#include <sys/fs/ufs_fs.h>
#include <sys/fs/ufs_inode.h>
#include <time.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>


main(argc, argv)
int argc; 
char *argv[];
{

  
  struct stat buf;
  int fd;
  
  unsigned long ftype;
  
    //Extracting Fname from argv[1]
	  char * x=strrchr( argv[1],  '/');
	   char Fname[20];
	   if(x)
	   {
	   x=x+1;
	   }
	   if(!x)
	   {
	   x=argv[1];
	   }
	   if(x)
	   {
	   int counter=0;
		while(*x != '\0')
		 {
		 Fname[counter]=*x;
		 x++;counter++;
		 }
         Fname[counter]='\0'; 
		 }
		  //printf("Fname is %s  ",Fname);
		 
  
  if (argc != 2) {printf ("usage: File_Attr filename \n"); exit(0);}
  
  /* USING FSTAT() */
	if ((fd = open (argv[1], O_RDONLY)) == -1)
	{
	perror(Fname);
	printf ("error=%d \n", errno);
	exit (-1);
	}
	if (fstat(fd, &buf) < 0)        //USING FSTAT 
	   {perror ("fstat problem"); exit (-1);}

	   if (! S_ISREG(buf.st_mode))  //CHECKING IF INPUT IS NOT A REGULAR FILE
	   {
	   printf("Input is not a regular file !!!");
	   exit(0);
	   }
	   
	  
	 print_attr(buf,Fname);

	 close(fd);
}//end of main

print_attr(struct stat buf,char Fname[])
{

printf("\n");

//printing file permissions starts
//printf("File Permissions: \t");
    printf( (S_ISDIR(buf.st_mode)) ? "d" : "-");
    printf( (buf.st_mode & S_IRUSR) ? "r" : "-");
    printf( (buf.st_mode & S_IWUSR) ? "w" : "-");
    printf( (buf.st_mode & S_IXUSR) ? "x" : "-");
    printf( (buf.st_mode & S_IRGRP) ? "r" : "-");
    printf( (buf.st_mode & S_IWGRP) ? "w" : "-");
    printf( (buf.st_mode & S_IXGRP) ? "x" : "-");
    printf( (buf.st_mode & S_IROTH) ? "r" : "-");
    printf( (buf.st_mode & S_IWOTH) ? "w" : "-");
    printf( (buf.st_mode & S_IXOTH) ? "x" : "-");
    
//printing file permission ends

//no of links
//printf("\n Number of Links: \t%d\n",buf.st_nlink);
printf("   %d",buf.st_nlink);

//UID and GID
//printf("\n The userID and the GroupID of the owner of the file are [%d] and [%d] respectively \n", (int)buf.st_uid, (int)buf.st_gid);

struct passwd *pws;
pws = getpwuid((int)buf.st_uid);
if(pws)
printf(" %s ",pws->pw_name);

struct group *grp;
grp = getgrgid(buf.st_gid);
if(grp)
    printf("   %s ", grp->gr_name);


//printing size
printf("   %d",buf.st_size);


//printing time
char buff[20];
strftime(buff, 20, "%b %d %H:%M", localtime(& buf.st_mtime));
printf("  %s",buff);


//printing file name
printf("  %s\n\n ",Fname);




}//end of function attr

