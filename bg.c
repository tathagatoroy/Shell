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

void bg(char* final1[100],int z,struct sol store[])
{
    int job1=con1(final1[1]);
    if(store[job1].status!=1)
    {
       fprintf(stderr,"job number given wrong\n");

    }
    else
    {
        int pid=store[job1].pid;
        int dd=kill(pid,SIGCONT);
        if(dd<0)
        fprintf(stderr,"some error occured\n");
    }
}