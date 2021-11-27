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
int readline(char str[],char* final[]);

void parse1(char *command[100],char *res[100],char input[1024],char output[1024],int size,int  *in,int *out,int *flag,int *ret_size)
{
   // for(int i=0;i<size;i++)
   // printf("%s\n",command[i]);
   int cur=0;
   int i=0;
  // printf("entering parse\n");
  // printf("size : %d, i : %d\n",size,i);
   
   while(i<size-1)
   {
  //     printf("enter loop\n");
    //   printf("i : %d ,size %d",i,size);
      // printf("%d : %s\n",i,command[i]);
       if(strcmp(command[i],">")==0 || strcmp(command[i],">>")==0)
       {
          // printf("inside \n");
           if(strcmp(command[i],">")==0)
           *out=1;
           else
           *out=2;
           i++;
           if(i>=size)
           {
               *flag=1;
           }
           else
           {
               strcpy(output,command[i]);
           }
           i++;
       }
       else if(strcmp(command[i],"<")==0)
       {
         //  printf("outside\n");
           i++;
           if(i>=size)
           {
               *flag=1;

           }
           else
           {
               *in=1;
               strcpy(input,command[i]);
               i++;
           }
       }
       else
       {
           res[cur]=command[i];
           i++;
           cur++;
           //printf("%d haha : %s\n",cur-1,res[cur-1]);
       }
   }
   res[cur]='\0';
   cur++;
//   printf("print return\n");

   *ret_size=cur;
 //  printf("return from parse\n");
}
/*int main()
{
    char *command[100];
    char input[1024];
    char output[1024];
    char sin[1024];
    int flag=0;
    int in=0;
    int out=0;
    int size=0;
    int ret_size=0;
    gets(sin);
    char *res[100];
    size = readline(sin,command);
    parse1(command,res,input,output,size,&in,&out,&flag,&ret_size);
    printf("in : %d  out : %d  flag : %d   size : %d  ret_size : %d\n",in,out,flag,size,ret_size);
    if(!flag && in)
    {
        printf("%s\n",input);
    }
    if(!flag && out)
    {
        printf("%s \n",output);

    }
    for(int i=0;i<ret_size;i++)
    printf("%s  ",res[i]);
    printf("\n");
    return 0;
}*/
