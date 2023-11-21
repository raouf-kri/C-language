#include<stdio.h>

int main()
{
int i,p,x,y;

printf("donner x et y \n");
scanf("%d %d",&x,&y);

if(y>0)
{

p=x;

for(i=2;i<=y;i++)
  {
    p=p*x;
    printf("x^y = %d",p);
  }
}

return 0;}
