#include<stdio.h>

int main()
{
    int b,d,r,z,k,i;
    do
    {
        printf("number in binary ");
        scanf("%d",&b);
    }
    while(b <= 0);

    d = 0;
    z = 0;
    k = 2;

    while(b > 0)
    {
        r = b % 10;
        b = b / 10;

        if(r == 0)
        {
            z++;
        }
        else
            if(r == 1)
        {
            for(i = 2 ; i <= z ;i++)
            {
                k = 2*k;
            }

            z++;
            d = d+k;
        }
    }
     printf("%d",d);
return 0;
}
