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
commodity tmp[max_channels + 1]; 
commodity buffer[max_channels + 1];//缓存组2

int i = 0; //用于储存阶段
char s[100];
char *x = s;

int n = 0; //用于购买阶段
char p[100];
char *q = p;

int main(void)
{
    //说明用法
    printf("Usage: Input X(A-E) Y(1-5) Y(1-9) Y(1-50) to store things.Input END to skip to next part\n");
          
    //开始接受输入  
    while(gets(x))
    {                                
        if(i != 0 && s[0] == 'E' && s[1] == 'N' && s[2] == 'D') //若输入END则进入下一阶段
        {               
            break;
        }
        else if(i == 0 && s[0] == 'E' && s[1] == 'N' && s[2] == 'D') //但第一次就直接输入END是无效的
        {
            printf("Nothing has been stored,invalid input. \n");
        }
        else if (!isdigit(s[2]) || s[3] != 32 || !isdigit(s[4]) || s[5] != 32 || !isdigit(s[6]))
        {
            printf("Nonstanderd input \n");
        }
        else if (isalpha(s[7]) || s[7] == '.')
        {
            printf("Nonstanderd input \n");
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
                printf("Only A-E are allowed for names.\n");            
            }
            else if (tmp[i].channel < 1 || tmp[i].channel > 5)
            {
                printf("Only 1-5 are allowed for channels.\n");            
            }
            else if (tmp[i].price  < 1 || tmp[i].price  > 10)
            {
                printf("Only 1-10 are allowed for price.\n");            
            }
            else if (tmp[i].number < 1 || tmp[i].number > 50)
            {
                printf("Only 1-50 are allowed for numbers.\n");           
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
                            //确认货道是否一致
                            if(tmp[i].channel != com[j].channel)
                            {
                                if_repetition = true;
                                printf("The channel inputed does not match that before. \n");
                                break;
                            }

                            //确认价格是否一致
                            if(tmp[i].price != com[j].price)
                            {
                                if_repetition = true;
                                printf("The price inputed does not match that before. \n");
                                break;
                            }

                            //不允许同一货道中的物品数量超过50
                            if(tmp[i].number + com[j].number > 50)
                            {
                                if_repetition = true;
                                printf("overstored \n");
                                break;
                            }
                            else
                            {
                                //符合条件则将同种物品数量叠加
                                com[j].number = tmp[i].number + com[j].number; 
                                if_repetition = true;
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
                            printf("The channel you choose is already taked,invalid input. \n");
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
        if(i > 5)
        {
            printf("Channels overused,storing system exited automatically and picking system started. \n");
            break;
        } 

        rewind(stdin);       
    }    
    //开始选择货物环节
    printf("Input X(A-E) Y(1-10) to pick commodities. \n");
    int sum = 0; 
    char m;

again:
    printf("Picking started. \n");
    while(gets(q))
    {   
                                     
        if(n != 0 && p[0] == 'E' && p[1] == 'N' && p[2] == 'D') //若输入END则进入下一阶段
        {               
            break;
        }
        else if(n == 0 && p[0] == 'E' && p[1] == 'N' && p[2] == 'D') //但第一次就直接输入END是无效的
        {
            printf("Nothing choosed,invalid input. \n");
        }
        else if(!isdigit(p[2]))
        {
            printf("channel inputed should be an intege.\n");
        }
        else if(!isdigit(p[4]))
        {
            printf("number inputed should be an integer.\n");
        }
        else
        {
            //将有效数据暂时存入缓存组
            buffer[n].name = p[0];
            buffer[n].channel = atoi(&p[2]);           
            buffer[n].number = atoi(&p[4]); 
        } 
        
        bool if_yes1 = false;
        bool if_yes2 = false;
        //检查用户的选货指令是否符合格式要求
        //以及其选择的货物是否有存货
        for(int j = 0; j < i; j++)
        {
            if(buffer[n].name == com[j].name) //检查选择的物品是否存在
            {
                if_yes1 = true;
                if(buffer[n].channel == com[j].channel) //检查选择的物品货道是否与之前的储存匹配
                {
                    if_yes2 = true;                                
                }                                              
            }                       
        }
        if(if_yes1 == false)
        {
            printf("commodity wanted does not exist. \n");
        }
        if(if_yes2 == false)
        {
            printf("channel inputed does not match that before. \n");
        }

        if(if_yes1 == true && if_yes2 == true)
        {
            for(int j = 0; j < i; j++)
            {
              //若其输入的格式正确且有存货
                if(buffer[n].name == com[j].name && buffer[n].channel == com[j].channel && buffer[n].number <= com[j].number) 
                {                
                    sum = sum + (buffer[n].number * com[j].price);
                    com[j].number = com[j].number - buffer[n].number;  
                    n++;             
                    break;
                }            
                else if(buffer[n].name == com[j].name && buffer[n].channel == com[j].channel && buffer[n].number > com[j].number) //检查存货是否充足
                {
                    printf("lacking storage \n");                
                }
            }
        }
    }

    //投币环节
    printf("the whole price: %d\n", sum); 
    int coin;
    int left = sum;
    while(~scanf("%d", &coin))
    {
        rewind(stdin);
        if (coin != 1 && coin != 2 && coin != 5)
        printf("invalid input\n");      
        else if(left - coin > 0)
        left = left - coin;
        else if(left - coin == 0)
        {
            printf("commodity bought successfully.\n");
            left = left - coin;
            printf("Wanna buy more things? y or n?\n");
            while(~scanf("%c", &m))
            {
                rewind(stdin);
                if(m == 'y')
                {
                    sum = 0;
                    goto again;
                }
                else if(m == 'n')
                return 0;               
            }
        }
        else if(left - coin < 0)
        {
            left = left - coin;
            printf("overinput \n");
            printf("%d\n",  0 - left);
            printf("Wanna buy more things? Y or N?\n");
            while(~scanf("%c", &m))
            {
                rewind(stdin);
                if(m == 'Y')
                {
                    sum = 0;
                    goto again;
                }
                else if(m == 'N')
                return 0;                
            }
        }
    }     
}