#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<pwd.h>
void echo1(char input[1024],char print[1024])
{
    //printf("inside %s\n",input);
    int start=0;
    int k=strlen(input);
    for(int i=4;i<k;i++)
    {
        if(input[i]==' ' && input[i-1]=='o' && input[i-2]=='h' && input[i-3]=='c' && input[i-4]=='e')
        {
            start=i+1;
            break;
        }
    }
   // for(int i=0;i<k;i++)
 //   printf("%d : %c\n",i,input[i]);
   // printf("start : %d\n",start);
    int index=0;
    int cur=0;
    int s=0;
    for(int i=start;i<k;i++)
    {
        if(s==0 && input[i]==' ')
        {
            if(index!=0 && print[index-1]!=' ')
            {
                print[index]=input[i];
                index++;
            }
        }
        else if(s==0 && input[i]=='\t')
        {
            if(index!=0 && print[index-1]!=' ')
            {
                print[index]=' ';
                index++;
            }
        }
        else if(s==0 && (int)input[i]==34)
        {
            s=1;
        }
        else if(s==1 && (int)input[i]==34)
        {
            s=0;
            print[index]=' ';
            index++;
        }
        else 
        {
            print[index]=input[i];
            index++;
        }
    }
    print[index]='\0';
  //  printf("final : %s\n",print);
}
/*int main()
{
    char input[1024];
    char print[1024];
    gets(input);
    echo(input,print);
    printf("%s\n",print);
    return 0;
}*/