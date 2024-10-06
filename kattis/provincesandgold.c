#include <stdio.h>

int main()
{
    int g, s, c;
    scanf("%d %d %d", &g, &s, &c);
    int money = 3*g + 2*s + c;

    if      (money >= 8) printf("Province or ");
    else if (money >= 5) printf("Duchy or ");
    else if (money >= 2) printf("Estate or ");

    if      (money >= 6) puts("Gold");
    else if (money >= 3) puts("Silver");
    else                 puts("Copper");
}
