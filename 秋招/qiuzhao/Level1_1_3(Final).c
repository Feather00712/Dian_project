#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    //第一次输入必须为商家储存货物，因此对输入进行检查
       //先检查argc是否正确
       bool if_ok1 = false;
       
    if(argc != 5)
    {
        printf("Usage:");
        return 1;
    }
    else
    {
        //检查储存货物的格式是否正确
        //检查是否是字母A~E
        char a = *argv[1];

        if (a < 65 || a > 69 )
        {
            printf("Correct usage : AA");
            return 1;
        }
        else
        {
            for (int i = 2; i < argc; i++)
            {
                //检查是否是整数
                if(isdigit(*argv[i]) == 0)
                {
                    printf("correct usage : AC");
                    return 1;
                }
                
            }

        //检查输入的数字大小是否合适
        if(atoi(argv[2]) <= 0 || atoi(argv[2]) >= 5)
        {
            printf("correct:");
            return 1;
        }
        else if(atoi(argv[3]) <=0 || atoi(argv[3]) >= 11)
        {
            printf("correct:");
            return 1;
        }
        else if(atoi(argv[4]) <= 0 || atoi(argv[4]) >= 51)
        {
            printf("correct:");
            return 1;
        }
        else   
        if_ok1 = true;
        }    
    }
    //进行输出,输出货架情况
    int price = atoi(argv[3]);
    int number = atoi(argv[4]);
    if(if_ok1 == true)
    {
        printf("%d: ", atoi(argv[2]));
        for (int i = 0; i < number; i++)
        {
            printf("%s", argv[1]);
        }
        printf(" %d\n", price);
    }

    //开始投币
    bool if_ok2 = false;
    int n;

    scanf("%d", &n);
    if (n != price)
    {
        printf("correct: \n");
        return 2;
    }
    else
    if_ok2 = true;
  
    if (if_ok2 == true)
    {
        int coin;
        int left = price;
        while(~scanf("%d", &coin))
        {
            if (coin != 1 && coin != 2 && coin != 5)
            printf("invalid input\n");
            else if(left - coin > 0)
            left = left - coin;
            else if(left - coin == 0)
            {
                printf("commodity bought successfully\n");
                left = left - coin;
                return 0;
            }
            else if(left - coin < 0)
            {
                left = left - coin;
                printf("overinput ");
                printf("%d\n",  0 - left);
                return 0;
            }
        }
    }
}