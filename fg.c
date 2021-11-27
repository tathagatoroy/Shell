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
//int size=40000;
struct sol
{
    char jobname[1024];
    char run[1024];
    int pid;
    int job_no;
    int status;
};
int con1(char str[]);

void fg(char* final1[],int z,struct sol store[],int *fg_flag)
{
   /* fprintf(stderr,"ans\n");
    fprintf(stderr,"%d\n",z);
    for(int i=0;i<z;i++)
    {
        fprintf(stderr,"%d\n",i);
      fprintf(stderr,"%d : %s\n",i,final1[i]);
    }*/
    if(z != 2)
    {
        fprintf(stderr,"wrong number of arguments\n");
    }
    //checking the correctness of job number given
    else if(z == 2)
    {
        int job_no=con1(final1[1]);
        printf("job_no\n",job_no);
        if(store[job_no].status == 0)
        {
            fprintf(stderr,"job id given is wrong\n");
        }
        else
        {
            //fprintf(stderr,"inside\n");
            struct sol job_info;
            job_info.pid=store[job_no].pid;
            strcmp(job_info.jobname,store[job_no].jobname);
            store[job_no].status=-1;
            //deleting the job number from background list
            
            //protection against signals
            //background processes trying to access the terminal
            signal(SIGTTIN,SIG_IGN);
            signal(SIGTTOU,SIG_IGN);
            pid_t gid=getpgid(job_info.pid);
            int r=tcsetpgrp(STDIN_FILENO,gid);
            if(r<0)
            {
                printf("failure to access to STDIN\n");
            }
            //resume the child process
            //fprintf(stderr,"STDIN SET\n");
            //fprintf(stderr,"job_no %d pid %d job_name %s\n",job_no,job_info.pid,job_info.jobname);
            kill(job_info.pid,SIGCONT);
            
            int status;
             fg_flag = job_info.pid;
            //wait
            waitpid(job_info.pid,&status,WUNTRACED);
            
            // resume control by parent process
            int f=tcsetpgrp(STDIN_FILENO,getpgrp());
            fg_flag = -1;
            //no signal handling anymore.Ignore previous handling
            signal(SIGTTIN,SIG_DFL);
            signal(SIGTTOU,SIG_DFL);

            if(WIFSTOPPED(status))
            {
                store[job_no].status=1;
            }
            
            
            
        }
    }
}