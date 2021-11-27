#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<pwd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <string.h>
#include<math.h>
#include <fcntl.h>     
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <grp.h>
#include <time.h>
struct sol
{
    char jobname[1024];
    char run[1024];
    int pid;
    int job_no;
    int status;
};
int con1(char str[]);

void kjob(char* final1[100],int z,struct sol store[])
{
    if(z!=3)
    {
        printf("command given is wrong\n");
    }
    else
    {
        int sig_val=con1(final1[2]);
        int job_no=con1(final1[1]);
        int pid=store[job_no].pid;
        if(store[job_no].status!=1)
        fprintf(stderr,"job number is wrong\n");
        else
        {
     //   printf("signal %d pid %d\n",sig_val,pid);
       int f= kill(pid,sig_val);
       if(f<0)
       fprintf(stderr,"error occured when signalling\n");
        }
    }
}