
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<pwd.h>
//#include "readline.h"
 // char* final[100];
int readline(char str[],char* final[])
{
    //char **final;
    char *token;
    const char s[]=" \t";
    token=strtok(str,s);
    int cnt=0;
    while(token != NULL)
    {
        
       final[cnt]=token;
       cnt++;
       token=strtok(NULL,s);
     //  printf("%s here \n",token);
    }
    return cnt;
}
/*int main()
{

/*    char* final[100];
    char inp[1000];
    gets(inp);
    int r=readline(inp,final);
    for(int i=0;i<r;i++)
    printf("%s\n",final[i]);
    return 0;


}*/