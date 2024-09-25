#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



int main(int argc, char *argv[])
{
    printf("%s", argv[3]);
    
    //第一次输入必须为商家储存货物，因此对输入进行检查
       //先检查argc是否正确
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
                
                
            }
            printf("success");
                    return 0;
        }    
    }
    
}