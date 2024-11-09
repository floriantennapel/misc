#include <complex.h>
#include <stdio.h>

int mandelbrot(double complex c, int r)
{
    double complex z = 0; 
    for (int i = 0; i < r; i++) {
        z = z*z + c;
        if (cabs(z) > 2) return 0;
    }
    return 1;
}

int main()
{
    double x, y;
    int r, i = 1;
    while ((scanf("%lf %lf %d", &x, &y, &r) != EOF)) 
        printf("Case %d: %s\n", i++, ((mandelbrot(x + I*y, r) ? "IN" : "OUT")));
}
