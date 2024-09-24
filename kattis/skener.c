#include <stdio.h>

int main()
{
    int r, c, zr, zc;
    scanf("%d %d %d %d\n", &r, &c, &zr, &zc);
    char buf[c+1];
    for (int i = 0; i < r; i++) {
        fgets(buf, c+1, stdin);
        getchar();

        for (int zri = 0; zri < zr; zri++) {
            for (int j = 0; j < c; j++) {
                for (int zci = 0; zci < zc; zci++) {
                    putchar(buf[j]);
                }
            }
            putchar('\n');
        }
    }
}