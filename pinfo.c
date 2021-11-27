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
#include<sys/procfs.h>
#include<math.h>
int power(int a,int p)
{
    int res=1;
    if(a==0)
    res=0;
    for(int i=1;i<=p;i++)
    res=res*a;
    return res;

}
void pinfo1(char *final1[100],int z)
{
//printf("%d zz d also final 1 2 %s %s\n",z,final1[0],final1[1]);
    pid_t p;

    if(z==1)
    p=getpid();
    else
    {
        int k=0;
        int zz=strlen(final1[1]);
    //    printf("hoho %s\n",final1[1]);
        for(int i=0;i<zz;i++)
        {
            int u2=final1[1][i]-'0';
            k=k+u2*power(10,zz-1-i);
        }
        p=k;
    }
  //  printf("z %d p %d\n",p);

char file[1024];

sprintf(file,"/proc/%d/status",p);
FILE *f=fopen(file,"r");
if(f==NULL)
{
    fprintf(stderr,"given process id is wrong\n");

}
else
{
    char line[400];
    int buffer=400;
    char *stat;
    char *mem;
    stat=NULL;
    mem=NULL;
    char s[]="State:";
    char s1[]="VmSize:";
    char *token;
    char x;
    while(fgets(line,400,f)!=NULL)
    {
     //   printf("%s\n",line);
        token=strtok(line," \t");
     //   printf("token : %s\n",token);
        if(strcmp(token,s)==0 & stat==NULL)
        {
            //printf("here\n");
            stat=strtok(NULL," \t\0\n");
           // printf("haha : %s\n",stat);
            x=stat[0];
            
            
        }
        if(strcmp(token,s1)==0 && mem==NULL)
        {
          //  printf("not here\n");
            mem=strtok(NULL," \t\0\n");
          //  printf("haha1 : %s\n",mem);
        }
        if(mem!=NULL && stat!=NULL)
        break;
       // if(stat!=NULL)
     //   printf("stat : %s\n",stat);
    }
    if(mem!=NULL)
    printf("pid : %d\n Process status : %c\nVirtual Memory :%s\n",p,x,mem);
    else
    printf("pid : %d\n Process status : %c\nVirtual Memory :0\n",p,x);
    char path[1024];
    int b1=1024;
    char path1[1024];
    sprintf(path1,"/proc/%d/exe",p);
  //  printf("path1 : %s\n",path1);
    int r=readlink(path1,path,b1);
    if(r==-1)
    {
        fprintf(stderr,"path not found\n");
    }
    else
    {
       // int dd=strlen(path);
        path[r]='\0';
       /* for(int i=5;i<dd;i++)
        {
            if(path[i]=='t' && path[i-1]=='u' && path[i-2]=='o' && path[i-3]=='.' && path[i-4]=='a' && path[i-5]=='/')
            {
                path[i+1]='\0';
                break;
            }
        }*/
        printf("executable path : %s\n",path);
    }


    }
}


    
/*int main()
{
    int d=1;
    pinfo(31082);
    return 0;
}*/