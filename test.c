 #include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<pwd.h>
#include <fcntl.h>     
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
void permission(struct stat fileStat)
{
 //   printf("inside permission\n");
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\t");
  //  printf("outside permission\n");
}
void size1(struct stat filestat)
{
   // printf("inside size \n");
    printf("%d \t",filestat.st_size);
  //  printf("outside size\n");
}
void user_group(struct stat filestat)
{
    //printf("user_group\n");
    struct group *grp;
    struct passwd *pwd;

    grp = getgrgid(filestat.st_gid);
    pwd = getpwuid(filestat.st_uid);
    printf("%s \t %s \t",pwd->pw_name,grp->gr_name);
   // printf("outside _ group\n");
}
void link1(struct stat filestat)
{
 //   printf("aha link1 \n");
    printf("%d \t",filestat.st_nlink);
  //  printf("bye bye link2\n");
}
/*void type1(struct stat *filestat)
{
    if(filestat.st_mode & S_ISREG)
    printf("-");
    else if(filestat.st_mode & S_ISDIR)
    printf("d");
    else if(filestat.st_mode & S_ISCHR)
    printf("c");
    else if(filestat.st_mode & S_ISBLK)
    printf("b");
    else if(filestat.st_mode & S_ISFIFO)
    printf("p");
}*/
void time1(struct stat filestat)
{
   // printf("time\n");
    struct tm dt;
    dt = *(gmtime(&filestat.st_mtime));
    printf("%d-%d-%d %d:%d:%d\t", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, 
                                              dt.tm_hour, dt.tm_min, dt.tm_sec);
  //  printf("ok\n");
}
void ls1(char* command[100],int z,char home[1024])
{
    char address[1024];
    int h=0;
    int l=0;
    char x[1024];
    address[0]='.';
    address[1]='\0';
    if(z>1 && z<=4)
    {
      for(int i=1;i<z;i++)
      {
        if(command[i][0]=='-')
        {
          int k=strlen(command[i]);
          for(int j=0;j<k;j++)
          {
            if(command[i][j]=='l')
            l=1;
            if(command[i][j]=='a')
            h=1;
          }
        }
        else
        {
             int k=strlen(command[i]);
             int u=0;
             
             if(command[i][0]=='~')
             {
               fprintf(stderr,"enter %s\n",home);
               int rr=strlen(home);
               printf("%s\n",home);
               for(int i=0;i<rr;i++)
               address[i]=home[i];
               address[rr]='\0';
             }
             else
             {
             for(int u=0;u<k;u++)
             address[u]=command[i][u];
             address[k]='\0';
             }
        }
      }
    }
    struct dirent *folder;
    DIR *dir=opendir(address);
    if(dir==NULL)
    {
        perror("Error");
    }
    else
    {
        int u=0;
        int d=strlen(address);
        for(int i=0;i<d;i++)
        x[i]=address[i];
        while((folder=readdir(dir)))
        {
        int size=d;
        x[d]='/';
        size++;
        int r=strlen(folder->d_name);
        for(int i=0;i<r;i++)
        {
            x[size]=folder->d_name[i];
            size++;
        }
        x[size]='\0';
       
      //  printf("%s\n",x);
         struct stat buf;
      //  printf("here\n");
         int u=stat(x,&buf);
        // printf("not here\n");
        // type1(buf);
         //printf("x : %s l : %d h : %d\n",x,l,h);
       //  printf("u : %d\n",u);
        if(!(folder->d_name[0]=='.' && h==0))
        {
        if(u!=-1)
        {
          
        if(l==1)
        {
         //   printf("inside\n");
         permission(buf);
       //  printf("not inside\n");
         link1(buf);
       //  printf("not not inside\n");
         user_group(buf);
        // printf("not not not inside\n");
         size1(buf);
       //  printf("here 1\n");
         time1(buf);
       //  printf("not here\n");
         printf("%s\n",folder->d_name);
       //  printf("sad\n");
        }
        else if(l==0)
        {
           printf("%s\n",folder->d_name);
        }
        
        }

        else
        {
            perror("error");
        }
        }

        }

    }
    closedir(dir);
    
}
/*int main()
{

}*/
