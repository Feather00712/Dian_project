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
commodity com[max_channels + 1]; //实际组
commodity tmp[max_channels + 1]; //缓存组
char s[100];
char *x = s;


int main(void)
{
    //说明用法
    printf("Usage: \n");
    int i = 0;   
    
    //开始接受输入  
    while(gets(x))
    {                                
        if(i != 0 && s[0] == 'E' && s[1] == 'N' && s[2] == 'D') //若输入END则进入下一阶段
        {               
            break;
        }
        else if(i == 0 && s[0] == 'E' && s[1] == 'N' && s[2] == 'D') //但第一次就直接输入END是无效的
        {
            printf("ADDDD\n");
        }
        else
        {
            //将有效数据暂时存入缓存组
            tmp[i].name = s[0];
            tmp[i].channel = atoi(&s[2]);
            tmp[i].price = atoi(&s[4]);
            tmp[i].number = atoi(&s[6]);  
            
            //对缓存组的数据进行判断，检查是否符合要求          
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
                //定义需使用的布尔表达式
                bool if_repetition = false;
                bool if_channelok = true;
                if(i > 0)
                {
                    //检查是否重复在同一货道上货，若是，则将商品数量相加
                    for(int j = 0; j < i; j++)
                    {
                        if(tmp[i].name == com[j].name )
                        {
                            //确认货道、价格是否一致
                            if(tmp[i].channel != com[j].channel || tmp[i].price != com[j].price)
                            {
                                if_repetition = true;
                                printf("ac\n");
                                break;
                            }
                            //不允许同一货道中的物品数量超过50
                            if(tmp[i].number + com[j].number > 50)
                            {
                                if_repetition = true;
                                printf("overstored\n");
                                break;
                            }
                            else
                            {
                                com[j].number = tmp[i].number + com[j].number; 
                                if_repetition = false;
                                break;
                            }
                        }
                        else
                        {
                            if_repetition = false;
                        }
                        
                    }                   
                }
                if(if_repetition == false)
                {
                    //检查不同种类商品的货道输入是否重复
                    for(int j = 0; j < i; j++)
                    {
                        if(tmp[i].channel == com[j].channel)
                        {
                            printf("invalid input\n");
                            if_channelok = false;
                            break;                           
                        }
                    }

                    //当用户的输入完全符合要求，则完成本次上货，并将数据储存在com中
                    if(if_channelok == true)
                    {
                        com[i].name = tmp[i].name;
                        com[i].channel = tmp[i].channel;
                        com[i].price = tmp[i].price;
                        com[i].number = tmp[i].number;           
                        i++;
                    }
                }
            }               
        }       
        //最多给五个货道上货
        if(i > 4)
        {
            printf("Channels overused,storing system exited automatically and picking system started\n");
            break;
        } 

        rewind(stdin);       
    }
    printf("ok\n");
    //开始选择货物环节 

    
    
}