#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct 
{
    char name;
    int channel;
    int price;
    int number;
}commodity;

void revocate(char name, int x, int y, int z);


void revocate(char name, int x, int y, int z)
{
    name = 0;
    x = 0;
    y = 0;
    z = 0;  
}
