#include <stdio.h>

int main(void)
{
    int x;
    printf("How many? \n");
    scanf("%i", &x);
    if ( x > 0 )
    {
        while (x > 0)
        {
            printf("one dollar...\n");
            x--;
        }
    }
    else if ( x < 0)
    {
        printf("You even have a debt? \n");
    }
    else 
    {
    printf("Go away!\n");
    } 
}
