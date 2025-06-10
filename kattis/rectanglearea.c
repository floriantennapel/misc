#include <stdio.h>
#include <math.h>

int main()
{
    long double x1, y1, x2, y2;
    scanf("%Lf %Lf %Lf %Lf", &x1, &y1, &x2, &y2);
    printf("%Lf\n", fabsl(x1-x2)*fabsl(y1-y2));
}
