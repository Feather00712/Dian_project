#include <stdbool.h>

#define max_channels 5

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

bool if_add = false;
bool if_repetition = false;
bool if_channelok = true;
bool if_back = false;
bool if_invalid = false;
bool if_yes1 = false;
bool if_yes2 = false;

int sum = 0; 
char m;

int sum2 = 0;
int number2 = 0;

int sum1 = 0;
int coin;
int left;
int arry[100];