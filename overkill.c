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
void overkill(char* final1[],int z,struct sol store[])
{
    if(z!=1)
    {
        fprintf(stderr,"Wrong command\n");
    }
    else
    {
        for(int i=0;i<40000;i++)
        {
            if(store[i].status==1)
            {
                store[i].status=-1;
           int f  = kill(store[i].pid,SIGINT);
           {
               if(f<0)
               {
                   fprintf(stderr,"killing job with id %d and pid %d unsuccesful\n",i,store[i].pid);
               }
           }
            }
        }
    }
}