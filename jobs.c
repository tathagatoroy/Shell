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

void jobs(char* pro_id[],int pro_id_job[],char* pro[],struct sol store[],int pjob[])
{
    int ans[40000]={0};
    int flag[40000]={0};
    //printf("enter\n")
    for(int i=0;i<40000;i++)
    {
        flag[i]=0;
        ans[i]=0;
        if(store[i].status==1)
        {
            //printf("process id : %d called process %s has job %d\n",i,pro_id[i],pro_id_job[i]);
            ans[i]=store[i].pid;
        }
    }
  //  char* ans_state[40000];
    for(int i=1;i<40000;i++)
    {
        if(store[i].status==1)
        {
                char line[400];
    int buf=400;
   // int state=0;
    char* state=NULL;
    char r[]="State:";
    char file[1024];
    char x;

sprintf(file,"/proc/%d/status",store[i].pid);
//printf("file : %s\n",file);
FILE *f=fopen(file,"r");
if(f==NULL)
{
    fprintf(stderr,"cant get information about job with proccess id %d\n",ans[i]);
     flag[i]=1;
}
else
{
    char* token;
      while(fgets(line,400,f)!=NULL)
    {
       // printf("%s\n",line);
        token=strtok(line," \t");
       // printf("token : %s\n",token);
        if(strcmp(token,r)==0 & state==NULL)
        {
         //   printf("here\n");
            state=strtok(NULL," \t\0\n");
           // printf("haha : %s\n",state);
            x=state[0];
            if(x=='S')
            {
                char temp[]="RUNNING";
             //   printf("%d %s\n",i,temp);
                strcpy(store[i].run,temp);
            }
            else if(x=='T')
            {
                char temp[]="STOPPED";
               // printf("%d %s\n",i,temp);
                strcpy(store[i].run,temp);
            }
           break; 
            
        }
    }
}
        }
    }
 /*   for(int i=0;i<40000;i++)
    {
        if(ans[i]!=0)
        printf("%s %d",pro_id[i],i);
    }*/
    for(int i=0;i<40000;i++)
    {
        if(store[i].status==1 && flag[i]==0)
        printf("[%d] %s %s [%d]\n",i,store[i].run,store[i].jobname,store[i].pid);
    }
}