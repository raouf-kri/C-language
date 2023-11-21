#include<stdio.h>

int main()
{
int t[20][20],n,i,j;

do
{
    printf("donner la taille de la matrice : ");
    scanf("%d",&n);
}
while(n < 0 || n > 20);

for(i = 0 ; i < n ;i++)
{
    for(j = 0 ; j <= i ;j++)
    {
        scanf("%d",&t[i][j]);
    }
}
for(i = 0 ; i < n ;i++)
{
    for(j = 0 ; j <= i ;j++)
    {
     printf("3%d",t[i][j]);
    }
    printf("\n");
}
return 0;
}
