#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>

#define max_channels 5

//初始化结构组
typedef struct 
{
    char name;
    int channel;
    int price;
    int number;
}commodity;

//初始化货物种类
commodity com[max_channels]; //实际组
commodity tmp[max_channels]; //缓存组
char s[100];
char *x = s;


int main(void)
{
    printf("Usage: \n");

    int i = 0;
    while(~scanf("%c %d %d %d", &tmp[i].name, &tmp[i].channel, &tmp[i].price, &tmp[i].number))
    {


        //检查输入的储存货物的格式是否符合要求
        if (tmp[i].name < 'A' || tmp[i].name > 'E')
        {
            printf("AA");
            
        }
        else if (tmp[i].channel < 1 || tmp[i].channel > 5)
        {
            printf("AB");
            
        }
        else if (tmp[i].price  < 1 || tmp[i].price  > 10)
        {
            printf("AC");
            
        }
        else if (tmp[i].number < 1 || tmp[i].number > 50)
        {
            printf("AD");
            
        }
        else
        {
            com[i].name = tmp[i].name;
            com[i].channel = tmp[i].channel;
            com[i].price = tmp[i].price;
            com[i].number = tmp[i].number;
            i++;
        }                  
        //检查是否要结束该过程
        
        rewind(stdin);
        while(gets(x))
        {            
            if(s[0] == 'E' && s[1] == 'N' && s[2] == 'D')
            {               
                break;
            }
            else
            {
                tmp[i].name = s[0];
                tmp[i].channel = atoi(&s[2]);
                tmp[i].price = atoi(&s[4]);
                tmp[i].number = atoi(&s[6]);
             if (tmp[i].name < 'A' || tmp[i].name > 'E')
            {
                printf("AAA\n");            
            }
            else if (tmp[i].channel < 1 || tmp[i].channel > 5)
            {
                printf("ABB\n");            
            }
            else if (tmp[i].price  < 1 || tmp[i].price  > 10)
            {
                printf("ACC\n");            
            }
            else if (tmp[i].number < 1 || tmp[i].number > 50)
            {
                printf("ADD\n");           
            }
            else
            {
                com[i].name = tmp[i].name;
                com[i].channel = tmp[i].channel;
                com[i].price = tmp[i].price;
                com[i].number = tmp[i].number;                               
                printf("%c %d %d %d\n", com[i].name, com[i].channel, com[i].price, com[i].number);
                i++;
            }               
            }
        }
    printf("ok\n");
    return 0;

    //开始选择货物阶段
    //开始投币环节  
    }
}