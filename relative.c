#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<pwd.h>
//#include "relative.h"

char* path1(char to[],char from[])
{
    char* ans=(char *)malloc(1024);
    
  //  printf("initial ans : %s\n",ans);
 //   printf("to : %s and from : %s \n",to,from);
    
    int x=strlen(to);
    int y=strlen(from);
  //  printf("x : %d   y : %d",x,y);
    if(x<y)
    {
        for(int i=0;i<x;i++)
        ans[i]=to[i];
        ans[x]='\0';
    }
    else if(x==y)
    {
        int t=1;
        for(int i=0;i<x;i++)
        {
            if(to[i]!=from[i])
            {
                t=0;
                break;
            }
        }
        if(t==1)
        {
            ans[0]='~';
            ans[1]='\0';
        }
        else 
        {
            for(int i=0;i<x;i++)
            ans[i]=to[i];
            ans[x]='\0';
        }
    }
    else if(x>y)
    {
        int t=1;
        for(int i=0;i<y;i++)
        {
            if(from[i]!=to[i])
            {
                t=0;
                break;
            }
        }
        if(t==1)
        {
            ans[0]='~';
           // printf("ans at 0 : %s\n",ans);
            for(int i=y;i<x;i++)
            {
                ans[1+i-y]=to[i];
              //  printf("to : %s %d : %s\n",to,i,ans);
            }
            ans[1+x-y]='\0';
            
            //for(int i=x+1;i<1024;i++)
            //ans[i]='\0';
        }
        else
        {
            for(int i=0;i<x;i++)
            ans[i]=to[i];
            ans[x]='\0';
            //for(int i=x+1;i<1024;i++)
            //ans[i]='\0';
        }
       // printf("ans here is %s\n",ans);
    }
 return ans;   
}
/*int main()
{
    /*
    char ans[5][1024];
    for(int i=0;i<5;i++)
    {
        char from[1024];
        char to[1024];
        scanf("%s",from);
        scanf("%s",to);
        path(to,from,ans[i]);
        printf("%s\n",ans[i]);
    }
    return 0;
}*/