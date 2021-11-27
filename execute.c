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
struct sol
{
    char jobname[1024];
    char run[1024];
    int pid;
    int job_no;
    int status;
    
};
void parse1(char *command[100],char *res[100],char input[1024],char output[1024],int size,int  *in,int *out,int *flag,int *ret_size);
void execute(char *final1[100],int z,char* pro_id[],int pro_id_job[],char* pro[],struct sol store[],int pjob[],int* fg_flag)
{
  //  printf("hola\n");
    pid_t pid;
    int status;
    char *cur[100];
 //   printf("%d  \n",z);

  // printf("here\n"); 
   int cnt=0;
       //char *res[100];
    for(int i=0;i<z;i++)
    {
        if(!(i==z-1 && (strcmp(final1[i],"&")==0)))
        {
           cur[i]=final1[i];
          // printf("%s\n",cur[i]);
           cnt++;
        }
        
    }
    cur[cnt]='\0';
    cnt++;

    //for(int i=0;i<cnt;i++)
  // printf("haha %d\t %s\n",i,cur[i]);

   // printf("not here\n");

    pid = fork();
    if(pid < 0)
    {
        fprintf(stderr,"Error in forking\n");
    }
    else if(pid == 0)
    {
        
       // pid_t child=getpid();
        
        //proc_id[child]=cur[0];
     //   printf("process with pid %d and called %s has started\n",child,proc_id[child]);
 
  /*   int in=0;
     int flag=0;
     int out=0;
     int save_inp=0;
     int save_out=0;
     char inp[1024];
     char output[1024];
     int ret_size;
  //   printf("enter\n");
    // printf("haha\n");
     parse1(cur,res,inp,output,cnt,&in,&out,&flag,&ret_size);
   //  printf("parse returns with flag %d\n",flag);
    // printf("check...\n");

     if(flag == 1)
     printf("command given is wrong\n");
     if(flag == 0)
     {
    //     printf("command op\n");
   
       if(in == 1)
       {
          printf("input file\n",inp);
       int fd1=open(inp,O_RDONLY);
       
           if(fd1<0)
           {
              printf("input file couldnot be opened\n");
               flag=1;
           }
           else
           {
               save_inp=dup(STDIN_FILENO);
               int d1=dup2(fd1,STDIN_FILENO);
             //  printf("d1 %d\n",d1);
               if(d1<0)
               {
                   perror("error1");
                   flag =1;
               }
               
               close(fd1);
               }
           }
       }
       
     
     if(flag == 0)
     {
         if(out!=0)
         {
     //        printf("output file\n",output);
         int fd2 = -1;
         if(out = 1)
         fd2 = open(output,O_WRONLY|O_CREAT |O_TRUNC,0644);
         else if(out ==2)
         fd2 = open(output,O_WRONLY|O_CREAT |O_APPEND,0644);
         if(fd2<0)
         {
             printf("couldnot open output file\n");
             flag =1;
         }
         else
         {
             save_out=dup(STDOUT_FILENO);
             int zz=dup2(fd2,1);

             if(zz<0)
             {
                 flag=1;
                 perror("error2");
             }
             close(fd2);
         }
         }
     }
     //printf("flag %d\n",flag);
     if(flag == 0)
     {*/
       //  printf("here1\n");
       /*  for(int i=0;i < ret_size;i++)
         printf("%s ",res[i]);
         printf("\n");*/
         
        int z=execvp(cur[0],cur);
        if(z<0)
        fprintf(stderr,"wrong command try again\n");
        /*if(flag == 0)
        {
            if(in !=0)
            dup2(save_inp,STDIN_FILENO);
            if(out!=0)
            dup2(save_out,STDOUT_FILENO);
        }*/
     }
     
        
        


    else
    {
        pid_t child=pid;
        //printf("pinfo : %d\n",pid);
        pro[child]=cur[0];
        pro_id[child]=cur[0];
        //printf("process :%s\n",pro_id[child]);
        int max1=0;
        for(int i=0;i<40000;i++)
        {
            if(pro_id_job[i]>max1)
            max1=pro_id_job[i];
        }
        max1++;
        pro_id_job[child]=max1;
      //  printf("pid %d pro_id %s pro %s job %d\n",child,pro_id[child],pro[child],pro_id_job[child]);
       // printf("job id %d\n",max1);
      // printf("child process is  %d\n",child);
        int status;
        if(!(strcmp(final1[z-1],"&")==0))
        {
            //pprintf("foreground\n");
            int jobb=0;
            for(int i=1;i<40000;i++)
            {
                if(store[i].status == 0)
                {
                    store[i].status=1;
                    strcpy(store[i].jobname,cur[0]);
                    store[i].job_no=i;
                    store[i].pid=child;
                    pjob[child]=i;
                    jobb=i;
                   // fprintf(stderr,"job : %d pid %d\n",jobb,child);
                    break;

                }
            }
            *fg_flag=pid;
            waitpid(pid,&status,WUNTRACED);
            *fg_flag=-1;
            //if(WIFEXITED)
      /*      if(WIFSIGNALED(status))
            {
                int d=WTERMSIG(status);
                fprintf(stderr,"process %d stopped by signal %d",pid,d);
            }*/
            if(WIFSTOPPED(status))
            {
                fprintf(stderr,"status stopped\n");
                store[jobb].status=1;
            }
            else
            {
               // fprintf(stderr,"terminated not stopped\n");
            store[pjob[child]].status=-1;
            }
        }
        else
        {
            for(int i=1;i<40000;i++)
            {
                if(store[i].status == 0)
                {
                    store[i].status=1;
                    strcpy(store[i].jobname,cur[0]);
                    store[i].job_no=i;
                    store[i].pid=child;
                    pjob[child]=i;
                    break;

                }
            }
        }
        
    }
}