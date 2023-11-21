#include<stdio.h>

int main()
{

int r,x;

printf("donner un entier : ");

do
{
    scanf("%d",&r);
    if(r<0)
    {
    printf("fausse insertion !\n");
    printf("redonner un entier positif : ");
    }
}

while(r<0);

x=0;

while(x*x < r)
{
    x++;
}
if(x*x == r)
{
    printf("%d est un carre parfait. ",r);
}
else

    printf("%d est pas un carre parfait.",r);

return 0;
}
