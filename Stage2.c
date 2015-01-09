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
#include <dirent.h>

struct dirent * entry;
DIR * dir;


main(argc, argv)
int argc; 
char *argv[];
{

  int fd;
  unsigned long ftype;
  
   if (argc != 2) {printf ("Inputs are not correct !! \n"); exit(0);}
  
  
 //printf("argv 1 is %s",argv[1]);
	
	if( ( dir = opendir(argv[1]) ) == NULL  )
	{
	perror("open problem");
	exit(0);
	}
	else
	{
	visitDir(argv[1]);
	}
  


}//end of main

visitDir(char path[])
{
printf("\n Path is--> %s \n ",path);
dir = opendir(path);

while ((entry= readdir(dir)) != NULL)  //WHILE LOOP TO ITERATE THE DIRECTORY STARTS
{
//ignoring . and .. entries
if((entry->d_name[0] == '.')  && (entry->d_name[1] == '\0') )
{
continue;
}
if((entry->d_name[0] == '.')  && (entry->d_name[1] == '.') && (entry->d_name[2] == '\0') )
{
continue;
}

char full_path[100]="";
strcat(full_path,path);
strcat(full_path,"/");
strcat(full_path,entry->d_name);  //now the full path is complete



//printf("\n full path %s",full_path);

 //printf("\n %s",entry->d_name);

int fd;
struct stat buf;
if ((fd = open (full_path, O_RDONLY)) == -1)
	{
	perror("ERROR in opening file");
	printf ("error=%d \n", errno);
	exit (-1);
	}
	else
	{
	fstat(fd, &buf);
	print_attr(buf,entry->d_name);
	//free(&full_path);  //FREE THE MEMORY 
	}
 

 close(fd);


}//end of while

if(closedir(dir)==-1)
{
perror("close problem");
	exit(0);
}

}//end of visitDir


print_attr(struct stat buf,char Fname[])
{
//printf("In the function print_attrn \n");
//printf("Fname is %s \n",Fname);


//printing file permissions starts
//printf("File Permissions: \t");
printf("\n");
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
printf("   %5d",buf.st_size);

//printing time
char buff[20];
strftime(buff, 20, "%b %d %H:%M", localtime(& buf.st_mtime));
printf("  %s",buff);

//printing file name
printf("   %s \n",Fname);




}//end of function attr

