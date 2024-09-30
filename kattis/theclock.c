#include <stdio.h>

int main()
{
    int angle;
    scanf("%d\n", &angle);

    int h = 0;
    int m = 0;
    int dm = 3600 / 60;
    int dh = dm / 12;

    for (int time = 0; time < 12*60; time++) {
        int a = (m + 3600 - h) % 3600;
        if (a == angle) {
            printf("%02d:%02d\n", time / 60, time % 60);
        }

        h += dh;
        m += dm;
    }
}