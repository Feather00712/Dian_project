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

int n = 0; //用选货买阶段
char p[100];
char *q = p;

//用于投币阶段
char b[100];
char *c = b;
int a = 0;

int w = 0;//用于计算撤销次数
int pay[100];
int r = 0;//用于跟踪j的大小

bool if_add = false;//用于选货阶段

int main(void)
{
    //说明用法
    printf("Usage: Input X(A-E) Y(1-5) Y(1-9) Y(1-50) to store things.\n");
    printf("       Input END to skip to next part. \n");
    printf("       Input back to revocate what you just did,but three consistent times at most. \n");
          
    //开始接受输入
again1:  
    printf("Storing started \n");
    while(gets(x))
    {   
        rewind(stdin);                             
        if(i != 0 && s[0] == 'E' && s[1] == 'N' && s[2] == 'D') //若输入END则进入下一阶段
        {   
            w = 0;            
            break;
        }
        else if(i == 0 && s[0] == 'E' && s[1] == 'N' && s[2] == 'D') //但第一次就直接输入END是无效的
        {
            printf("Nothing has been stored,invalid input. \n");
        }
        else if(w < 3 && i != 0 && s[0] == 'b' && s[1] == 'a' && s[2] == 'c' && s[3] == 'k')
        {
            if(if_add == true)
            {
                printf("revocated successfully. \n");
                com[i - 1].channel = 0;
                com[i - 1].name = 0;
                com[i - 1].price = 0;
                com[i - 1].number = 0;//完成一次撤销
                com[r].number = com[r].number - tmp[i].number;
                i--;
                w++;
            }
            else
            {
                printf("revocated successfully. \n");
                com[i - 1].channel = 0;
                com[i - 1].name = 0;
                com[i - 1].price = 0;
                com[i - 1].number = 0;//完成一次撤销
                i--;
                w++;
            }
        }
        else if(w < 3 && i == 0 && s[0] == 'b' && s[1] == 'a' && s[2] == 'c' && s[3] == 'k')
        {
            printf("Nothing has been stored,invalid revocation. \n");
        }
        else if (w >= 3 && s[0] == 'b' && s[1] == 'a' && s[2] == 'c' && s[3] == 'k' )
        {
            printf("Three consistent times of revocations are allowed. You've run out of them. \n");
        }
        else if (!isdigit(s[2]) || s[3] != 32 || !isdigit(s[4]) || s[5] != 32 || !isdigit(s[6]))
        {
            printf("Nonstandard input \n");
        }
        else if (isalpha(s[7]) || s[7] == '.')
        {
            printf("Nonstandard input \n");
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
                if_add = false;
                if(i > 0)
                {
                    //检查是否重复在同一货道上货，若是，则将商品数量相加
                    for(int v = 0; v < i; v++)
                    {
                        if(tmp[i].name == com[v].name )
                        {
                            //确认货道是否一致
                            if(tmp[i].channel != com[v].channel)
                            {
                                if_repetition = true;
                                printf("The channel inputed does not match that before. \n");
                                break;
                            }

                            //确认价格是否一致
                            if(tmp[i].price != com[v].price)
                            {
                                if_repetition = true;
                                printf("The price inputed does not match that before. \n");
                                break;
                            }

                            //不允许同一货道中的物品数量超过50
                            if(tmp[i].number + com[v].number > 50)
                            {
                                if_repetition = true;
                                printf("overstored \n");
                                break;
                            }
                            else
                            {
                                //符合条件则将同种物品数量叠加
                                com[v].number = tmp[i].number + com[v].number; 
                                if_repetition = true;
                                w = 0;
                                r = v;
                                if_add = true;
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
                    for(int v = 0; v < i; v++)
                    {
                        if(tmp[i].channel == com[v].channel)
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
                        w = 0;         
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
    printf("Usage: Input X(A-E) Y(1-10) to pick commodities. \n");
    int sum = 0; 
    char m;

    int sum2 = 0;
    int number2 = 0;

    bool if_back = false;
    bool if_invalid = false;

    int sum1 = 0;
    
again2:
    if_back = false;
    if_invalid = false;

    printf("Picking started. \n");
    while(gets(q))
    {   
        rewind(stdin);                             
        if(n != 0 && p[0] == 'E' && p[1] == 'N' && p[2] == 'D') //若输入END则进入下一阶段
        {   
            w = 0;            
            break;
        }
        else if(n == 0 && p[0] == 'E' && p[1] == 'N' && p[2] == 'D') //但第一次就直接输入END是无效的
        {
            printf("Nothing choosed,invalid input. \n");
        }
        else if(w < 3 && n != 0 && p[0] == 'b' && p[1] == 'a' && p[2] == 'c' && p[3] == 'k')
        {
            printf("revocated successfully \n");
            pay[n - 1] = 0;
            sum = sum - sum2;
            com[n - 1].number = com[n - 1].number + number2;
            buffer[n - 1].name = 0;
            buffer[n - 1].channel = 0;
            buffer[n - 1].price = 0;
            buffer[n - 1].number = 0;//完成一次撤销
            n--;
            w++;
            if_back = true;
        }
        else if(w < 3 && n == 0 && p[0] == 'b' && p[1] == 'a' && p[2] == 'c' && p[3] == 'k')
        {
            w++;
            printf("revocated successfully \n");
            goto again1;
        }
        else if (w >= 3 && p[0] == 'b' && p[1] == 'a' && p[2] == 'c' && p[3] == 'k' )
        {
            printf("Three consistent times of revocations are allowed. You've run out of them. \n");
        }
        else if(p[1] != ' ' || p[3] != ' ')
        {
            printf("Nonstandard input \n");
            if_invalid = true;
        }
        else if(!isdigit(p[2]))
        {
            printf("channel inputed should be an integer.\n");
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
        for(int v = 0; v < i; v++)
        {
            if(buffer[n].name == com[v].name) //检查选择的物品是否存在
            {
                if_yes1 = true;
                if(buffer[n].channel == com[v].channel) //检查选择的物品货道是否与之前的储存匹配
                {
                    if_yes2 = true;                                
                }                                              
            }                       
        }
        if(if_yes1 == false && if_back == false && if_invalid == false)
        {
            printf("commodity wanted does not exist. \n");
        }
        else if(if_yes2 == false && if_back == false)
        {
            printf("channel inputed does not match that before. \n");
        }

        if(if_yes1 == true && if_yes2 == true)
        {
            for(int v = 0; v < i; v++)
            {
              //若其输入的格式正确且有存货
                if(buffer[n].name == com[v].name && buffer[n].channel == com[v].channel && buffer[n].number <= com[v].number) 
                {   
                    pay[n] = buffer[n].number * com[v].price;            
                    sum = sum + (buffer[n].number * com[v].price);
                    sum2 = sum;
                    com[v].number = com[v].number - buffer[n].number;
                    number2 = buffer[n].number; 
                    w = 0; 
                    n++;             
                    break;
                }            
                else if(buffer[n].name == com[v].name && buffer[n].channel == com[v].channel && buffer[n].number > com[v].number) //检查存货是否充足
                {
                    printf("lacking storage \n");                
                }
            }
        }
    }

    //投币环节
    sum1 = 0;
    for (int z = 0; z < n; z++)
    {
        sum1 = sum1 + pay[z];
    }
    printf("The whole price: %d \n", sum1);
    printf("Only 1, 2, 5 are allowed. \n"); 
    int coin;
    int left = sum1;
    int arry[100];
    while(gets(c))
    {
        if (a == 0 && b[0] == 'b' && b[1] == 'a' && b[2] == 'c' && b[3] == 'k' )
        {
            w++;
            goto again2;
        }
        else if (a > 0 && w < 3 && b[0] == 'b' && b[1] == 'a' && b[2] == 'c' && b[3] == 'k' )
        {
            w++;
            left = left + arry[a - 1];          
            printf("%d is back here for you. \n", arry[a - 1]);
            a--;
        }
        else if (w >= 3 && b[0] == 'b' && b[1] == 'a' && b[2] == 'c' && b[3] == 'k' )
        {
            printf("Three consistent times of revocations are allowed. You've run out of them. \n");
        }
        else if(isdigit(b[0]))
        {    
            w = 0;       
            coin = atoi(&b[0]);
            rewind(stdin);
            if (coin != 1 && coin != 2 && coin != 5)
            printf("invalid input\n");        
            else if(left - coin > 0)
            {
                arry[a] = coin;
                left = left - coin;
                a++;
            }
            else if(left - coin == 0)
            {
                arry[a] = coin;
                printf("commodity bought successfully.\n");
                left = left - coin;
                printf("Wanna buy more things? Y or N?\n");
                
                while(~scanf("%c", &m))
                {
                    rewind(stdin);
                    if(m == 'Y')
                    {
                        w = 0;
                        sum1 = 0;
                        goto again2;
                    } 
                    else if(m == 'N')
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
                        w = 0;
                        sum1 = 0;
                        goto again2;
                    }
                    else if(m == 'N')
                    return 0;                
                }
            }
        }
    }     
}