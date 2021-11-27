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
struct sol store[40000];
int pjob[400000];
void ini2()
{
    for(int i=0;i<40000;i++)
    {
        store[i].status=0;
        pjob[i]=0;
    }
}
int power1(int a,int b)
{
    if(a==0)
    return 0;
    else if(b==0)
    return 1;
    else
    {
        int res=1;
        for(int i=1;i<=b;i++)
        res=res*a;
        return res;
    }
}
int con1(char str[])
{
    int u=strlen(str);
    int ans=0;
    for(int i=0;i<u;i++)
    {
        int f=str[i]-'0';
        ans=ans+f*(int)power1(10,u-1-i);
    }
    return ans;
}
void con2(char str[],int z)
{
    char temp[10];
    int i=0;
    while(z>0)
    {
        int r=z%10;
        char c='0'+r;
        z=z/10;
        temp[i]=c;
        i++;
    }
    for(int j=i-1;j>=0;j--)
    str[i-1-j]=temp[j];
    str[i]='\0';

}

char* path1(char to[],char from[]);
int readline(char str[],char* final[]);
void echo1(char input[],char print[]);
void ls1(char *command[],int z,char home[]);
void execute(char *final1[100],int z,char* pro_id[],int pro_id_job[],char pro[],struct sol store[],int pjob[],int* fg_flag);
void parse1(char *command[100],char *res[100],char input[1024],char output[1024],int size,int  *in,int *out,int *flag,int *ret_size);
int size=1024;
char dir[1024];// directory
char computer[1024];//computer info
char username[1024];//username info
char final[4096];//commandline shell location 
void pinfo1(char *final1[100],int z);//pinfo function
void kjob(char* final1[100],int z,struct sol store[]);//kjobs
void fg(char* final1[],int z,struct sol store[],int* fg_flag);//fg
void overkill(char* final1[],int z,struct sol store[]);
void bg(char* final1[100],int z,struct sol store[]);
void jobs(char* pro_id[],int pro_id_job[],char* pro[],struct sol store[],int pjob[]);//jobs function;
char* pro_id[40000];
char* pro[40000];
int pro_id_job[40000];


//count pipes
int count_pipes(char input[])
{
    int cnt=0;
    int size=strlen(input);
    for(int i=0;i<size;i++)
    {
        if(input[i]=='|')
        cnt++;
    }
    if(input[0]=='|' || input[size-1]=='|')
    cnt=-1;
    return cnt;
}
void ini()
{
    for(int i=0;i<40000;i++)
    {
        char str[]="";
        pro_id[i]=str;
        pro_id_job[i]=0;
        pro[i]=NULL;
    }
}
void handle(int signum)
{
    pid_t pid;
    int   status;
   
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        char h[2000];
        
        char sq[100];
        if(WIFEXITED(status))
        {
            sprintf(sq,"normally");
            
        }
        else
        sprintf(sq,"abnormally\n");  
        int job=pjob[pid];      
        sprintf(h,"\npid : %d program : %s exited %s\n",pid,store[job].jobname,sq);
     //   printf(" sad %s\n",sq);
       printf("%s \n",h);
       char str[]="";
       pro_id[pid]=str;
       pro[pid]=NULL;
       int dr=pjob[pid];
       pjob[pid]=0;
       store[dr].status=-1;
    }
    return ;
}

int fg_flag = -1;
void handle1(int signum)
{
  //  fprintf(stderr,"handle\n");
  if(fg_flag != -1)
  {
      int job_no=pjob[fg_flag];
      int d=kill(job_no,SIGTSTP);
      fg_flag=-1;
  }
}

void handle2(int signum)
{
if(fg_flag != -1)
{
    int job_no=pjob[fg_flag];
    int d=kill(job_no,9);
    fg_flag=-1;
}
}



//function to generate the the display
void present(char dir1[],char home[])
{
  getcwd(dir,size);
  register struct passwd *pw;
  pw=getpwuid(geteuid());
  if(!pw)
  {
      fprintf(stderr,"error in getting userid \n");
      fprintf(stderr,"shell exits\n");
      exit(1);
  }

  gethostname(computer,size);
 // getlogin_r(username,size);

  final[0]='<';
  int v=1;
  int s1=strlen(pw->pw_name);
  for(int i=0;i<s1;i++)
  {
      final[v]=pw->pw_name[i];
      v++;
  }
  final[v]='@';
  v++;
  int s2=strlen(computer);
  for(int i=0;i<s2;i++)
  {
      final[v]=computer[i];
      v++;
  }
  final[v]=':';
  v++;
  char *ans1=path1(dir1,home);
  int u=strlen(ans1);
 // printf("path returned %s\n",ans1);
  for(int i=0;i<u;i++)
  {
      final[v]=ans1[i];
      v++;
  }
  free(ans1);
  final[v]='>';
  v++;
  final[v]='\0';
}
pid_t sx;
int main()
{
   
    signal(SIGCHLD,handle);
    signal(SIGTSTP,handle1);
    signal(SIGINT,handle2);
    printf("Welcome to ROY's Shell\n");
  
    char dir1[1024];
    char home[1024];//contains home directory shell

    getcwd(home,size);
    char *final1[100];//tokenised input
    char input[1024];//input commandline
    char prev[1024];//contains previous directory
    char *comm[100];
    char t[1024];
    getcwd(prev,size);
    ini();
   // printf("shell begins\n");

    while(1)
    {
      //initiate some important useful varibale 
         sx=getpid();
        getcwd(dir1,size);
        present(dir1,home);
        char x[1024];// prints the echo
        printf("%s",final);
    //

    //inputs
        char input3[1024];
      char* z=  gets(input3);
    
    //Cnt^Z 
   if(z==NULL)
   {
      // fprintf(stderr,"exiting\n");
       exit(1);
   }
   
        if(strcmp(input3,"")!=0)
       {
     

     int no_of_pipes=count_pipes(input3);
     int no_of_commands=no_of_pipes+1;
     int cur_index=0;
     int size_of_input=strlen(input3);

     int fildes[no_of_pipes][2];
     if(no_of_commands>1)
     {
    // int fildes[no_of_pipes][2];
     for(int i=0;i<no_of_pipes;i++)
     {
         int ss=pipe(fildes[i]);
         if(ss<0)
         {
             fprintf(stderr,"couldnot create the required pipes,try again\n");
             no_of_commands=-1;
             break;
         }
     }
     }
     
     for(int i1=0;i1<no_of_commands;i1++)
     {
         char cur_command[1024];
         int in1=0;
         while(cur_index<size_of_input && input3[cur_index]!='|')
         {
           cur_command[in1]=input3[cur_index];
           in1++;
           cur_index++;
         }
         cur_index++;
         cur_command[in1]='\0';
         in1++;
       //  fprintf(stderr,"current command %s\n",cur_command);
         if(strcmp(cur_command,"")==0)
         {
             fprintf(stderr,"command is wrong,cant execute,try again please\n");
             break;
         }
         int old_stdin=dup(STDIN_FILENO);
         int old_stdout=dup(STDOUT_FILENO);
         if(no_of_commands>1)
         {
         
         if(i1==0)
         {
             int gg = dup2(fildes[i1][1],STDOUT_FILENO);
             if(gg < 0)
             {
                 fprintf(stderr," error during duplicating fds\n");
                 break;
             }
             close(fildes[i1][1]);
         }
         if(i1==no_of_commands-1)
         {
             int gg = dup2(fildes[i1-1][0],STDIN_FILENO);
             {
                 if(gg < 0)
                 {
                     fprintf(stderr," error during duplicating fds\n");
                 break;
                 }
             }
             close(fildes[i1-1][0]);
         }
         else if( i1 >=1 && i1 < no_of_commands-1)
         {
             int gg1 = dup2(fildes[i1-1][0],STDIN_FILENO);
             if(gg1 < 0)
             {
                 fprintf(stderr," error during duplicating fds\n");
                 break;
             }
             close(fildes[i1-1][0]);
             int gg2 = dup2(fildes[i1][1],STDOUT_FILENO);
             if(gg2 < 0)
             {
                 dup2(old_stdin,STDIN_FILENO);
                 fprintf(stderr," error during duplicating fds\n");
                 break;
             }
             close(fildes[i1][1]);
         }
         
         }
        int z=readline(cur_command,comm);
         int ff1=z;
        comm[ff1]='\0';
        ff1++;
      


  //parsing for input redirection
     int in=0;
     int flag=0;
     int out=0;
     int save_inp=0;
     int save_out=0;
     char inp[1024];
     char output[1024];
     int ret_size;

    z=0;
     parse1(comm,final1,inp,output,ff1,&in,&out,&flag,&z);
    z--;//doesnot inlclude null value present in final1;

     if(flag == 1)
     printf("command given is wrong\n");
     if(flag == 0)
     {
    //     printf("command op\n");
   
       if(in == 1)
       {
        //  printf("input file\n",inp);
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




        //command menu string and extra memory array for processing
        char cd[]="cd";
        char pwd[]="pwd";
        char echo[]="echo";
        char ls[]="ls";
        char pp[]="pinfo";
        char env1[]="setenv";
        char empty1[]="";
        char env2[]="unsetenv";
        char job1[]="jobs";
        char kill1[]="kjob";
     
      if(flag == 2)
      {
          //done
      }
      else if(flag== 0)
      {
         if(strcmp(final1[0],cd)==0)
        {
            if(z!=2)
            {
                fprintf(stderr,"Given Command is wrong\n");
            }
            
            //handles the cd command
            else
            {
                char tilda[]="~";
                char hyphen[]="-";
    
               if(strcmp(tilda,final1[1])==0)
               {
                   getcwd(prev,size);                   
                   int z1=chdir(home);
                   if(z1==-1)
                   perror("error");
               }


               //handle cd -
               else if(strcmp(hyphen,final1[1])==0)
               {
                   
                   char temp[1024];
                   for(int i=0;i<1024;i++)
                   temp[i]=prev[i];
                   getcwd(prev,size);
                   int z1=chdir(temp);
                   if(z1!=-1)
                   printf("%s\n",getcwd(temp,size));
                   if(z1==-1)
                   perror("error");
               }
                   
                   //handles the general case
               else
               {
                
                   getcwd(prev,size);
                  int z1 = chdir(final1[1]);
                  int z2;
                  
                  char temp[1024];
                  if(z1==-1)
                  {
                      int sd=strlen(dir1);
                      int ss=sd;
                  for(int j=0;j<sd;j++)
                  temp[j]=dir1[j];
                  temp[ss]='/';ss++;

                  int k1=strlen(final1[1]);
                  for(int i=0;i<k1;i++)
                  {
                      temp[ss]=final1[1][i];
                      ss++;
                  }
                  temp[ss]='\0';
                  z2=chdir(temp);
                  }
                 // printf("directory : %s\n",getcwd(temp,size));
                  if(z1==-1 && z2==-1)
                  perror("error");
               }
                
            }
        }
         else if(strcmp(final1[0],"jobs")==0)
         {
           
             if(z==1)
             jobs(pro_id,pro_id_job,pro,store,pjob);
             else
             fprintf(stderr,"wrong number of arguments\n");
         }
         else if(strcmp(final1[0],"quit")==0)
         {
            // fprintf(stderr,"ha\n");
             if(z==1)
             {
              //   fprintf(stderr,"ho\n");
                 exit(0);
             }

         }
         else if(strcmp(final1[0],"fg")==0)
         {

             fg(final1,z,store,&fg_flag);
         }
         //handles kjob
         else if(strcmp(final1[0],kill1)==0)
         {
             kjob(final1,z,store);
         }
         else if(strcmp(final1[0],"bg")==0)
         {
             
             if(z==2)
             bg(final1,z,store);
             else
             fprintf(stderr,"wrong number of argument\n");
         }
//handles setenv
        else if(strcmp(final1[0],env1)==0)
        {
            if(ff1 == 3 )
            {
                int st=setenv(comm[1],empty1,2);
                if(st < 0)
                {
                    fprintf(stderr,"Failure:couldnot set environment variable\n");
                }

            }
            else if(ff1 == 4)
            {
                int st = setenv(comm[1],comm[2],2);
                if(st < 0)
                fprintf(stderr,"Failure:couldnot set environment variable\n");
            }
            else
            {
                fprintf(stderr,"command is wrong\n");
            }

        }
        //handles unsetenv
        else if(strcmp(final1[0],env2)==0)
        {
            if(ff1==3)
            {
                int st=unsetenv(comm[1]);
                if(st < 0)
                fprintf(stderr,"command failed\n");
            }
            else
            {
               fprintf(stderr,"command wrong\n");
            }
        }
        else if(strcmp(final1[0],"overkill")==0)
        {
            overkill(final1,z,store);
        }
    
        else if(strcmp(final1[0],pp)==0)
        {
        //   printf("check %d\n",ff1);
            pinfo1(final1,ff1);
        }
        else if(strcmp(final1[0],pwd)==0)
        {

        // printf("pwd\n");         
            if(z!=1)
            fprintf(stderr,"error due to more than required arguments\n");
            else
            printf("%s\n",getcwd(dir1,size));
        }
        
        //handles echo
        else if(strcmp(final1[0],echo)==0)
        {
         
             echo1(t,x);
             printf("%s\n",x);
        }
        else if(strcmp(final1[0],ls)==0)
        {
            //printf("ls\n");
            
            ls1(final1,z,home);
        }
        else
        {
           
           char empty[]={};
           if(strcmp(empty,final1[0])!=0)
            execute(final1,z,pro_id,pro_id_job,pro,store,pjob,&fg_flag);
        }
      }
    if(flag == 0)
        {
            if(in !=0)
            dup2(save_inp,STDIN_FILENO);
            if(out!=0)
            dup2(save_out,STDOUT_FILENO);
        }
        if(no_of_commands > 1)
        {
        if(i1 == 0)
        {
           // close(fildes[i1][0]);
            dup2(old_stdout,STDOUT_FILENO);
        }
        else if(i1 == no_of_commands-1)
        {
          //  close(fildes[i1-1][0]);
            dup2(old_stdin,STDIN_FILENO);
        }
        else if(i1 < no_of_commands-1 && i1>0)
        {
            dup2(old_stdin,STDIN_FILENO);
            dup2(old_stdout,STDOUT_FILENO);
        }
        }

       }
       }
        
    }
 return 0;
    
}